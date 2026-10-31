#!/usr/bin/env python3
"""Configure actual APK CMake ABI selection using host tools and a bounded glue placeholder."""
import os
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


# Configuration only: imported target archives and Android sources are not compiled by this gate.
def main():
    cmake = os.environ.get('CMAKE', 'cmake')
    with tempfile.TemporaryDirectory(prefix='cmake-abis-', dir=ROOT) as directory:
        work = Path(directory)
        glue = work/'ndk/sources/android/native_app_glue'
        glue.mkdir(parents=True)
        (glue/'android_native_app_glue.c').write_text('int fixture_glue;\n')
        tree = work/'Inferno source'
        for abi, arch in (('armeabi-v7a','arm'),('arm64-v8a','arm64'),('x86_64','amd64')):
            build = work/abi
            command = [cmake,'-S',str(ROOT/'app/src/main/cpp'),'-B',str(build),
                       '-DCMAKE_POLICY_VERSION_MINIMUM=3.5','-DANDROID_ABI='+abi,
                       '-DANDROID_NDK='+str(work/'ndk'),'-DINFERNO_ROOT='+str(tree)]
            result = subprocess.run(command,capture_output=True,text=True)
            if result.returncode:
                raise RuntimeError(result.stdout+result.stderr)
            link = (build/'CMakeFiles/inferno_os_app.dir/link.txt').read_text()
            if str(tree/('Android/'+arch+'/lib/emu.a')) not in link:
                raise RuntimeError('Wrong imported archive for '+abi)
            flags = build/'CMakeFiles/inferno_os_app.dir/flags.make'
            if 'INFERNO_BUNDLE_RUNTIME=1' in flags.read_text():
                raise RuntimeError('Provisioning unexpectedly enabled by default')
            subprocess.run(command+['-DINFERNO_BUNDLE_RUNTIME=ON'],check=True,capture_output=True,text=True)
            if 'INFERNO_BUNDLE_RUNTIME=1' not in flags.read_text():
                raise RuntimeError('Provisioning option missing from native compilation')
            print('PASS actual CMake ABI selection:',abi,arch)
        rejected = subprocess.run([cmake,'-S',str(ROOT/'app/src/main/cpp'),'-B',str(work/'bad'),
                                   '-DCMAKE_POLICY_VERSION_MINIMUM=3.5','-DANDROID_ABI=unsupported'],capture_output=True,text=True)
        if rejected.returncode == 0 or 'Unsupported Inferno ABI' not in rejected.stderr:
            raise RuntimeError('Unsupported ABI was not rejected')
        print('PASS unsupported CMake ABI rejection; configuration only, not an APK build')


if __name__ == '__main__':
    main()
