#!/bin/bash
export ANDROID_NDK_ROOT=$ANDROID_NDK
export ANDROID_SDK_ROOT=$ANDROID_SDK
export NDK_ROOT=$ANDROID_NDK
export SDK_ROOT=$ANDROID_SDK
export CMAKE_PREFIX_PATH=$QT_ROOT/5.4/android_armv7
export PLATFORM=android-armeabi-v7a

PATH=$SDK_ROOT/tools:$PATH
PATH=$SDK_ROOT:$PATH

PROJECT_DIR=~/Dropbox/structures
BUILD_DIR=~/structures_android_build

rm -rf $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR

cmake \
	-D ANDROID=ON \
	-D CMAKE_TOOLCHAIN_FILE=$PROJECT_DIR/cmake/toolchains/Android.cmake \
	$PROJECT_DIR

make -j8
