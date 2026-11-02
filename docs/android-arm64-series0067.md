# Android ARM64 scalar framebuffer APK: series0067

This is a native-only ARM64 execution probe, not a full AWM desktop. The full
client still needs general Dis64 file calls, managed/import ownership and GUI
startup admission. Native JIT command coverage alone does not establish that.
The application runs only from /sdcard/Inferno; no private runtime tree or Java
application code is introduced. The existing ARM32 FB/GLES packages are separate.

The source pins Inferno4a910d74001e6868e35c7bc69a0d86afcdec4fdd and NDK r27c.
Classic mk builds the real Android/arm64 runtime. Before signing, ARM64/Bionic
QEMU runs the existing boot corpus,67 numeric-case sources and167 helper/result
sources in interpreter and JIT, including active controls. Exact packaged-image
runs also check real worker retirement. These are not NativeActivity/phone tests.

The bundled program executes4097 result-producing calls, fresh local renewal,
numeric cases, nested Word result forwarding, Big arithmetic results and exact
Real result delivery while retaining caller storage. Host x64 VM modes0/1 pass;
source compiler image SHA256 is
9138ae33fb041adb8b0b689ad1e5c1420fdb5d86a33f0c4dad6c6e96b05c18e0.
Cross-target APK CI and downloadable checksums follow after completion.

Both APK modes use isolated series0067 package IDs and a new
/sdcard/Inferno/dis/native64-apk/series0067-probe.dis64 path. Existing exact
probe bytes are reused; differing files are refused without overwrite. Existing
Inferno trees remain in place. Status identifies scalar execution and does not
claim AWM startup. Diagnostics stay in /sdcard/Inferno/native64-fb-probe.log.
The production result checker now rejects a panic even after completion markers;
a real-file host fixture and active removal control prove that rejection.
