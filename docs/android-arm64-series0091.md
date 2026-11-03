# ARM64 series0091: Loader descriptor and native-PC snapshot ownership

Pin core83b5fb23092f31b7aa2f15d73181fa6c7ebb983a. Production Loader now
stages three descriptor Types before checked registration, rolls back failures
and preserves diagnostics while Sys retains independent ownership. Shared
loaderpc validates native branch/export target geometry before forming indices.
No target is dereferenced or snapshot field changed on refusal.

NDK compiles the full Loader consumer. Static Bionic/QEMU additionally executes:
15 initializer failure/retry/partial cases per WORD model and three controls;
2800 native-index opcode/shape cases per model (99 conversions/429 refusals)
with >4GiB pointers and width/bounds controls;304 public snapshot cases per
model including18 real partial-array/string cleanup refusals. Sys init and
registration are injected boundaries in the initializer fixture. Public snapshot
fixture retains its legacy LSan opt-out; tracked ownership and ASan bounds are
separate from LSan certification. NDEBUG predicates remain active.

Package/label/shared image path and APK names are0091. Bundled scalar probe
source stays unchanged. Runtime storage remains /sdcard/Inferno with no private
tree or Java application source. This remains a scalar FB probe, not full AWM.

Local optimized UBSan, full Loader syntax, host launcher and shell checks pass.
Fresh target build results are pending;0090 success does not certify0091.
