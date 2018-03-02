//
// Created by zhzl on 2018/2/3.
//

#ifndef MYAPP1_JNIHELPER_H
#define MYAPP1_JNIHELPER_H


#include <jni.h>
#include <string>

class JNIHelper {

public:
    static JavaVM* getJavaVM();
    static JNIEnv* getEnv();
    static std::string jstring2string(jstring jstr);
    static std::string getApkPath();

    static void setJavaVM(JavaVM* javaVM);
    static void setApkPath(std::string apkPath);

private:
    static JNIEnv* cacheEnv(JavaVM* jvm);

private:
    static JavaVM* s_javaVM;
    static std::string s_apkPath;
};


#endif //MYAPP1_JNIHELPER_H
