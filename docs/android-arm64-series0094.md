# ARM64 series 0094: actual native64 Freetype registration

Core pin:2d92a79e658faa9315a2b98e53d81e483d7f2169. Host Limbo -H -M Freetype
now selects actual module declarations and dependent Draw_Point without Sys/
Draw export tables. Complete owning freetype.c uses coherent int32/ref64 frames
and the real builtinmod64 constructor for all six exports.

Before packaging, the Bionic/QEMU gate compiles the real font engine, registers
the module and calls all six Module.ext exports with fresh frames and two real
fonts. It covers21 allocation refusals per WORD32/WORD32-file,
three strict map/frame/retirement controls, header-only/packed refusal, five
invalid build configurations and compiler selection/dependency refusal. Existing
452/453 legacy bridge matrices and six controls remain. ASCII/heap/error/VM
exclusion transports are bounded; no moving-GC or full scheduler-call proof.
newmemface retains its explicit not-implemented result.

Linux gains separate optional --native64-freetype-boot through classic mk.
Android scalar APK startup remains builtin-free: the registration/font test runs
outside the packaged VM using the retained libc file adapter. Package names/
labels/shared scalar path move to0094; runtime stays /sdcard/Inferno. No private
runtime tree or Java application code. These remain scalar FB probes, not AWM.
Host launcher and shell checks pass; fresh target results follow independently.


## Source-specific target result

Android41611575016 succeeds at launcherbbe8202da0572dac7d7bd55887c818ad540bb9a8,
pinning core2d92a79e658faa9315a2b98e53d81e483d7f2169. Native ARM64/x64 address
run41611046071 passes separately at the same core source. Bionic logs confirm
six published exports/21 allocation refusals/two fonts per WORD32 and WORD32-
file, all three strict controls and header-only/packed/compiler/configuration
refusals. Its756 predicates per model include absolute ASCII path checks;
local754/native-CI758/peer748 totals differ only in those path lengths.

Artifact13218929385 ZIP SHA256:
2713c6617e4ab308219aa14506beb0c7cd9b5cbde7e2e3f8eb8050645544f791.
Independent checks cover ZIP integrity, exact core/package IDs, APK sidecars,
ELF64/AArch64,16KiB LOAD,noDEX and unchanged bundled scalar program bytes.
Both APKs are4621134 bytes. JIT0 SHA256:
69a52be848d9672ba74ff863c5fc105d26da5a4b7734e9fe49a3d7430b6f105a.
JIT1 SHA256:
220d9e3ba2c0fe3091ad7bffbedda1968958a482d64e492e3da9578fbc6682e3.
Download: https://github.com/bhgv/Inferno-OS_Android/actions/runs/41611575016/artifacts/13218929385

The module test is separate from packaged VM execution. These remain scalar
FB APKs using /sdcard/Inferno, not full managed GUI/AWM or phone acceptance.
