# Android shared-tree reuse and phone desktop checks

The phone desktop entry is `/sdcard/Inferno/dis/wm/awm.dis`, not a root-level
`awm` directory. It launches `dis/wm/atoolbar.dis`; toolbar setup is `lib/awmsetup`.
Build and install `appl/alib` and `appl/awm` with classic mk before staging the
runtime. The packager now rejects a missing/empty AWM, toolbar, keyboard, shell,
core UI library or required phone font before replacing generated assets.
This verifies presence, not bytecode ABI compatibility or device execution.

Native startup checks the required shared files and namespace directories first.
If they are present and accessible, it uses that tree immediately: no APK manifest
open, no APK traversal, no extraction and no overwrite. A ready user tree also
wins over an absent/corrupt bundled manifest. Existing startup settings are kept.
The root remains exclusively `/sdcard/Inferno`; there is no private-tree fallback.

If the tree is incomplete, the optional bundled installer validates the full
manifest and its required UI entries before copying files. Existing files remain
untouched; missing files are written through temporary files. An existing empty
or incompatible file is not silently overwritten. File progress counts include
already-present entries traversed during repair and are monotonic. Cancellation
is checked between entries and retries can complete a partially extracted tree.
A callback API reports current/total entries and the current path.

The Clutter repository uses that callback from a separate pthread. Its UI thread
polls status and draws percentage, counts and a bar, keeping the native event loop
responsive. It displays extraction failure and does not launch the VM after a
failed install. Closing the stage cancels provisioning; the worker is joined before
the enclosing native application loop returns. All actor calls remain on the UI
thread. The framebuffer launcher receives the shared-tree fast path and runtime
checks; this patch does not add its own framebuffer progress screen.

After successful preparation, native VM stdout/stderr append to
`/sdcard/Inferno/startup.log`. They are not a private runtime copy. Android logcat
logging remains available through explicit Android logging calls. Extraction
errors occur before VM logging starts; Clutter shows their failure status, and
the native installer prints the offending path to its current stderr/log sink.

Host validation covers the actual installer with real files and an asset-manager
adapter: ready-tree zero-asset-open reuse, preservation, repair, cancellation,
progress counts, bad manifests and missing-AWM preflight. Separate child processes
exercise actual append-only native log redirection. Clutter worker tests use real
pthreads with thread-checking bounded actor calls; they do not prove GLES rendering
or activity lifecycle behavior on a physical Android device. No replacement APK
or device boot is claimed by these source tests.
