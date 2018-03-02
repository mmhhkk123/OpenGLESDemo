#include "com_example_zhzl_myapp_JNIHelper.h"
#include "JNIHelper.h"
#include <string>

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIHelper::setJavaVM(vm);
    return JNI_VERSION_1_4;
}

JNIEXPORT void JNICALL Java_com_example_zhzl_myapp_JNIHelper_nativeSetApkPath
        (JNIEnv *, jclass, jstring apkPath)
{
    std::string path = JNIHelper::jstring2string(apkPath);
    JNIHelper::setApkPath(path);
}