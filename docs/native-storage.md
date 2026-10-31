# Shared Inferno tree and native library selection

Runtime files are used exclusively from `/sdcard/Inferno`. By default the APK
contains no runtime tree: populate this existing shared directory yourself,
including dis/emuinit.dis. There is no internal-directory fallback. Private trees
created by the withdrawn installer are neither migrated nor deleted automatically.

Optional provisioning is enabled with:

```
./gradlew -PinfernoBundleRuntime=true -PinfernoRoot=/path/to/Inferno-OS-bhgv assembleDebug
```

This stages compiled runtime assets into the APK and enables native extraction
directly into `/sdcard/Inferno` before startup. Only missing files are written;
existing files, including user edits, are preserved. Interrupted installation
can be retried. Switching the option off removes generated runtime assets from
the next APK. Runtime execution always uses the shared directory, never assets
or a private copy. The option is a build-time choice, default false.

Native startup verifies that the shared directory is readable, writable and
searchable. For the older bundled amain it sets EXTERNAL_STORAGE to /sdcard
inside the process. It does not supply INFERNO_FILES_DIR or use NativeActivity's
internalDataPath. If access is unavailable, startup reports an explicit error.
The launcher must have the shared-storage permissions allowed by the device's
Android policy; this change does not guarantee access on every Android release.
No Java source or new JNI call is introduced.

## Build inputs

Build Inferno's native archives before assembling the APK:

```
./gradlew -PinfernoRoot=/path/to/Inferno-OS-bhgv assembleDebug
```

CMake maps armeabi-v7a to Android/arm/lib, arm64-v8a to Android/arm64/lib and
x86_64 to Android/amd64/lib. infernoRoot selects the source/library tree;
infernoAbis is a comma-separated Gradle property, default armeabi-v7a.
This library selection does not move runtime files or change /sdcard/Inferno.
Do not enable a 64-bit ABI until its complete platform archives have been built.
The existing Gradle/SDK setup remains legacy. APK/device testing is outstanding.

## Verification

`python3 tests/shared-storage.py` compiles the actual C resolver with strict
UBSan and checks exact shared-path requests, permission flags, missing paths,
non-directory paths and denied access through bounded host stat/access adapters.
It also checks the compatibility environment value. It cannot certify Android
permissions or replace testing on a device.

`python3 tests/cmake-abis.py` checks actual CMake configuration for the three ABIs
and unsupported ABI rejection. Set CMAKE to the desired executable if needed.

`python3 tests/native-storage.py` enables provisioning and checks actual file
extraction, preserving existing files, failed-copy cleanup, retry, invalid paths
and disabling generated assets. A host asset adapter and remapped shared mount
stand in for Android APIs; no device permission behavior is certified.
