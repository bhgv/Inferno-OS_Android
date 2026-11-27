#!/usr/bin/env bash
# Build the native64 AWM NativeActivity against a selected Inferno core.
set -euo pipefail

if [ "$#" -ne 4 ]; then
    echo "Usage: $0 CORE_CHECKOUT NDK HOST_TOOLS BUILD_DIRECTORY" >&2
    exit 2
fi

exec "$(dirname "$0")/build-android-awm.sh" arm64-v8a "$@"
