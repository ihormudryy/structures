#include <stdio.h>
#include <iostream>
#include <stdlib.h>


#include <android_native_app_glue.h>
#include <android/log.h>
#define APPNAME "app_name"

ANativeActivity_onCreate()
{
    std::cout << "HELLO ANDROID" << std::endl;
}

void android_main(struct android_app* state)
{
    app_dummy(); // Make sure glue isn't stripped

    __android_log_print(ANDROID_LOG_INFO, APPNAME, "HolyShit you did it !");

    ANativeActivity_finish(state->activity);
}