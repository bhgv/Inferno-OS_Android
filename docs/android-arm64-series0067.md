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


## Verified APK pair and downloads

[Build41398236383](https://github.com/bhgv/Inferno-OS_Android/actions/runs/41398236383)
passes with core4a910d74001e6868e35c7bc69a0d86afcdec4fdd and launcher
7a60a15d46bf4690bbd8693b76edf11e9efe9a4f, NDK r27c. The initial build exposed
an undeclared poolmutable call in production Draw; the core now includes its
owning pool.h and classic-mk dependency, without compiler-error suppression.

[Download both APKs and full execution evidence](https://github.com/bhgv/Inferno-OS_Android/actions/runs/41398236383/artifacts/13119948900).

| APK | Mode | SHA256 |
| --- | --- | --- |
| Inferno-FB-arm64-v8a-series0067-jit0.apk | C interpreter | 2dbde4056d2399d1a65fedf4ee378add6bfda64f1410e37525e1776a228861d2 |
| Inferno-FB-arm64-v8a-series0067-jit1.apk | ARM64 JIT | 0a5b7562570899e145aba2e12da3a8f2bd4c6bc9e61fddbf241b57f46ff5b2db |

Each downloaded APK is4608846 bytes and matches its recorded checksum. Both
contain exactly the expected ARM64 ELF64 library,16KiB LOAD alignment, the
checked9138ae33... probe image and no DEX. CI verifies v1/v2/v3 signatures and
zip alignment. Package IDs end in series0067.jit0 and series0067.jit1 so both
can be installed independently. The native screen should show PASS after the
program and scheduler complete; shared-storage permission remains a phone step.

Real ARM64/Bionic QEMU logs pass167 helper sources /334 whole C/JIT processes
plus all8 active VM controls and16 refusals;67 case sources /134 processes and
67 stale-PC controls; the existing boot corpus and both exact packaged-image
runs with real worker retirement. Host production-function tests pass reuse,
no overwrite, partial reads, denial/retry, prior-session rejection, pending-worker
double-tap refusal and the new active panic-marker control. These runtime tests
adapt only Android logging/symbolization/CLI completion; actual VM, JIT, libc
and pthread cleanup execute. Physical NativeActivity, screen/storage permissions,
GPU and16KiB-page phone acceptance are not established by QEMU.

A complete ARM64 AWM client still needs shared runtime file-call/managed-import
admission and native64 builtin/GUI layouts across startup. The current trusted
scalar path and JIT173/173 dispatch do not supply those application contracts.
