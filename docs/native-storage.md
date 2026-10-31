# Native storage and Inferno library selection

All new runtime code is C/C++. No application Java source or JNI call is added.
The existing NativeActivity launch callback supplies internalDataPath and
AAssetManager before amain. ioa_prepare_storage creates its Inferno child,
deploys missing bundled files, then sets INFERNO_FILES_DIR. It also redirects
EXTERNAL_STORAGE inside this process for compatibility with the older bundled
amain, which otherwise appends /Inferno to that variable.

The system-provided private directory is accessible to this app without shared
storage permission, including scoped-storage Android versions. It is not a
public folder for arbitrary file managers; Android may remove it on uninstall.
No /sdcard access bypass, hidden platform API or all-files permission is used.

The Android-specific launch and APK packaging stay in this repository. The
cross-platform Inferno repository supplies the native resolver in emu/Android.
Its C directory API is available to other native launchers; activity/asset APIs
remain in this APK repository. The environment bridge also supports the older
bundled Inferno tree.

## Build inputs

Build Inferno libraries and Limbo runtime programs before assembling the APK.
In particular, dis/emuinit.dis must exist. The staging script packages dis, lib,
fonts, icons and the default usr/inferno tree, plus required empty mount points.
It excludes host toolchains, source/compiler directories and native archives.

```
python3 tools/stage-inferno.py --source /path/to/Inferno-OS-bhgv --output /path/to/generated/inferno
./gradlew -PinfernoRoot=/path/to/Inferno-OS-bhgv assembleDebug
```

Gradle automatically stages data into build/generated/infernoAssets before the
APK build. infernoPython selects the Python executable (default python3).
The manifest preserves parent-first directory creation and bounds native input.
Incomplete file writes use a temporary file and are retried on the next launch.
Existing files are never overwritten, including startup configuration and user
edits. Runtime updates therefore require deliberately backing up and refreshing
the private root; this is not a general automatic migration service.

CMake maps armeabi-v7a to Android/arm/lib, arm64-v8a to Android/arm64/lib and
x86_64 to Android/amd64/lib. infernoRoot selects the source/library tree;
infernoAbis is a comma-separated Gradle property, default armeabi-v7a.
Do not enable a 64-bit ABI until its complete platform archives have been built:
new mkfiles are toolchain profiles, not missing emu assembly/FPU/signal ports.
The existing Gradle/SDK setup is still legacy; these changes do not claim a
modern toolchain migration or an APK tested on every Android release.

## Verification

python3 tests/native-storage.py compiles the complete actual installer with
-Wall -Wextra -Werror and strict UBSan. A bounded host asset-manager adapter
uses real files to check packaging, deployment, user-edit preservation, missing
asset cleanup, retry and invalid manifest paths. It does not emulate Android
permissions, validate an APK or execute the complete GUI on a device.

References:
https://developer.android.com/ndk/reference/struct/a-native-activity
https://developer.android.com/training/data-storage/app-specific

The actual CMake ABI-selection gate is tests/cmake-abis.py (set CMAKE if needed).
It configures all three mappings and rejects an unsupported ABI, using a host
glue placeholder. It does not compile Android sources or validate NDK archives.
