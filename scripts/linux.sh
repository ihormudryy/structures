#!/bin/bash
PROJECT_DIR=~/Dropbox/structures
BUILD_DIR=~/structures_build

rm -rf $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR

cmake $PROJECT_DIR

make -j8
