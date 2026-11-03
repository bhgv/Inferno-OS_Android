# ARM64 series0088: managed module boundary on Bionic

Keep the proven0087 core pin81385bb23436185ecd5922714899e73a2163e5cb and
its exact scalar APK image. Add four existing owning-source suites to the real
NDK/Bionic QEMU build, using the production Android declaration and LP64 flags.

* Native builtin construction: generated headers, long maps, atomic module sets,
  staged failure retirement and existing publication/retirement controls.
* Sys initialization: actual descriptor constructors, wide reference maps and
  protected initialization failures.
* Sys registration: actual selected profile construction with observed callback
  identities; this is not real handler execution.
* Sys consumers: compile owning consumers and exercise actual fixed-frame I/O
  and UTF handlers with bounded OS transports.

Host Limbo generates matching native metadata; target binaries are compiled by
NDK r27c and run by qemu-aarch64. Legacy/packed ABI refusal and explicit option
refusal remain active. These tests do not admit new guest imports or establish
full managed file-call/GUI behavior. No runtime or JIT implementation changes
are made by this Android pipeline extension. Existing C/JIT whole-process and
exact packaged-image checks remain required after the new gates.

Local host launcher tests and shell syntax pass. Target execution and APK
packaging are pending fresh CI, not inferred from the successful0087 build.
The APK remains the scalar FB probe; AWM readiness remains separate.
