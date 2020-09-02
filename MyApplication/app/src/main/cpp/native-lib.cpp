#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_getLine(
        JNIEnv *env,
        jobject /* this */,
        jstring prompt,
        jint value ) {
    const char *str = env->GetStringUTFChars(prompt, NULL);
    if (NULL == str)
        return NULL;

    __android_log_print(ANDROID_LOG_INFO, "App Debug", "%s(default %d) : ", str, value);

    env->ReleaseStringUTFChars(prompt, str);

    const char *buf = "Hello";
    return env->NewStringUTF(buf);
}


extern "C" JNIEXPORT jstring JNICALL
//Java_<pacakge name>_<class name>_<method name>__<signature>
//Function overloading is not supported in C. So signature is needed to verify the functions
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
