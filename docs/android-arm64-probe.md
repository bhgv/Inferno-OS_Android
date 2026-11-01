# ARM64 framebuffer execution probes

This is a separate native-only ARM64 APK entry, not an ARM32 package relabelled
as arm64-v8a. It links a clean Bionic/ARM64 core built with classic mk using
CONF=emu-scalar. Core flags select the agreed restricted Dis64 profile and
refuse legacy native module tables. No application Java/DEX or Clutter stack
is required. Normal FB/GLES ARM32 build scripts and AWM startup are unchanged.

`tools/build-arm64-probe.sh` builds two signed packages: interpreter (JIT=0)
and ARM64 JIT (JIT=1). Both include exactly the same self-checking image.
The native framebuffer screen reports preparation, access errors, execution
and PASS/FAIL. PASS requires this session's actual named-module completion,
requested JIT mode and empty scheduler, without Broken/fault diagnostics.
It is not an installation-only or synthetic UI success message.

Install either APK, grant Files/Storage in Android settings and open it.
If access is denied, the native screen explains it; after granting access,
return and tap to retry. The app may also require Android's All files access
setting for /sdcard/Inferno. It never falls back to internal storage.
The only runtime image installed by this probe is
/sdcard/Inferno/dis/native64-apk/series0059-probe.dis64. Exact existing bytes
are reused; different/partial files are refused without overwriting. The normal
Inferno tree and lib/startup/cmd_line.txt are not changed. Diagnostics append to
/sdcard/Inferno/native64-fb-probe.log. Back closes this isolated VM process.

The program checks 4097 calls with fresh scalar locals, arithmetic, numeric
case lowering and caller Big/Real storage. Before packaging, the build runs
real static Bionic processes through QEMU with both execution modes, active
wrong-result controls and import/legacy refusals. Only Android log-daemon,
dynamic symbol lookup and CLI completion are adapted in that test executable;
the APK uses the real system Android libraries and framebuffer APIs.

Local ARM64 core and APK shared-library compilation/linking passes with NDK
r16b; the automated APK build pins modern NDK r27c, records its revision and
uses 16KiB ELF load alignment with extracted native libraries. The host gate
executes the production asset installer and result checker with real bounded
file I/O, including refusal to overwrite, denial, short reads, cleanup/retry,
previous-session false-success rejection and native-fault rejection.

A signed build and a QEMU/Bionic pass do not establish physical Android launch,
SELinux JIT behavior, framebuffer presentation or permissions on a particular
phone. Device feedback remains required. This is not a complete AWM desktop:
general native64 module imports and managed calling ABI remain unfinished.

The modern-Bionic link gate exposed standard-symbol collisions in Inferno's
strtoll/strtoull. The ARM64 core now uses private names for both implementations
and their callers. CI checks the actual archive symbols and every packaged
ELF LOAD segment; it does not allow multiple definitions to bypass the problem.

The static modern-Bionic CLI harness selects API29 native ELF TLS and supplies
a real 64-byte-aligned thread-local witness. Its initial thread sets a value;
the retiring VM worker must see its own zero value. This satisfies Bionic's
ARM64 static TLS geometry and checks thread isolation instead of disabling the
loader check. The delivered APK still targets API21+ and uses the real Android
loader and the core's pthread-key execution context. The CLI harness is not APK
startup evidence or an API21 static-Bionic compatibility claim.

## Downloads and recorded validation

[Build 41354049175](https://github.com/bhgv/Inferno-OS_Android/actions/runs/41354049175)
passes NDK r27c, all bounded host gates, 38 Bionic/QEMU processes with 1096
in-program checks and exact packaged-image runs with JIT0/1.
[Download both signed APKs and logs](https://github.com/bhgv/Inferno-OS_Android/actions/runs/41354049175/artifacts/13102686436).

Install Inferno-FB-arm64-v8a-probe-jit0.apk for the interpreter or
Inferno-FB-arm64-v8a-probe-jit1.apk for JIT. They have distinct application IDs.
Expected screen: PASS: ANDROID ARM64 DIS64. Exact source pins in the archive are
core56f112e and launcher ebfdea0. Both downloaded APKs are genuine ELF64/AArch64,
contain no DEX, retain 16KiB LOAD alignment and match their recorded checksums.
The archive also contains the source, identical bundled Dis64 image, private
source map, NDK revision, signature/ABI results and build/runtime logs.

The retry-state gate deliberately delays worker startup to expose rapid second
taps. The old state transition fails this control; the final launcher clears
failure state before creating a new worker, so a second tap cannot join a live
VM worker. Native window posting pauses when Android removes focus.

Artifacts require a GitHub login and follow the repository retention period.
These successful checks remain separate from the required physical-phone test.
