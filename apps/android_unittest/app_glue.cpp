#include <jni.h>
#include <android/log.h>
#include <hype/Context.h>
#include <hype/Settings.h>
#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

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

static void convertArgs(JNIEnv *env, jobjectArray java_args, std::vector<char *> &args)
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

static JavaVM *gVM;

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_here_geoviz_unittest_test_TestRunner_runTests(JNIEnv* env, jobject obj, jstring java_appPath, jstring java_logFilename, jobjectArray java_args)
{
    LOGI("runTests");
    // Get Context
    jclass clazz = env->GetObjectClass(obj);
    if (!clazz || env->ExceptionOccurred()) {
        LOGE("runTests failed to get class for object");
        env->ExceptionDescribe();
        env->ExceptionClear();
        return JNI_FALSE;
    }

    jmethodID getContext = env->GetMethodID(clazz, "getContext", "()Landroid/content/Context;");
    if (!getContext || env->ExceptionOccurred()) {
        LOGE("runTests failed to get getContext method");
        env->ExceptionDescribe();
        env->ExceptionClear();
        return JNI_FALSE;
    }

    jobject context = env->CallObjectMethod(obj, getContext);
    if (!context || env->ExceptionOccurred()) {
        LOGE("runTests failed to get Context");
        env->ExceptionDescribe();
        env->ExceptionClear();
        return JNI_FALSE;
    }

    const char *appPath = env->GetStringUTFChars(java_appPath, 0);
    hype::Context::init(appPath, gVM, context);
    env->ReleaseStringUTFChars(java_appPath, appPath);

    const char *logFilename = env->GetStringUTFChars(java_logFilename, 0);
    int logFd = ::open(logFilename, O_TRUNC | O_CREAT | O_RDWR, 0660);
    env->ReleaseStringUTFChars(java_logFilename, logFilename);
    if (logFd == -1) {
        LOGE("Cannot open log file: %s", strerror(errno));
        return JNI_FALSE;
    }

    OutputRedirector redirector(logFd);

    std::vector<char *> args;
    convertArgs(env, java_args, args);
    std::vector<char *> original_args = args;

    char **argv = args.data();
    int argc = args.size() - 1;

    for (int i = 0; i < argc; ++i) {
        if (strncmp(argv[i], "-D", 2)==0) {
            if (i < argc - 1) {
                hype::Settings::setValue(&argv[i][2], argv[i + 1]);
                i++;
            } else {
                hype::Settings::setValue(&argv[i][2], std::string());
            }
        }
    }

    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    for (unsigned int i = 0; i < original_args.size() - 1; ++i) {
        ::free(args[i]);
    }
    LOGI("result=%d", result);
    return (result == 0) ? JNI_TRUE : JNI_FALSE;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM* vm, void* reserved)
{
    LOGI("JNI_OnLoad");
    gVM = vm;
    return JNI_VERSION_1_6;
}