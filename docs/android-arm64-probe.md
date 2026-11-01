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


## Device-reported retirement failure and corrected APKs

The first phone logs reproduce `alloc:D2B ... in free blk` after the module
reports `exit=""` and an empty scheduler, in both JIT0 and JIT1. The APKs from
build 41354049175 therefore do not pass complete worker retirement. The old CLI
adapter exited at the splash callback, before production `pexit`, and missed
this failure.

Core commit `0a7cb57f00482117007a49f7f41c718d0075cae3` detaches the worker's
borrowed `Osenv` before `delprog` frees it. Otherwise Android `pexit` reads the
freed environment and frees its user string again. The corrected scheduler
fixture checks the pointer before process free and host exit, instead of
repairing it in the test. Removing the production fix fails the control.

The revised Bionic CLI adapter returns from the completion callback and waits
for actual `pexit` to reach `pthread_exit`. An ARM64/Bionic r16b QEMU replay of
the exact bundled module reproduces the allocator panic with the old core in
both modes; the corrected core exits zero in both modes. Symbolization locates
the old caller in `pexit` at `free(e->user)`. This is runtime cleanup evidence,
not physical Android UI validation.

[Corrected build 41357793945](https://github.com/bhgv/Inferno-OS_Android/actions/runs/41357793945)
passes NDK r27c compilation, host launcher gates, 38 Bionic/QEMU processes with
1096 in-program checks, import refusals and both exact packaged-image runs,
including real worker cleanup. Launcher pin: `9a893441692d3c21ac82df81e34e6660e7915078`.
[Download the corrected APK pair and evidence](https://github.com/bhgv/Inferno-OS_Android/actions/runs/41357793945/artifacts/13103996704).

| APK | SHA256 |
| --- | --- |
| Inferno-FB-arm64-v8a-probe-jit0.apk | ff7610c2ac9512c875b11eea3799c4a3b644993052990ade1a42b47334a5fd6b |
| Inferno-FB-arm64-v8a-probe-jit1.apk | 55f7a00a73ae222cc80fa93e4a4411e53e2f8277c5c7664dbb3ab4d7ba9e99f4 |

Downloaded files match their checksums, contain ELF64/AArch64 native libraries
with 16KiB LOAD alignment, no DEX and the unchanged shared probe image. These
remain scalar framebuffer probes, without AWM. Physical-phone confirmation of
the corrected retirement path is pending.
