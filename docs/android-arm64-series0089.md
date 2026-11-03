# ARM64 series0089: coherent isolated allocator boundaries

Pin owning experiment619d58bc88d265c5a4c22c96a642b3208ab68d25. It fixes
the module/Sys fixture header mismatch exposed by0088. Object-like Android
allocator aliases are cleared in isolated test units before Type declarations
and libc allocation transports. Production Android headers/allocators are intact.

Builtin module-set tests now explicitly inject port aliases as well as using
the Android port. Existing long-map, staged-failure, publication/retirement,
Sys initializer/registration and I/O/UTF gates remain mandatory. The root
source does not change VM/JIT behavior or the scalar probe image in this series;
APK identities remain0087. This is not an AWM client.

Local host O3 nonrecovering UBSan passes the four affected suites with alias
injection; launcher production-function checks and shell syntax pass. The
previous0088 target run failed compilation, not a semantic control. A new
source-pinned Bionic build is required before target success is reported.


## Completed target evidence

Run41558762745 succeeds at launcher3184e90b9f87afc60da0ae29c8b302ef87619171
and core619d58bc88d265c5a4c22c96a642b3208ab68d25. Actual Bionic builtin sets,
Sys initializer (emu/os, wide/smallmap), registration and I/O/UTF suites pass.
UTF checks1115061 scalar/bounds cases per active model. All previous whole C/JIT
process checks and exact packaged-image runs retire the real VM worker normally.

Downloaded artifact13196446425; ZIP digest43f1b13006897fba3daba80f63f4e9d648db7362c85e45ecbe5c2da00795f6d8
matches GitHub. Both APKs are4617038 bytes, native-only ELF64/AArch64 with16KiB
LOAD alignment. Their shared probe hash remains9138ae33fb041adb8b0b689ad1e5c1420fdb5d86a33f0c4dad6c6e96b05c18e0.
JIT0 APK SHA2560472e217ba4dcead865563a27b8032bcf4399e005bcd045f4139a28346ea467a.
JIT1 APK SHA256208620b0675cf08d144780114cbd54d44441ba7f78048c05d1f1945c0eeefddc.
APK identities remain0087; this is test-fixture portability, not a new GUI app.
Physical-phone acceptance and complete AWM remain separate.
