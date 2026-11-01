# Native Activity lifetime: phone video follow-up

Retain the original FB display and touch coordinates. Handle native configuration
changes without recreating the Activity. If Android actually destroys a running
VM Activity, terminate its process so worker threads cannot retain the former
stack-owned Engine or stale Android context. The next launch creates a fresh VM.

The window test APKs also pin Inferno's independent GLES window-storage fix;
the FB layer remains the standard shared software-screen view. Both preserve
/sdcard/Inferno, reuse an existing ready tree and contain no application Java/DEX.
Physical font appearance, Bounce and repeated phone launch still require device
verification; host tests do not establish their visual outcome.
