#!/usr/bin/env bash
# Build the panel-free native64 AWM NativeActivity against a selected Inferno core.
set -euo pipefail

if [ "$#" -ne 4 ]; then
    echo "Usage: $0 CORE_CHECKOUT NDK HOST_TOOLS BUILD_DIRECTORY" >&2
    exit 2
fi

app_root="$(cd "$(dirname "$0")/.." && pwd -P)"
core_root="$(cd "$1" && pwd -P)"
shift

exec python3 "$core_root/utils/tests/android-gui-build.py" \
    --app-root "$app_root" --ndk "$1" --host-tools "$2" --build-root "$3" \
    --native64-draw --native64-tk --native64-sys-fixed --native64-formatter --native64-awm
