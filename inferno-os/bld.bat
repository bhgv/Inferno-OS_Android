
::set NDK=D:\Android\sdk\ndk-bundle
set NDK=D:/andro-dev/android-ndk-r10d

set PWD=C:/Users/x200t/AndroidStudioProjects/inferno_os/inferno-os

::python %NDK%/build/tools/make_standalone_toolchain.py -v --arch arm --api 17 --install-dir=ndk_toolchain

::D:/andro-dev/android-ndk-r10d/build/tools/make-standalone-toolchain.sh  --platform=android-19 --arch=arm --install-dir=./ndk_toolchain --ndk-dir=D:/andro-dev/android-ndk-r10d --system=windows-x86_64


set PATH=%PWD%/Nt/386/bin;%PWD%/ndk_toolchain/bin;%PATH%

::call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86

::mk clean

mk install

::emu -r./ 
::wm/wm
