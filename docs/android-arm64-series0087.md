# ARM64 framebuffer series 0087

Build pin: Inferno experiment 81385bb23436185ecd5922714899e73a2163e5cb.
This advances the Android core from series0067 through the current result-address,
published LEA/cache, static attachment and public Loader compilation guards.
The APK package, label and shared probe asset destination are versioned0087 so
a prior successful probe image cannot be mistaken for this source.

The classic-mk NDK r27c build retains existing compiler case/helper/result and
exact-packaged-image interpreter/JIT process checks. Two new static ARM64/Bionic
QEMU fixtures compile actual binding and public Loader bodies in WORD32/WORD64.
Binding has 1536 cases per model and three semantic removal controls. Loader has
1024 cases and32 owner/result guards per model and one semantic removal control.
These add Bionic execution evidence; they are not sanitizer checks.

Native-only FB probe APKs still test bounded scalar startup and worker retirement,
not AWM/managed GUI/imports or physical Android presentation. No Java application
code or private runtime tree is added. The runtime path remains /sdcard/Inferno.

Local host launcher tests and shell syntax must pass before publication. NDK/APK
and Bionic results are pending the source-pinned GitHub build; Linux sanitizer
results are separate and do not certify this packaging.

First NDK run41555685980 compiled the current core successfully, then rejected
the new isolated binding fixture: it selected Linux declarations instead of the
Android port declarations (missing Bionic ulong/ushort aliases). The fixture
compiler flags now select the same Android headers and native64 target prelude
as the classic-mk core. Compiler errors are not accepted as semantic controls.
A fresh source-pinned run is required; the failed run produced no APK pair.
