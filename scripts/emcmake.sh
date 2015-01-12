#!/bin/bash
export EMSCRIPTEN_ROOT=/home/stalker/emscripten/emsdk_portable/emscripten/incoming
PATH="$EMSCRIPTEN_ROOT:$PATH"
PATH="/home/stalker/emscripten/emsdk_portable:$PATH"
PATH="/home/stalker/emscripten/emsdk_portable/clang/fastcomp/build_master_64/bin:$PATH"
rm -rf build
mkdir build
cd build
emcmake cmake \
        -G "Unix Makefiles" \
        -D EMSCRIPTEN_PATH=$EMSCRIPTEN_ROOT \
        -D EMSCRIPTEN=ON \
        -D CMAKE_BUILD_TYPE=Debug \
        -D BUILD_TESTS=ON \
        ..

make -j2

