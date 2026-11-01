# Native startup test APKs — 2026-11-01

Both native-only ARM32 APKs were built successfully by the same CI run:
https://github.com/bhgv/Inferno-OS_Android/actions/runs/41314236854

Download archives (each contains one APK, its SHA-256 file and build diagnostics):

- Framebuffer: https://github.com/bhgv/Inferno-OS_Android/actions/runs/41314236854/artifacts/13086648086
- Clutter/GLES: https://github.com/bhgv/Inferno-OS_Android/actions/runs/41314236854/artifacts/13087010173

These Actions artifacts expire on 2026-11-15. The workflow can reproduce fresh
test packages. They are not permanent release assets.

## Inputs and verification

- Core: bhgv/Inferno-OS-bhgv c958911cc2da9ad796638c4df85334d55999ba82.
- Framebuffer launcher: c5a67d0e04305b13de698d893557604576a1a9d5;
  build orchestration: 2bd66b300d686528d2116b53994791acbdad0860.
- GLES launcher: bhgv/Inferno-OS_Android-Clutter3d
  01e113492b8efdf5ca07d5e3edffa0d03489d064.
- NDK r16b, native API17, resource SDK28, classic mk for core/libraries and Limbo modules.
- Separate core builds: framebuffer has EXTWINFLAGS empty; GLES has -DEXT_WIN.
- Each runtime has5365 staged files, including dis/wm/awm.dis, atoolbar.dis,
  keyboard.dis and sh/std.dis.
- Signature schemes v1 and v2 verify; zipalign, ZIP CRC and actual ELF/ABI checks pass.
- No application DEX is present. Java tooling is used on the build host only.
- ABI is armeabi-v7a, ELF32 ARM. These are not ARM64 APKs and cannot run on
  devices that accept only64-bit applications.
- Physical-device installation, GLES rendering and complete desktop startup
  remain for the user's test; compilation/signature checks do not establish them.

## Test behavior

The test package IDs are bhgv.vitanuova.inferno_os.fbtest.startup20261101 and
bhgv.vitanuova.inferno_os.glestest.startup20261101. They are separate from the
previous test IDs and production application. These are generated test signatures.

A complete existing /sdcard/Inferno wins before any APK assets are opened. If its
required phone desktop inputs are missing, bundled provisioning repairs missing
files while preserving existing ones. The Clutter version provisions in a native
worker and shows a progress bar, completed-file counts and failures on its UI
thread. This series does not add a framebuffer extraction progress screen.

Runtime files remain exclusively in /sdcard/Inferno. After preparation, native
VM stdout/stderr append to /sdcard/Inferno/startup.log. If the desktop still
stays gray, inspect that file before treating it as a rendering failure.

## Reproduction details

tools/build-test-apks.sh is the executable build recipe. The legacy Android
emulator all/default recipes recurse; the script requests the concrete emu.a
target instead, then builds libbio/libdynld needed by the launcher. Native
libncurses5/libtinfo5 are installed for the old NDK's host archive/plugin tools.
Clutter's modified Android backend is rebuilt and Inferno's FreeType symbols are
isolated using the existing repository helper.

Actions uploads only APKs, SHA-256 files, provenance and diagnostics. Generated
test keystores are not uploaded. The workflow token has read-only repository
permissions.
