# ARM32 window ownership test, 2026-11-02

Use Inferno core experiment 1b66f1e52af8dbf4ba5ceb32d1e96dcf457dfe01 or later. The core fixes two confirmed issues:
Tk.toplevel reused the process's existing window instead of creating a new
namespace, producing `.Wm_t` already-exists errors in debugger/dialog windows;
Draw.Display.allocate returned a cached display without retaining it. The first
live top remains the primary #G root, and weak ownership is resolved by PID.

Both FB and GLES APKs include this corrected core and bundled AWM files. Runtime
execution remains /sdcard/Inferno; complete existing trees are reused unchanged.
No private runtime directory or application Java/DEX is added. The new test
application IDs end in windowfix20261102, so they can coexist with older test
APKs signed by earlier ephemeral CI keys. Open the newly dated test icon.

GLES retains its renderer-specific canvas/input transform, immutable per-window
buffers and separate Inferno/Clutter FreeType implementations. FB retains its
identity pixel/touch path. Host input, geometry, lifecycle, storage, clipping and
FreeType tests pass; these are not physical-phone GUI acceptance. Startup logs
identify the native renderer and this ownership-fix revision. Test the original
additional-window scenario and Bounce, then retain /sdcard/Inferno/startup.log
and backtrace.log if a separate device failure remains.


## Verified ARM32 APKs, 2026-11-02

[Build41374740439](https://github.com/bhgv/Inferno-OS_Android/actions/runs/41374740439)
passes both renderers. Core pin:f9ea7ac0d47bfe16573fd77f99ca9c5e2f76d5da;
FB launcher:638710fd24be56ef8aee2bade350a941f8eb6990;
GLES launcher:284c5ecc837a9fec292a136173d23d7a77194fcc.

| Renderer | Signed APK and build evidence | APK SHA256 |
| --- | --- | --- |
| FB | [Download](https://github.com/bhgv/Inferno-OS_Android/actions/runs/41374740439/artifacts/13111125768) | 4df36635fdae1a440cc705c6c463bda4070219fe47983ab147753c18c8457ac8 |
| GLES/Clutter | [Download](https://github.com/bhgv/Inferno-OS_Android/actions/runs/41374740439/artifacts/13110612907) | 400e0f7c55952e6aa08414212d82829d8041e28a27c36111a7510a6e01a58ac6 |

The downloaded APKs match their hashes, contain actual ELF32/ARM native
libraries, no DEX and the required AWM runtime. CI verifies APK v1/v2 signatures
and ZIP alignment. Application IDs end in windowfix20261102 and versionName is
windowfix-2026-11-02; open the newly installed dated test application.

Each renderer's build passes14160 ownership cases in each host WORD64/WORD32
model under UBSan/NDEBUG. Separate static Bionic/API17 ARM32 fixtures run33
constructor/display cases under qemu-arm, with both old-fault controls active.
These are actual ARM32 pointer layouts with bounded native window adapters,
not execution of an Android GUI. Explicit Android headers and API17 are selected
for these cross fixtures; native adapter allocation uses libc consistently.

FB pixel/lifecycle/startup/storage gates pass. GLES input/geometry checks3312
predicates; startup/UI-thread/clip/storage gates pass. Both private and renderer
FT_Init_FreeType implementations are defined separately in the downloaded GLES
APK (inferno_private_FT_Init_FreeType versus FT_Init_FreeType), matching the
host private-FreeType link control. This preserves renderer-specific transforms.

Repeat the photographed debugger additional-window scenario and Bounce on the
phone. Physical rendering, font appearance and all device-specific crash paths
are not established by host/QEMU ownership fixtures. Existing /sdcard/Inferno
files remain reusable; no private runtime tree or extraction migration is needed.
GitHub artifacts require login and follow14-day repository retention.
