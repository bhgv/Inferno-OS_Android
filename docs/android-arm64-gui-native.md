# ARM64 native GUI build

The `experiment-arm64-gui` branch updates the ordinary framebuffer NativeActivity
for modern NDK builds. Its event loop uses `ALooper_pollOnce`; recorder buffers
are arrays of sample pointers. It is separate from the scalar probe activity.

The core `experiment` branch supplies `utils/tests/android-gui-build.py`:

```sh
python3 /path/to/core/utils/tests/android-gui-build.py \
  --ndk /path/to/android-ndk-r27c \
  --host-tools /path/to/native-host-tools \
  --app-root /path/to/Inferno-OS_Android \
  --build-root /path/to/empty-output
```

It compiles the complete WORD32/ref64 Android core with Draw/Tk, FreeType,
framebuffer and audio, and links the actual NativeActivity shared library.
The output includes ELF inspection, build logs and `result.json`.

This is native compilation/linking evidence, not a working AWM APK. The ordinary
entry still refuses legacy int32/ref32 builtin registration on LP64. General
managed Dis64 compilation, coherent builtin frames/maps and full GUI startup
remain required before packaging this as a usable ARM64 desktop. No ABI guard
has been disabled, and no scalar-probe result is used as AWM acceptance.
