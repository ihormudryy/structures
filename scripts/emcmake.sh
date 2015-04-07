#!/bin/bash
export EMSCRIPTEN=/opt/emscripten/emsdk_portable/emscripten/master
export EMSCRIPTEN_ROOT='/opt/emscripten/emsdk_portable/emscripten/master'
export LLVM_ROOT='/var/lib/emscripten/emsdk_portable/clang/fastcomp/build_master_64/bin'
PATH="$EMSCRIPTEN_ROOT:$PATH"
PATH="/opt/emscripten/emsdk_portable:$PATH"
PATH="/opt/emscripten/emsdk_portable/clang/fastcomp/build_master_64/bin:$PATH"

rm -rf build
mkdir build
cd build
WORKSPACE=$(pwd)

cd /opt/emscripten/emsdk_portable
./emsdk activate sdk-master-64bit
./emsdk list
./emsdk_env.sh

cd $WORKSPACE

emcmake cmake \
        -D EMSCRIPTEN_PATH=$EMSCRIPTEN_ROOT \
        -D EMSCRIPTEN=ON \
        -D CMAKE_BUILD_TYPE=Debug \
        -D BUILD_TESTS=ON \
        ..

make -j2