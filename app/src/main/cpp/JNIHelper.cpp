//
// Created by zhzl on 2018/2/3.
//

#include "JNIHelper.h"

JavaVM* JNIHelper::s_javaVM = nullptr;
std::string JNIHelper::s_apkPath = "";
static pthread_key_t g_key;

//清理函数，释放线程存储的时候被调用
void _detachCurrentThread(void* a)
{
    JNIHelper::getJavaVM()->DetachCurrentThread();
}

void JNIHelper::setJavaVM(JavaVM *javaVM)
{
    // 保存java虚拟机
    s_javaVM = javaVM;
    // 创建线程存储
    pthread_key_create(&g_key, _detachCurrentThread);
}

JavaVM *JNIHelper::getJavaVM()
{
    return s_javaVM;
}

JNIEnv *JNIHelper::cacheEnv(JavaVM *jvm)
{
    JNIEnv* env = nullptr;
    jint ret = jvm->GetEnv((void**)&env, JNI_VERSION_1_4);
    switch (ret)
    {
        case JNI_OK:
            pthread_setspecific(g_key, env);
            return env;
        case JNI_EDETACHED: // 当前线程没有与VM建立关联
            if (jvm->AttachCurrentThread(&env, nullptr) >= 0)
            {
                // 关联成功
                pthread_setspecific(g_key, env);
                return env;
            }
        case JNI_EVERSION:
        default:
            return nullptr;
    }
}

JNIEnv *JNIHelper::getEnv()
{
    JNIEnv* env = (JNIEnv*)pthread_getspecific(g_key);
    if (env == nullptr)
        env = JNIHelper::cacheEnv(s_javaVM);
    return env;
}

std::string JNIHelper::jstring2string(jstring jstr)
{
    if (jstr == nullptr)
        return "";

    JNIEnv* env = JNIHelper::getEnv();
    if (!env)
        return "";

    const jclass stringClass = env->GetObjectClass(jstr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray)env->CallObjectMethod(jstr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t)env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);
    std::string ret = std::string((char*)pBytes, length);

    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);
    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);

    return ret;
}

void JNIHelper::setApkPath(std::string apkPath) {
    s_apkPath = apkPath;
}

std::string JNIHelper::getApkPath() {
    return s_apkPath;
}
