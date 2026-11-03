# ARM64 series 0093: checked native Freetype bridges

Pin core efbf604235d57947141f1872034829d12ae81151. Both transform layers now
copy scalar fields rather than casting VM-word/int/native-long layouts. Target
limits, signed font-stream decoding, glyph sizes/pitch/advances/pixel format,
face path OOM/nullable names and return-slot exclusion receive explicit checks.

Before packaging, Bionic/QEMU executes actual-entry WORD32/64 raster/transform/
refusal matrices, native FreeType declarations/stream patterns and five strict
semantic controls. It also compiles the vendored engine and production bridge
to render Vera and Noto with identity, translation and rotation; this separate
executable uses the retained libc I/O adapter, not Inferno's namespace adapter.
All earlier initializer/heap-map/binding/loader/scalar startup gates remain.

Package names, labels and shared scalar path move to 0093. Runtime storage
remains /sdcard/Inferno, with no private runtime copy or Java application code.
These APKs remain scalar FB probes, not the complete Freetype/Draw module ABI
or AWM. Host launcher/shell checks pass; new target results are pending.


## Sorter callback follow-up

Initial Android41601304711 failed before packaging at a retained CFF callback
type mismatch: Clang rejects const-void comparisons passed to Inferno's void-
pointer sorter. No APK was produced. Core696234e28f209de3a0e6f65d5edc1026b0262800
fixes all five real signatures and orders Type1 kerning/PostScript Unicode keys
without narrowing unsigned subtraction. Native boundary checks add72 ordered
key pairs plus a sixth strict restored-subtraction control. Engine compilation
also rejects incompatible pointer types on GCC.

The earlier efbf6042 native ARM64/x64 ASan/UBSan run41601134425 passed actual
rendering and five controls, but does not certify this correction. Local O3
UBSan passes the corrected real engine and actual-record sorting oracle.
Fresh corrected native/Bionic results are pending.
