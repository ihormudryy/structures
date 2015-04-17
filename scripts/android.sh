#!/bin/bash
export NDK_ROOT=$ANDROID_NDK
export SDK_ROOT=$ANDROID_SDK

PATH=$QT_LIB_ROOT/android_armv7/bin:$PATH
PATH=$SDK_ROOT/tools:$PATH
PATH=$SDK_ROOT:$PATH
PATH=$NDK_ROOT/toolchains:$PATH
PATH=$NDK_ROOT:$PATH

export CMAKE_PREFIX_PATH=$QT_ROOT/5.4/android_armv7
export CROSS_COMPILE=arm-linux-gnueabi-

PROJECT_DIR=~/Dropbox/structures
BUILD_DIR=~/structures_android_build

rm -rf $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR

#echo $PATH

cmake \
	-D ANDROID=ON \
	-D CMAKE_BUILD_TYPE=Debug \
	$PROJECT_DIR

make -j2
