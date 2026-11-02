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
