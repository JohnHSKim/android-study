#include <jni.h>
#include <string>
#include <android/log.h>
#include <unistd.h>
#include <sys/types.h>

// Example 2-03
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_JNICallBackMethod_PrinttoString(JNIEnv *env,
                                                               jobject obj) {
    jclass cls = env->GetObjectClass(obj);
    jmethodID mid = env->GetMethodID(cls, "toString", "()Ljava/lang/String;");

    jstring s = (jstring) env->CallNonvirtualObjectMethod(obj, cls, mid);
    const char *buf = env->GetStringUTFChars(s, 0);

    __android_log_print(ANDROID_LOG_INFO, "JNICallBackMethod_PrinttoString", "%s", buf);

    env->ReleaseStringUTFChars(s, buf);
    return s;
}


// Example 2-02
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_getLine(
        JNIEnv *env,
        jobject /* this */,
        jstring prompt,
        jint value) {
    const char *str = env->GetStringUTFChars(prompt, NULL);
    if (NULL == str)
        return NULL;

    __android_log_print(ANDROID_LOG_INFO, "App Debug", "%s(default %d) : ", str, value);

    env->ReleaseStringUTFChars(prompt, str);

    const char *buf = "Hello";
    return env->NewStringUTF(buf);
}


// Example 2-01
//Java_<pacakge name>_<class name>_<method name>__<signature>
//Function overloading is not supported in C. So signature is needed to verify the functions
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
//    std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());

    // Example 3-04
    char dump[300];
    sprintf(dump, "Process uid=%d, gid=%d, effective uid=%d, effective gid=%d \n", (int) getuid(),
            (int) getgid(), (int) getegid(), (int) getegid());
    return env->NewStringUTF(dump);
}
