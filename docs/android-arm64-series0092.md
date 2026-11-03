# ARM64 series0092: native font roots and graphical factories

Pin core05591a391106947421f7e1a0a148b23789fa2397. Native Freetype maps now
use actual public fields. For LP64 WORD32/ref64, Face names need0x18 (not private
FT-handle bits0x06), and Glyph.bitmap needs0x10 (not out-of-record0x02).
Prefab/Freetype stage all maps/Types and roll back allocation/registration
refusal with preserved diagnostics. Tk and FT rendering code are unchanged.

Bionic/QEMU adds Prefab14/Freetype23 initialization cases per WORD model, eight
strict controls including restoring stale font maps, and1072 actual heap/map/
copy/alias/release cases per model. Registration/native graphics/FT destructor
boundaries remain injected in these fixtures. Legacy heap-map LSan opt-out is
retained; other new initializer fixtures do not opt out. NDEBUG predicates stay
active. Fresh classic host-Limbo tables support full-consumer syntax checks;
Prefab stays absent from default OFILES. Freetype remains compiled by classic mk.

Package/label/shared path and APK names become0092. The same bundled scalar
program remains under /sdcard/Inferno, with no private runtime tree or Java app
source. These remain scalar FB probes, not native FT rendering/full AWM.

Host launcher and shell checks pass. Fresh target results are pending; no0091
result certifies this change. Full module/file-call ABI admission stays separate.

## Corrected map-fixture boundary

First run41594788023 compiled full consumers and passed initializer/maps and
eight strict controls, then failed the legacy heap-map fixture: Android lib9
allocator aliases renamed Type.free before its function-like tracker. No APK
success is claimed from that run. Pin corrected core143fd9c218ea02ea106a64cc5b9b4a1fe4dc8347;
only test alias handling changes from production05591a39. Host synthetic-alias
UBSan passes both1072-case map models and initializer modules. A fresh Bionic
build is required; source production fixes and0092 package identities stay.


## Corrected target result

Android41596693062 succeeds at launcher8d853fb5e16c636012756bee71f5c33b09f6c95e,
pinning core143fd9c218ea02ea106a64cc5b9b4a1fe4dc8347. Artifact13212528423 ZIP
SHA2561b04fdb98d87d1cd5fbfa334d463f8534db39825f7d6d83ac211724b320e44a5
was independently checked, including integrity, both APK sidecars, exact core
pin, ELF64/AArch64, 16KiB LOAD alignment, no DEX and unchanged scalar bytes.
Both APKs are4621134 bytes. JIT0 SHA256:
c9f65348f5a173737f12e4a5470b7f3a637d5c82de1660169d6c08fec3ee2c09.
JIT1 SHA256:
72d062568dcc33af16a33aadd74c619ac738d957c3c4956a861b3a8a8d4963fd.
These are scalar probes, not AWM/physical-phone GUI certification.
