#include <jni.h>
#include <android/log.h>
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifndef APP_GLUE
#define APP_GLUE

#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-activity", __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

class OutputRedirector
{
public:
    OutputRedirector(int logFd)
        : old_stdout(-1), old_stderr(-1)
    {
        old_stdout = ::dup(STDOUT_FILENO);
        ::dup2(logFd, STDOUT_FILENO);
        old_stderr = ::dup(STDERR_FILENO);
        ::dup2(logFd, STDERR_FILENO);
        ::close(logFd);
    }

    ~OutputRedirector()
    {
        ::dup2(old_stdout, STDOUT_FILENO);
        ::close(old_stdout);
        ::dup2(old_stderr, STDERR_FILENO);
        ::close(old_stderr);
    }

private:
    int old_stdout;
    int old_stderr;
};

static JavaVM *gVM;

static void convertArgs(JNIEnv *env, 
                        jobjectArray java_args, 
                        std::vector<char *> &args)
{
    int java_argcount = env->GetArrayLength(java_args);
    for (int i = 0; i < java_argcount; ++i) {
        jstring string = static_cast<jstring>(env->GetObjectArrayElement(java_args, i));
        const char *java_arg = env->GetStringUTFChars(string, 0);
        args.push_back(::strdup(java_arg));
        env->ReleaseStringUTFChars(string, java_arg);
        env->DeleteLocalRef(string);
    }
    args.push_back(0);
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_structures_unittests_RunUnittests_stringFromJNI(JNIEnv* env, 
                                                         jobject obj, 
                                                         jstring java_appPath, 
                                                         jstring java_logFilename, 
                                                         jobjectArray java_args)
{
    const char *appPath = env->GetStringUTFChars(java_appPath, 0);
    env->ReleaseStringUTFChars(java_appPath, appPath);

    const char *logFilename = env->GetStringUTFChars(java_logFilename, 0);
    int logFd = ::open(logFilename, O_TRUNC | O_CREAT | O_RDWR, 0660);
    env->ReleaseStringUTFChars(java_logFilename, logFilename);
    if (logFd == -1) {
        return JNI_FALSE;
    }
    
    OutputRedirector redirector(logFd);
    
    std::vector<char *> args;
    convertArgs(env, java_args, args);
    std::vector<char *> original_args = args;

    char **argv = args.data();
    int argc = args.size() - 1;

    const char *appPath2 = env->GetStringUTFChars(java_appPath, 0);;
    return env->NewStringUTF(appPath2);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_structures_unittests_RunUnittests_runTests(JNIEnv* env, 
                                                    jobject obj, 
                                                    jstring java_appPath, 
                                                    jstring java_logFilename, 
                                                    jobjectArray java_args)
{  
    const char *appPath = env->GetStringUTFChars(java_appPath, 0);
    env->ReleaseStringUTFChars(java_appPath, appPath);

    const char *logFilename = env->GetStringUTFChars(java_logFilename, 0);
    int logFd = ::open(logFilename, O_TRUNC | O_CREAT | O_RDWR, 0660);
    env->ReleaseStringUTFChars(java_logFilename, logFilename);
    if (logFd == -1) {
        return JNI_FALSE;
    }
    
    OutputRedirector redirector(logFd);

    std::vector<char *> args;
    std::vector<char *> original_args = args;

    char **argv = args.data();
    int argc = args.size() - 1;

    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    std::fstream f("/data/user/10/com.structures.unittests/files/out.xml");
    if (f.good()) {
        f.close();
        for (unsigned int i = 0; i < original_args.size() - 1; ++i) {
            ::free(args[i]);
        }
        return (result == 0) ? JNI_TRUE : JNI_FALSE;
    } else {
        f.close();
        return JNI_FALSE;
    }
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM* vm, void* reserved)
{
    gVM = vm;
    return JNI_VERSION_1_6;
}

#endif //  APP_GLUE