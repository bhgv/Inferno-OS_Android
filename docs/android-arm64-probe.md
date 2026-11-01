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
