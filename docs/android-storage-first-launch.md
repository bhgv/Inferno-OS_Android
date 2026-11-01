# Native first-launch shared storage

Both clients use only `/sdcard/Inferno`. A complete existing AWM tree bypasses APK traversal. Missing required files trigger bundled installation, preserving existing regular files. Required files and namespace directories are validated before VM startup.

`EACCES` (13) before extraction means Android refused filesystem access. Declaring permissions does not grant them. In Android Settings, open the installed test application's permissions and grant Files/Storage. On Android versions exposing it, also inspect Special app access / All files access. Close and reopen the application after granting access. No Java source, DEX, JNI permission requester, or private runtime fallback is added. Availability and wording of permission controls depend on Android version and manufacturer; installation tests cannot establish a device permission grant.

GLES now distinguishes permission denial from an incomplete tree, displays instructions below the content inset and reports the root path before the first mkdir. FB draws asset-independent native text and percentage progress before the VM framebuffer exists, so a root permission failure is visible rather than a blank screen. FB extraction currently runs on the native event thread; the progress image is posted directly and does not imply responsive input during installation.

Tests inject EACCES before any APK read, retry after removing the denial, validate creation of the AWM tree, existing-tree reuse, missing assets, cancellation and partial-file cleanup. The Clutter controller runs under a thread-checking toolkit adapter; the FB font renderer runs with guarded buffers and padded strides. These are host tests, not Android device execution.

The test APK package suffix `storage20261101` separates this build's generated signing key from previous test APKs. Builds contain the runtime and retain target SDK 28. Physical-device confirmation of storage permissions and first launch remains required.
