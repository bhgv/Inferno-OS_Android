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
