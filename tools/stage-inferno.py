#!/usr/bin/env python3
"""Stage only the runtime filesystem, with an index readable through the native asset API."""
import argparse
from pathlib import Path
import shutil

REQUIRED = (
    'dis/emuinit.dis',
    'dis/sh.dis',
    'dis/wm/awm.dis',
    'dis/wm/atoolbar.dis',
    'dis/wm/keyboard.dis',
    'dis/wm/sh.dis',
    'dis/lib/arg.dis',
    'dis/lib/string.dis',
    'dis/lib/wmsrv.dis',
    'dis/lib/wmclient.dis',
    'dis/lib/winplace.dis',
    'dis/lib/tkclient.dis',
    'dis/lib/wmlib.dis',
    'dis/lib/titlebar.dis',
    'lib/awmsetup',
    'fonts/ttf/Vera.ttf',
    'dis/sh/std.dis',
    'fonts/ttf/FantasqueSansMono-Regular.ttf',
)

DIRECTORIES = ('dis', 'lib', 'fonts', 'icons')
OPTIONAL = ('acme', 'locale', 'man', 'module', 'services', 'usr/inferno')
EMPTY = ('chan', 'dev', 'env', 'fd', 'mnt', 'net', 'prog', 'srv', 'tmp', 'usr', 'usr/inferno')


# Keep host sources, archives and toolchains out of the APK; never follow filesystem aliases.
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--source', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--disabled', action='store_true')
    args = parser.parse_args()
    source, output = args.source.resolve(), args.output.resolve()
    if args.disabled:
        if output.exists():
            if not (output/'manifest.txt').is_file():
                raise RuntimeError('Refusing to delete a non-generated asset directory')
            shutil.rmtree(output)
        return
    missing = [name for name in REQUIRED if not (source/name).is_file() or (source/name).stat().st_size == 0]
    if missing:
        raise RuntimeError('Incomplete Android AWM runtime; build appl/alib and appl/awm and install them before packaging: '+', '.join(missing))
    if output == source or source in output.parents or output in source.parents:
        raise RuntimeError('Place generated assets outside the Inferno source tree')
    directories = set(EMPTY)
    files = []
    for name in DIRECTORIES+tuple(name for name in OPTIONAL if (source/name).is_dir()):
        tree = source/name
        if not tree.is_dir():
            raise RuntimeError('Required runtime directory is missing: '+str(tree))
        directories.add(name)
        for path in sorted(tree.rglob('*')):
            relative = path.relative_to(source).as_posix()
            if '\n' in relative or '\r' in relative or path.is_symlink():
                raise RuntimeError('Unsupported runtime asset path: '+str(path))
            if path.is_dir():
                directories.add(relative)
            elif path.is_file():
                files.append((relative, path))
    if output.exists():
        if any(output.iterdir()) and not (output/'manifest.txt').is_file():
            raise RuntimeError('Refusing to replace a non-generated asset directory')
        shutil.rmtree(output)
    output.mkdir(parents=True)
    records = ['D\t'+name for name in sorted(directories)]
    for relative, path in files:
        destination = output/relative
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(path, destination)
        records.append('F\t'+relative)
    (output/'manifest.txt').write_text('\n'.join(records)+'\n', encoding='utf-8')
    print('Staged', len(files), 'runtime assets in', output)


if __name__ == '__main__':
    main()

