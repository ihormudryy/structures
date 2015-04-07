# Minimal Android.mk to support the ndk-gdb command
APP_STL := gnustl_shared
APP_ABI := armeabi-v7a
LOCAL_LDLIBS += -llog