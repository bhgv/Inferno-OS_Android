#!/usr/bin/env bash
# Build native-only ARM32 test APKs without invoking the recursive Android emulator default target.
set -euo pipefail
variant="${1:?Expected fb or gles}"
case "$variant" in fb|gles) ;; *) exit 2 ;; esac
workspace="$(pwd)"
work="${RUNNER_TEMP:-$workspace/.build}/inferno-apk-$variant"
out="$workspace/apk-output"
mkdir -p "$work" "$out"
exec > >(tee "$out/build-$variant.log") 2>&1
export TMPDIR="$work/tmp"
mkdir -p "$TMPDIR"
sdk="$work/sdk"
mkdir -p "$sdk"
curl -fsSL --retry 3 https://dl.google.com/android/repository/android-ndk-r16b-linux-x86_64.zip -o "$work/ndk.zip"
unzip -tq "$work/ndk.zip" >/dev/null
unzip -q "$work/ndk.zip" -d "$work"
ndk="$work/android-ndk-r16b"
python3 "$ndk/build/tools/make_standalone_toolchain.py" --arch arm --api 17 --install-dir "$work/toolchain"
curl -fsSL --retry 3 https://dl.google.com/android/repository/build-tools_r28.0.3-linux.zip -o "$work/build-tools.zip"
echo "ea6f2f7103cd9da9ff0bdf6e37fbbba548fa4165  $work/build-tools.zip" | sha1sum -c -
unzip -q "$work/build-tools.zip" -d "$sdk"
curl -fsSL --retry 3 https://dl.google.com/android/repository/android-17_r03.zip -o "$work/platform.zip"
echo "dbe14101c06e6cdb34e300393e64e64f8c92168a  $work/platform.zip" | sha1sum -c -
unzip -q "$work/platform.zip" -d "$sdk/platform"
buildtools="$sdk/android-9"
export LD_LIBRARY_PATH="$buildtools/lib64:${LD_LIBRARY_PATH:-}"
core="$work/core"
git clone --depth 1 --branch experiment https://github.com/bhgv/Inferno-OS-bhgv.git "$core"
git -C "$core" fetch --depth 1 origin c958911cc2da9ad796638c4df85334d55999ba82
git -C "$core" checkout --detach FETCH_HEAD
mkdir -p "$work/host-tools"
(cd "$core"; MKBOOTSTRAP_LIMBO=1 MKBOOTSTRAP_BINDIR="$work/host-tools" sh makemk.sh)
printf '#!/bin/sh\nexec date +%%s\n' > "$work/host-tools/ndate"
chmod +x "$work/host-tools/ndate"
export PATH="$work/host-tools:$work/toolchain/bin:$PATH"
ln -s "$work/toolchain" "$core/ndk_toolchain"
renderer=framebuffer
if [ "$variant" = gles ]; then renderer=gles; fi
python3 "$core/utils/configure.py" --host linux --target android --arch arm --root "$core" --renderer "$renderer" --output "$core/mkconfig"
mkdir -p "$core/Android/arm/bin" "$core/Android/arm/lib" "$core/dis/lib" "$core/dis/wm" "$core/dis/sh"
for tool in mk limbo iyacc decgen; do ln -sf "$work/host-tools/$tool" "$core/Android/arm/bin/$tool"; done
# The legacy Android all/default recipes recurse; request the actual archive explicitly.
(cd "$core/emu/Android"; mk "$core/Android/arm/lib/emu.a" KERNDATE=1793556000)
# Keep the standard compiler/install rules while excluding unrelated optional subprojects.
for directory in appl/alib appl/cmd appl/cmd/sh appl/awm; do
  (cd "$core/$directory"; mk install DIRS=)
done
app="$workspace"
if [ "$variant" = gles ]; then
  app="$work/gles"
  git clone --depth 1 https://github.com/bhgv/Inferno-OS_Android-Clutter3d.git "$app"
  git -C "$app" fetch --depth 1 origin 01e113492b8efdf5ca07d5e3edffa0d03489d064
  git -C "$app" checkout --detach FETCH_HEAD
  tar --no-same-owner -xzf "$app/install.tgz" -C "$app"
  python3 "$app/tools/rebuild-android-backends.py" --cc "$work/toolchain/bin/arm-linux-androideabi-gcc" --ar "$work/toolchain/bin/arm-linux-androideabi-ar"
  native="$app/app/jni"
  resources="$app/app/res"
  manifest="$app/app/AndroidManifest.xml"
else
  native="$app/app/src/main/cpp"
  resources="$app/app/src/main/res"
  manifest="$app/app/src/main/AndroidManifest.xml"
fi
python3 "$app/tests/native-storage.py"
python3 "$app/tests/startup-log.py"
if [ "$variant" = gles ]; then python3 "$app/tests/startup-progress.py"; fi
assets="$work/assets"
python3 "$app/tools/stage-inferno.py" --source "$core" --output "$assets/inferno"
cmake -S "$native" -B "$work/native" -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$ndk/build/cmake/android.toolchain.cmake" \
  -DANDROID_ABI=armeabi-v7a -DANDROID_PLATFORM=android-17 \
  -DANDROID_TOOLCHAIN=gcc -DANDROID_STL=gnustl_static \
  -DINFERNO_ROOT="$core" -DCLUTTER_PREFIX="$app/install" \
  -DINFERNO_BUNDLE_RUNTIME=ON -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_NM=/usr/bin/nm
cmake --build "$work/native" --parallel 2
mkdir -p "$work/package/lib/armeabi-v7a"
cp "$work/native/libinferno_os_app.so" "$work/package/lib/armeabi-v7a/"
python3 - "$manifest" "$work/AndroidManifest.xml" "$variant" <<'PY'
import sys,xml.etree.ElementTree as E
source,destination,variant=sys.argv[1:]
E.register_namespace('android','http://schemas.android.com/apk/res/android')
tree=E.parse(source);root=tree.getroot();a='{http://schemas.android.com/apk/res/android}'
root.set('package','bhgv.vitanuova.inferno_os.'+variant+'test.startup20261101')
root.set(a+'versionCode','20261101')
root.set(a+'versionName','startup-2026-11-01')
for node in root.iter():
    if node.tag in ('application','activity'):node.set(a+'label','Inferno '+variant.upper()+' startup test')
tree.write(destination,encoding='utf-8',xml_declaration=True)
PY
jar="$(find "$sdk/platform" -name android.jar -print -quit)"
"$buildtools/aapt" package -f -M "$work/AndroidManifest.xml" -S "$resources" -A "$assets" -I "$jar" \
  --min-sdk-version 14 --target-sdk-version 28 -F "$work/unsigned.apk"
(cd "$work/package"; zip -q -0 "$work/unsigned.apk" lib/armeabi-v7a/libinferno_os_app.so)
"$buildtools/zipalign" -f 4 "$work/unsigned.apk" "$work/aligned.apk"
keytool -genkeypair -noprompt -keystore "$work/test.jks" -storepass android -keypass android \
  -alias androiddebugkey -dname 'CN=Inferno native test' -keyalg RSA -keysize 2048 -validity 3650 -storetype JKS
apk="$out/Inferno-$variant-armeabi-v7a-startup-with-runtime.apk"
java -jar "$buildtools/lib/apksigner.jar" sign --ks "$work/test.jks" --ks-key-alias androiddebugkey \
  --ks-pass pass:android --key-pass pass:android --out "$apk" "$work/aligned.apk"
java -jar "$buildtools/lib/apksigner.jar" verify --verbose "$apk"
"$buildtools/zipalign" -c 4 "$apk"
python3 "$app/tools/verify-apk-abi.py" "$apk" --abi armeabi-v7a
python3 - "$apk" <<'PY'
import sys,zipfile
with zipfile.ZipFile(sys.argv[1]) as z:
    if z.testzip() is not None:raise RuntimeError('Invalid ZIP CRC')
    if any(n.endswith('.dex') for n in z.namelist()):raise RuntimeError('Native APK must contain no application DEX')
    for path in ('dis/emuinit.dis','dis/wm/awm.dis','dis/wm/atoolbar.dis','dis/wm/keyboard.dis','dis/sh/std.dis'):
        if z.getinfo('assets/inferno/'+path).file_size==0:raise RuntimeError('Empty runtime entry: '+path)
print('PASS signed native-only APK; phone AWM entries included; Android device testing remains required')
PY
sha256sum "$apk" > "$apk.sha256"
"$buildtools/aapt" dump badging "$apk" > "$out/badging-$variant.txt"
git -C "$core" rev-parse HEAD > "$out/core-$variant.txt"
git -C "$app" rev-parse HEAD > "$out/launcher-$variant.txt"
