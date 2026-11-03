# ARM64 series 0094: actual native64 Freetype registration

Core pin:2d92a79e658faa9315a2b98e53d81e483d7f2169. Host Limbo -H -M Freetype
now selects actual module declarations and dependent Draw_Point without Sys/
Draw export tables. Complete owning freetype.c uses coherent int32/ref64 frames
and the real builtinmod64 constructor for all six exports.

Before packaging, the Bionic/QEMU gate compiles the real font engine, registers
the module and calls all six Module.ext exports with fresh frames and two real
fonts. It covers21 allocation refusals/754 predicates per WORD32/WORD32-file,
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
