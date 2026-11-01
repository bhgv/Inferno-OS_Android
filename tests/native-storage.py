#!/usr/bin/env python3
"""Check actual C installation with real files and a bounded host asset-manager adapter."""
import ctypes as C
import runpy
import os
from pathlib import Path
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
HEADER = '''#ifndef TEST_ASSET_MANAGER_H
#define TEST_ASSET_MANAGER_H // Bounded host adapter, not the NDK's structure layout.
#include <sys/types.h>
#include <stddef.h>
typedef struct AAssetManager {
    const char *base; // Host directory containing staged asset files.
} AAssetManager;
typedef struct AAsset AAsset;
#define AASSET_MODE_STREAMING 2 // Mode accepted by the actual installer's read path.
#define AASSET_MODE_BUFFER 3 // Mode accepted for the bounded manifest read.
AAsset *AAssetManager_open(AAssetManager*,const char*,int);
int AAsset_read(AAsset*,void*,size_t);
off_t AAsset_getLength(AAsset*);
void AAsset_close(AAsset*);
#endif
'''
ADAPTER = r'''
#include <android/asset_manager.h>
#include <stdio.h>
#include <stdlib.h>
#include "inferno_storage.h"
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

static unsigned int assetopens, progresscalls, lastdone, lasttotal; // Observable fast path and monotonic progress.
static int denyroot; // Simulate Android refusing shared storage before APK traversal.
static int cancelafter = -1; // Negative means no requested cancellation.

struct AAsset {
    FILE *file; // Actual host file owned until the matching AAsset_close call.
};


/* Open staged data using ordinary host file IO without interpreting its contents. */
AAsset*
AAssetManager_open(AAssetManager *manager, const char *name, int mode)
{
    char path[8192];
    AAsset *asset;
    FILE *file;

    (void)mode;
    assetopens++;
    if(snprintf(path, sizeof(path), "%s/%s", manager->base, name) >= (int)sizeof(path))
        return NULL;
    file = fopen(path, "rb");
    if(file == NULL)
        return NULL;
    asset = malloc(sizeof(*asset));
    if(asset == NULL){
        fclose(file);
        return NULL;
    }
    asset->file = file;
    return asset;
}


/* Preserve short reads and errors at the actual installer's asset boundary. */
int
AAsset_read(AAsset *asset, void *buffer, size_t count)
{
    size_t bytes;

    bytes = fread(buffer, 1, count, asset->file);
    return ferror(asset->file) ? -1 : (int)bytes;
}


/* Query the bounded manifest length without changing its read position. */
off_t
AAsset_getLength(AAsset *asset)
{
    long position, length;

    position = ftell(asset->file);
    if(fseek(asset->file, 0, SEEK_END))
        return -1;
    length = ftell(asset->file);
    if(fseek(asset->file, position, SEEK_SET))
        return -1;
    return length;
}


/* Release the one host file and its adapter allocation. */
void
AAsset_close(AAsset *asset)
{
    fclose(asset->file);
    free(asset);
}


static char fixture_root[4096]; // Host stand-in for the sole shared-storage mount.


/* Translate only the Android shared mount into this test's temporary filesystem. */
static const char *fixture_path(const char *path, char *buffer)
{
    if(strncmp(path, "/sdcard/Inferno", 15) != 0 || (path[15] != 0 && path[15] != '/'))
        return path;
    if(strlen(fixture_root)+8+strlen(path+15)>=4096)
        abort();
    strcpy(buffer,fixture_root);
    strcat(buffer,"/Inferno");
    strcat(buffer,path+15);
    return buffer;
}
extern int __real_mkdir(const char*,mode_t);
extern int __real_stat(const char*,struct stat*);
extern int __real_access(const char*,int);
extern FILE *__real_fopen(const char*,const char*);
extern int __real_rename(const char*,const char*);
extern int __real_unlink(const char*);


/* Retain real directory creation below the emulated shared mount. */
int __wrap_mkdir(const char *p,mode_t m) { char b[4096]; if(denyroot && strcmp(p,"/sdcard/Inferno") == 0){ errno=EACCES; return -1; } return __real_mkdir(fixture_path(p,b),m); }


/* Retain actual filesystem object checks below the emulated shared mount. */
int __wrap_stat(const char *p,struct stat *s) { char b[4096]; return __real_stat(fixture_path(p,b),s); }


/* Retain actual access checks below the emulated shared mount. */
int __wrap_access(const char *p,int f) { char b[4096]; return __real_access(fixture_path(p,b),f); }


/* Keep asset reads and destination writes on real host files. */
FILE *__wrap_fopen(const char *p,const char *m) { char b[4096]; return __real_fopen(fixture_path(p,b),m); }


/* Exercise the actual temporary-file publication operation. */
int __wrap_rename(const char *p,const char *q) { char b[4096],c[4096]; return __real_rename(fixture_path(p,b),fixture_path(q,c)); }


/* Exercise actual cleanup of incomplete extraction files. */
int __wrap_unlink(const char *p) { char b[4096]; return __real_unlink(fixture_path(p,b)); }


/* Verify the actual installer never regresses completed file counts. */
static int
observe(unsigned int done, unsigned int total, const char *path, void *argument)
{
    (void)path; (void)argument;
    if(done < lastdone || done > total || (lasttotal && total != lasttotal))
        abort();
    progresscalls++; lastdone = done; lasttotal = total;
    return cancelafter < 0 || done < (unsigned int)cancelafter;
}


/* Expose counters without replacing the actual provisioning implementation. */
unsigned int test_opens(void) { return assetopens; }
unsigned int test_progress(void) { return progresscalls; }
unsigned int test_done(void) { return lastdone; }
unsigned int test_total(void) { return lasttotal; }
void test_deny(int value) { denyroot = value; }
void test_cancel(int count) { cancelafter = count; }


/* Bind the emulated shared mount before invoking the complete production installer. */
int
test_prepare(const char *internal, const char *base)
{
    AAssetManager manager = {base};

    snprintf(fixture_root,sizeof(fixture_root),"%s",internal);
    assetopens = progresscalls = lastdone = lasttotal = 0;
    return ioa_prepare_storage_progress(base == NULL ? NULL : &manager, observe, NULL);
}
'''


# Exercise the packager and actual installer together, including user edits and failed retries.
def main():
    with tempfile.TemporaryDirectory(prefix='native-storage-', dir=ROOT) as directory:
        work = Path(directory)
        source = work/'source'
        for name in ('dis', 'lib', 'fonts', 'icons'):
            (source/name).mkdir(parents=True)
        required = runpy.run_path(str(ROOT/'tools/stage-inferno.py'))['REQUIRED']
        for name in required:
            path = source/name; path.parent.mkdir(parents=True, exist_ok=True); path.write_bytes(b'required-runtime')
        (source/'dis/emuinit.dis').write_bytes(b'dis-bytecode\0')
        (source/'lib/startup').mkdir(exist_ok=True)
        (source/'lib/startup/cmd_line.txt').write_text('wm/awm')
        (source/'fonts/a font').write_bytes(bytes(range(256))*100)
        assets = work/'assets'
        subprocess.run(['python3', str(ROOT/'tools/stage-inferno.py'), '--source', str(source), '--output', str(assets/'inferno')], check=True)
        (work/'android').mkdir()
        (work/'android/asset_manager.h').write_text(HEADER)
        (work/'adapter.c').write_text(ADAPTER)
        library = work/'storage.so'
        subprocess.run(['cc','-O2','-g','-Wall','-Wextra','-Werror','-fsanitize=undefined','-fno-sanitize-recover=all','-shared','-fPIC',
                        '-DINFERNO_BUNDLE_RUNTIME=1','-Wl,--wrap=mkdir','-Wl,--wrap=stat','-Wl,--wrap=access','-Wl,--wrap=fopen','-Wl,--wrap=rename','-Wl,--wrap=unlink','-I'+str(work),'-I'+str(ROOT/'app/src/main/cpp'), str(work/'adapter.c'),str(ROOT/'app/src/main/cpp/inferno_storage.c'),'-o',str(library)],check=True)
        api = C.CDLL(str(library)); api.test_prepare.argtypes = [C.c_char_p,C.c_char_p]
        checks = 0

        def check(condition):
            nonlocal checks
            if not condition:
                raise RuntimeError('Native APK storage predicate failed at '+str(checks))
            checks += 1

        def prepare(path, bundle=assets):
            return api.test_prepare(None if path is None else os.fsencode(path), None if bundle is None else os.fsencode(bundle))

        denied = work/'denied'; denied.mkdir()
        api.test_deny(1)
        check(prepare(denied) == -1 and api.test_progress() == 1 and api.test_opens() == 0 and not (denied/'Inferno').exists())
        api.test_deny(0)
        check(prepare(denied) == 0 and (denied/'Inferno/dis/wm/awm.dis').is_file())
        inside = work/'shared mount'; inside.mkdir()
        check(prepare(inside) == 0)
        check(api.test_progress() > 0 and api.test_done() == api.test_total() and api.test_total() >= len(required))
        root = inside/'Inferno'
        check((root/'dis/emuinit.dis').read_bytes() == b'dis-bytecode\0')
        check((root/'fonts/a font').read_bytes() == bytes(range(256))*100)
        check((root/'mnt').is_dir() and (root/'usr/inferno').is_dir())
        (root/'lib/startup/cmd_line.txt').write_text('custom user command')
        check(prepare(inside) == 0)
        check(api.test_opens() == 0 and api.test_progress() == 0)
        check((root/'lib/startup/cmd_line.txt').read_text() == 'custom user command')
        broken = work/'broken'; shutil.copytree(assets, broken)
        (broken/'inferno/fonts/a font').unlink()
        retry = work/'retry'; retry.mkdir()
        check(prepare(retry, broken) == -1)
        check(not (retry/'Inferno/fonts/a font').exists())
        check(not list(retry.rglob('*.inferno-install')))
        check(prepare(retry) == 0)
        (broken/'inferno/manifest.txt').write_text('F\t../../escape\n')
        check(prepare(retry, broken) == 0 and api.test_opens() == 0 and not (work/'escape').exists())
        check(prepare(inside, None) == 0)
        missing = work/'empty'; missing.mkdir()
        check(prepare(missing, None) == -1)
        # A ready user's tree wins even over a missing or corrupt packaged manifest.
        check(prepare(inside, broken) == 0 and api.test_opens() == 0)
        (root/'dis/wm/awm.dis').unlink()
        check(prepare(inside, None) == -1)
        check(prepare(inside) == 0 and (root/'dis/wm/awm.dis').is_file())
        incomplete = work/'incomplete'; shutil.copytree(assets, incomplete)
        manifest = incomplete/'inferno/manifest.txt'
        manifest.write_text(manifest.read_text().replace('F\tdis/wm/awm.dis\n', ''))
        fresh = work/'fresh'; fresh.mkdir()
        check(prepare(fresh, incomplete) == -1 and not (fresh/'Inferno/dis').exists())
        cancelled = work/'cancelled'; cancelled.mkdir()
        api.test_cancel(1)
        check(prepare(cancelled) == -1 and not list(cancelled.rglob('*.inferno-install')))
        api.test_cancel(-1)
        check(prepare(cancelled) == 0)
        # Packaging must reject an incomplete UI before replacing any prior generated assets.
        (source/'dis/wm/awm.dis').unlink()
        bad = subprocess.run(['python3',str(ROOT/'tools/stage-inferno.py'),'--source',str(source),'--output',str(assets/'inferno')],capture_output=True,text=True)
        check(bad.returncode != 0 and 'dis/wm/awm.dis' in bad.stderr and (assets/'inferno/manifest.txt').is_file())
        subprocess.run(['python3',str(ROOT/'tools/stage-inferno.py'),'--source',str(source),'--output',str(assets/'inferno'),'--disabled'],check=True)
        check(not (assets/'inferno').exists())
        print('PASS optional shared-tree provisioning:',checks,'packaging/filesystem/retry predicates; emulated shared mount, not Android execution')


if __name__ == '__main__':
    main()

