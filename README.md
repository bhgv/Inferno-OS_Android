# Inferno-OS_Android
for Android > v4.0 (api 14)

it is based on the last [official sources from Vitanuova](https://bitbucket.org/inferno-os/inferno-os/).

I have built it under Windows. But if you are using Linux it is easy to build it under Linux. only a pair of changes. go to the "inferno-os" folder and rewrite "bld.bat" script to Linux one. also do not forget to make a Linux tools modifying "makeconfig" script and so on.

## Dependencies
* Android Studio > v3.0
* Cmake plugin for Android Studio
* NDK 

# how to build

## Windows host
```
cd inferno-os
bld.bat
```
after the successful building of the inferno libs (`./inferno-os/Android/arm/lib`)
open this project in the Android Studio and build apk.

# how to run
install this apk on the android
copy this inferno tree (`./inferno-os`) to android by the path `/sdcard/Inferno`.

run it
