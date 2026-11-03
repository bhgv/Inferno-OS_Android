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


## Completed target build

Run41588361296 passes at launcher271f22d0db79f47c6a95b53f20eb0be8ce021ffe
and core83b5fb23092f31b7aa2f15d73181fa6c7ebb983a. NDK compiles the complete
Loader consumer. Bionic/QEMU passes all new initializer/PC/public snapshot cases
and controls, previous Draw/binding/module/Sys gates, whole C/JIT processes and
exact packaged images through real VM worker retirement.

Downloaded artifact13209341557; ZIP SHA256db73d14a0e1fa155c4ecdf64cd3b178de465a432c57c5884678ae46ca7b1d2fe
matches GitHub. Verified exact core.txt, APK hashes, no DEX, ELF64/AArch64,
16KiB LOAD and0091 identities. APKs are4621134 bytes each. Probe remains
9138ae33fb041adb8b0b689ad1e5c1420fdb5d86a33f0c4dad6c6e96b05c18e0.

| Mode | APK SHA256 |
|---|---|
| C | 122b46a4ad693a8e2bd354e8bf18158851cd2fca4292cff480883cd9cee38416 |
| JIT | aae361c08107a3ea08023d6c5ecdcc985f4b6eb129f226c112095889e31408d8 |

Download: https://github.com/bhgv/Inferno-OS_Android/actions/runs/41588361296/artifacts/13209341557
These remain scalar FB probes, not physical-phone/complete AWM acceptance.
