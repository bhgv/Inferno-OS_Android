
set NDK=D:\Android\sdk\ndk-bundle

set PWD=C:/Users/x200t/AndroidStudioProjects/inferno_os/inferno-os

python %NDK%/build/tools/make_standalone_toolchain.py --arch arm --api 17 --install-dir=ndk_toolchain


set PATH=%PWD%/Nt/386/bin;%PWD%/ndk_toolchain/bin;%PATH%

::call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86

::mk clean

mk install

::emu -r./ 
::wm/wm
