#!/usr/bin/env python3
"""Reject APKs whose actual native library ABI does not match the intended device."""
import argparse
from pathlib import Path
import struct
import zipfile

ABIS={'armeabi-v7a':(1,40),'arm64-v8a':(2,183),'x86_64':(2,62)}


# Inspect ELF headers instead of trusting the APK filename or its lib directory label.
def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('apk',type=Path)
    parser.add_argument('--abi',choices=tuple(ABIS),required=True)
    args=parser.parse_args()
    found=[]
    with zipfile.ZipFile(args.apk) as archive:
        for name in archive.namelist():
            if name.startswith('lib/') and name.endswith('.so'):
                with archive.open(name) as source:
                    header=source.read(20)
                if len(header)!=20 or header[:4]!=b'\x7fELF' or header[5] not in (1,2):
                    parser.error('Invalid ELF header: '+name)
                machine=struct.unpack(('<' if header[5]==1 else '>')+'H',header[18:20])[0]
                if header[4:5]==bytes([ABIS[args.abi][0]]) and machine==ABIS[args.abi][1] and name.startswith('lib/'+args.abi+'/'):
                    found.append(name)
    if 'lib/'+args.abi+'/libinferno_os_app.so' not in found:
        parser.error('APK has no actual '+args.abi+' native library; incompatible with the selected device')
    print('PASS actual APK ABI:',args.abi,', '.join(found))


if __name__=='__main__':
    main()
