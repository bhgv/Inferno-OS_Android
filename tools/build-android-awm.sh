#!/usr/bin/env bash
# Build the NativeActivity and optionally package or test it for the selected ABI.
set -euo pipefail

if [ "$#" -lt 5 ]; then
    echo "Usage: $0 ABI CORE_CHECKOUT NDK HOST_TOOLS BUILD_DIRECTORY [build options]" >&2
    exit 2
fi

abi="$1"
flags=()
case "$abi" in
    armeabi-v7a) ;;
    arm64-v8a)
        flags=(--native64-draw --native64-tk --native64-sys-fixed --native64-formatter --native64-awm)
        ;;
    *)
        echo "Expected ABI armeabi-v7a or arm64-v8a" >&2
        exit 2
        ;;
esac
app_root="$(cd "$(dirname "$0")/.." && pwd -P)"
core_root="$(cd "$2" && pwd -P)"
ndk="$3"
host_tools="$4"
build="$5"
shift 5

exec python3 "$core_root/utils/tests/android-gui-build.py" \
    --app-root "$app_root" --ndk "$ndk" --host-tools "$host_tools" --build-root "$build" \
    --abi "$abi" "${flags[@]}" "$@"
