#!/bin/sh

#export NDK=$PWD/../android-ndk-r10e

#python %NDK%/build/tools/make_standalone_toolchain.py -v --arch arm --api 17 --install-dir=ndk_toolchain

export ANDR_TOOLCHAIN=$PWD/../toolchain
#$(NDK)/build/tools/make-standalone-toolchain.sh  --platform=android-14 --arch=arm --install-dir=$(ANDR_TOOLCHAIN) --ndk-dir=$(NDK) #--system=windows-x86_64

export PATH=$PWD/Linux/386/bin:$ANDR_TOOLCHAIN/bin:$PATH

export ROOT=$PWD

mk clean

