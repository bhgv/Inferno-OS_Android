#!/usr/bin/env bash
# Build the real ARM64/Bionic core with classic mk, then package isolated native framebuffer probes.
set -euo pipefail
workspace="$(pwd)"
work="${RUNNER_TEMP:-$workspace/.build}/inferno-arm64-probe"
out="$workspace/apk-arm64-output"
mkdir -p "$work" "$out"
exec > >(tee "$out/build.log") 2>&1
export TMPDIR="$work/tmp"
mkdir -p "$TMPDIR"
core="$work/core"
ndk="$work/android-ndk-r27c"
if [ ! -d "$ndk" ]; then
    curl -fsSL --retry 3 https://dl.google.com/android/repository/android-ndk-r27c-linux.zip -o "$work/ndk.zip"
    unzip -tq "$work/ndk.zip" >/dev/null
    unzip -q "$work/ndk.zip" -d "$work"
fi
grep 'Pkg.Revision = 27.2.12479018' "$ndk/source.properties"
cp "$ndk/source.properties" "$out/ndk.txt"
git clone --depth 1 --branch experiment https://github.com/bhgv/Inferno-OS-bhgv.git "$core"
git -C "$core" fetch --depth 1 origin 619d58bc88d265c5a4c22c96a642b3208ab68d25
git -C "$core" checkout --detach FETCH_HEAD
mkdir -p "$work/host-tools"
(cd "$core"; MKBOOTSTRAP_LIMBO=1 MKBOOTSTRAP_BINDIR="$work/host-tools" sh makemk.sh)
printf '#!/bin/sh\nexec date +%%s\n' > "$work/host-tools/ndate"
chmod +x "$work/host-tools/ndate"
export PATH="$work/host-tools:$PATH"
python3 "$core/utils/tests/configure.py"
python3 "$core/utils/configure.py" --host linux --target android --arch arm64 --renderer framebuffer \
    --native64-scalar-boot --ndk "$ndk" --root "$core" --output "$core/mkconfig"
mkdir -p "$core/Android/arm64/bin" "$core/Android/arm64/lib"
for tool in mk limbo iyacc decgen; do ln -s "$work/host-tools/$tool" "$core/Android/arm64/bin/$tool"; done
(cd "$core/emu/Android"; mk CONF=emu-scalar "$core/Android/arm64/lib/emu.a" KERNDATE=1793577600)
llvm="$ndk/toolchains/llvm/prebuilt/linux-x86_64/bin"
python3 tests/arm64-probe.py
# Execute the actual current binding/loader bodies against Bionic, independently of APK startup.
# These static fixtures cover both WORD models but do not imply shared WORD64 wire execution.
export CC="$llvm/aarch64-linux-android29-clang"
export NATIVE64_ARCH=arm64
export NATIVE64_RUNNER=qemu-aarch64
export NATIVE64_CFLAGS="-O3 -g -DNDEBUG -fno-strict-aliasing -static -DANDROID -DLINUX_ARM64 -include $core/include/native64-target.h -I$core/Android/arm64/include -I$core/Android/arm/include"
python3 "$core/utils/tests/native64-disc-binding.py" | tee "$out/bionic-binding.log"
for control in mode jit image; do
    python3 "$core/utils/tests/native64-disc-binding.py" --control "$control" | tee -a "$out/bionic-binding.log"
done
python3 "$core/utils/tests/native64-loader-mode.py" | tee "$out/bionic-loader-mode.log"
python3 "$core/utils/tests/native64-loader-mode.py" --control | tee -a "$out/bionic-loader-mode.log"
# Exercise the native64 module/managed-descriptor boundary on Bionic before GUI admission.
# Registration identity tests and actual Sys handler tests are separate evidence.
export NATIVE64_LIMBO="$work/host-tools/limbo"
python3 "$core/utils/tests/native64-builtins.py" --sets --port-aliases | tee "$out/bionic-builtins.log"
python3 "$core/utils/tests/native64-sys-init.py" --limbo "$NATIVE64_LIMBO" | tee "$out/bionic-sys-init.log"
python3 "$core/utils/tests/native64-sys-register.py" --limbo "$NATIVE64_LIMBO" | tee "$out/bionic-sys-register.log"
python3 "$core/utils/tests/native64-sys.py" --limbo "$NATIVE64_LIMBO" | tee "$out/bionic-sys.log"
unset NATIVE64_LIMBO
unset CC NATIVE64_ARCH NATIVE64_RUNNER NATIVE64_CFLAGS
"$llvm/llvm-nm" -g --defined-only "$core/Android/arm64/lib/lib9.a" > "$out/converter-symbols.txt"
python3 - "$out/converter-symbols.txt" <<'PYCORE'
from pathlib import Path
import sys
symbols={line.split()[-1] for line in Path(sys.argv[1]).read_text().splitlines() if len(line.split())>=3}
if not {'inferno_strtoll','inferno_strtoull'}<=symbols or {'strtoll','strtoull'}&symbols:
    raise RuntimeError('Inferno must not interpose on Bionic integer converters')
print('PASS private ARM64 integer converter symbols; Bionic standard entries remain independent')
PYCORE
# Only log-daemon/symbolization/CLI-completion adapters are substituted; the Bionic core and JIT are real.
"$llvm/aarch64-linux-android29-clang" -static -fno-emulated-tls tests/arm64-probe-cli.c \
    -Wl,--start-group "$core/Android/arm64/lib/"*.a -Wl,--end-group -Wl,--wrap=pthread_exit -lm -o "$work/bionic-cli"
python3 "$core/utils/tests/native64-scalar-boot.py" --root "$core" --emu "$work/bionic-cli" \
    --runner qemu-aarch64 | tee "$out/bionic-runtime.log"
# Execute the current compiler's actual case/helper/result images on the real ARM64/Bionic VM.
python3 "$core/utils/tests/dis64-cases.py" --limbo "$work/host-tools/limbo" \
    --root "$core" --emu "$work/bionic-cli" --runner qemu-aarch64 | tee "$out/bionic-cases.log"
python3 "$core/utils/tests/dis64-inline.py" --limbo "$work/host-tools/limbo" \
    --root "$core" --emu "$work/bionic-cli" --runner qemu-aarch64 | tee "$out/bionic-helpers.log"
python3 "$core/utils/tests/dis64-setup-targets.py" | tee "$out/compiler-setup-targets.log"
assets="$work/assets"
mkdir -p "$assets/native64"
python3 "$core/utils/dis64-locations.py" compile --limbo "$work/host-tools/limbo" \
    --source app/src/main/cpp/arm64-probe/probe.b --image "$assets/native64/probe.dis64" --map "$out/probe.locations.json"
cp app/src/main/cpp/arm64-probe/probe.b "$out/"
cp "$assets/native64/probe.dis64" "$out/"
# Run the exact packaged image through both execution modes before signing either APK.
cp "$assets/native64/probe.dis64" "$core/probe-apk.dis64"
python3 - "$core" "$work/bionic-cli" <<'PY'
from pathlib import Path
import runpy,sys
root=Path(sys.argv[1]);binary=Path(sys.argv[2])
execute=runpy.run_path(str(root/'utils/tests/native64-scalar-boot.py'))['execute']
for jit in (0,1):
    output=execute(['qemu-aarch64',str(binary),'-v','-r',str(root),'-c',str(jit),'-d','/probe-apk.dis64'])
    print(output)
    if 'native64 scalar module Native64AndroidProbe: jit='+str(jit)+', exit=""' not in output or 'native64 scalar scheduler empty after program retirement' not in output:
        raise RuntimeError('The packaged Bionic image did not retire correctly')
print('PASS exact packaged Android ARM64 image with interpreter and JIT')
PY
sdk="${ANDROID_HOME:?GitHub Android SDK is required}"
readarray -t sdk_files < <(python3 - "$sdk" <<'PY'
from pathlib import Path
import sys,re
root=Path(sys.argv[1])
key=lambda path:[int(n) for n in re.findall(r"\d+",path.parent.name)]
print(sorted(root.glob('build-tools/*/aapt'),key=key)[-1].parent)
print(sorted(root.glob('platforms/*/android.jar'),key=key)[-1])
PY
)
buildtools="${sdk_files[0]}"
jar="${sdk_files[1]}"
keytool -genkeypair -noprompt -keystore "$work/test.jks" -storepass android -keypass android \
    -alias androiddebugkey -dname 'CN=Inferno ARM64 probe' -keyalg RSA -keysize 2048 -validity 3650 -storetype JKS
for jit in 0 1; do
    native="$work/native-$jit"
    cmake -S app/src/main/cpp/arm64-probe -B "$native" -G Ninja \
        -DCMAKE_TOOLCHAIN_FILE="$ndk/build/cmake/android.toolchain.cmake" -DANDROID_ABI=arm64-v8a \
        -DANDROID_PLATFORM=android-21 -DANDROID_STL=c++_static -DINFERNO_ROOT="$core" \
        -DINFERNO_PROBE_JIT="$jit" -DCMAKE_BUILD_TYPE=Debug
    cmake --build "$native" --parallel 2
    "$llvm/llvm-readelf" -l "$native/libinferno_os_app.so" > "$out/elf-jit$jit.txt"
    python3 - "$native/libinferno_os_app.so" <<'PYELF'
from pathlib import Path
import struct,sys
image=Path(sys.argv[1]).read_bytes()
if image[:6]!=b'\x7fELF\x02\x01' or struct.unpack_from('<H',image,18)[0]!=183:
    raise RuntimeError('Expected little-endian AArch64 ELF64')
start=struct.unpack_from('<Q',image,32)[0]
size,count=struct.unpack_from('<HH',image,54)
loads=[struct.unpack_from('<Q',image,start+i*size+48)[0] for i in range(count) if struct.unpack_from('<I',image,start+i*size)[0]==1]
if not loads or any(value<16384 for value in loads):
    raise RuntimeError('APK native LOAD segments must retain 16KiB alignment')
print('PASS AArch64 ELF64 with 16KiB native LOAD alignment')
PYELF
    package="$work/package-$jit"
    mkdir -p "$package/lib/arm64-v8a"
    cp "$native/libinferno_os_app.so" "$package/lib/arm64-v8a/"
    python3 - "$jit" "$work/AndroidManifest.xml" <<'PY'
from pathlib import Path
import sys,xml.etree.ElementTree as E
jit,destination=sys.argv[1:]
E.register_namespace('android','http://schemas.android.com/apk/res/android')
tree=E.parse('app/src/main/cpp/arm64-probe/AndroidManifest.xml');root=tree.getroot();a='{http://schemas.android.com/apk/res/android}'
root.set('package','bhgv.vitanuova.inferno_os.arm64fbprobe.series0087.jit'+jit)
root.find('application').set(a+'label','Inferno ARM64 0087 '+('JIT' if jit=='1' else 'C'))
tree.write(destination,encoding='utf-8',xml_declaration=True)
PY
    "$buildtools/aapt" package -f -M "$work/AndroidManifest.xml" -S app/src/main/res -A "$assets" -I "$jar" \
        --min-sdk-version 21 --target-sdk-version 28 -F "$work/unsigned-$jit.apk"
    (cd "$package"; zip -q -0 "$work/unsigned-$jit.apk" lib/arm64-v8a/libinferno_os_app.so)
    "$buildtools/zipalign" -f 4 "$work/unsigned-$jit.apk" "$work/aligned-$jit.apk"
    apk="$out/Inferno-FB-arm64-v8a-series0087-jit$jit.apk"
    java -jar "$buildtools/lib/apksigner.jar" sign --ks "$work/test.jks" --ks-key-alias androiddebugkey \
        --ks-pass pass:android --key-pass pass:android --out "$apk" "$work/aligned-$jit.apk"
    java -jar "$buildtools/lib/apksigner.jar" verify --verbose "$apk"
    "$buildtools/zipalign" -c 4 "$apk"
    python3 tools/verify-apk-abi.py "$apk" --abi arm64-v8a
    "$buildtools/aapt" dump badging "$apk" > "$out/badging-jit$jit.txt"
    sha256sum "$apk" > "$apk.sha256"
done
python3 - "$out" <<'PY'
import sys,zipfile
from pathlib import Path
for apk in Path(sys.argv[1]).glob('*.apk'):
    with zipfile.ZipFile(apk) as z:
        if z.testzip() is not None or any(n.endswith('.dex') for n in z.namelist()):
            raise RuntimeError('Invalid native-only APK')
        if not z.getinfo('assets/native64/probe.dis64').file_size:
            raise RuntimeError('Missing checked probe image')
print('PASS signed native-only ARM64 framebuffer APKs; physical Android launch remains a device check')
PY
git -C "$core" rev-parse HEAD > "$out/core.txt"
git rev-parse HEAD > "$out/launcher.txt"
