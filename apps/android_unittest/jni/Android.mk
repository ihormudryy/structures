# Minimal Android.mk to support the ndk-gdb command
APP_STL := gnustl_shared
APP_ABI := @ANDROID_ABI@
LOCAL_LDLIBS += -llog