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
