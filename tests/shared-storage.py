#!/usr/bin/env python3
"""Check actual fixed-root C code against bounded stat/access interfaces."""
import ctypes as C
import errno
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
CORE = (ROOT/'emu/Android/storage.c').is_file()
SOURCE = ROOT/('emu/Android/storage.c' if CORE else 'app/jni/inferno_storage.c' if (ROOT/'app/jni').is_dir() else 'app/src/main/cpp/inferno_storage.c')
ADAPTER = r'''
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
static int mode;
static int calls;


/* Select success, absent directory, non-directory or denied access. */
void fixture_mode(int value) { mode=value; calls=0; }


/* Expose whether an invalid output requested a filesystem operation. */
int fixture_calls(void) { return calls; }


/* Accept only the exact shared path, never an internal or environment-provided path. */
int __wrap_stat(const char *path, struct stat *state)
{
    calls++;
    if(strcmp(path,"/sdcard/Inferno") != 0) { errno=EINVAL; return -1; }
    if(mode==1) { errno=ENOENT; return -1; }
    memset(state,0,sizeof(*state));
    state->st_mode=mode==2 ? S_IFREG : S_IFDIR;
    return 0;
}


/* Verify required permissions without emulating Android's permission policy. */
int __wrap_access(const char *path,int flags)
{
    calls++;
    if(strcmp(path,"/sdcard/Inferno") != 0 || flags!=(R_OK|W_OK|X_OK)) { errno=EINVAL; return -1; }
    if(mode==3) { errno=EACCES; return -1; }
    return 0;
}
'''
with tempfile.TemporaryDirectory(prefix='shared-storage-',dir=ROOT) as directory:
    work=Path(directory)
    (work/'adapter.c').write_text(ADAPTER)
    subprocess.run(['cc','-shared','-fPIC','-Wall','-Wextra','-Werror','-O2','-fsanitize=undefined','-fno-sanitize-recover=all',str(SOURCE),str(work/'adapter.c'),'-Wl,--wrap=stat','-Wl,--wrap=access','-o',str(work/'storage.so')],check=True)
    api=C.CDLL(str(work/'storage.so'),use_errno=True)
    libc=C.CDLL(None)
    libc.getenv.restype=C.c_char_p
    libc.setenv.argtypes=[C.c_char_p,C.c_char_p,C.c_int]
    for key in (b'INFERNO_ROOT',b'INFERNO_FILES_DIR',b'EXTERNAL_STORAGE'):
        libc.setenv(key,b'/private/forbidden',1)
    def check(condition):
        if not condition:
            raise RuntimeError('Shared root predicate failed')
    if CORE:
        api.inferno_android_root.argtypes=[C.c_char_p,C.c_size_t]
        def run():
            out=C.create_string_buffer(b'unchanged',64)
            result=api.inferno_android_root(out,len(out))
            check(out.value==(b'/sdcard/Inferno' if result==0 else b'unchanged'))
            return result
        api.fixture_mode(0)
        check(api.inferno_android_root(None,64)==-1 and C.get_errno()==errno.EINVAL)
        out=C.create_string_buffer(b'same')
        check(api.inferno_android_root(out,0)==-1 and C.get_errno()==errno.EINVAL)
        check(api.inferno_android_root(out,4)==-1 and C.get_errno()==errno.ENAMETOOLONG)
        check(out.value==b'same' and api.fixture_calls()==0)
    else:
        def run():
            return api.ioa_prepare_storage(None)
    for mode,error in ((0,0),(1,errno.ENOENT),(2,errno.ENOTDIR),(3,errno.EACCES)):
        api.fixture_mode(mode)
        result=run()
        check(result==(0 if mode==0 else -1))
        if error:
            check(C.get_errno()==error)
        check(api.fixture_calls()==(2 if mode in (0,3) else 1))
    if not CORE:
        check(libc.getenv(b'EXTERNAL_STORAGE')==b'/sdcard')
        check(libc.getenv(b'INFERNO_FILES_DIR')==b'/private/forbidden')
    print('PASS fixed /sdcard/Inferno:', 'core output bounds and environment isolation' if CORE else 'launcher compatibility environment', '; missing/non-directory/denied storage; bounded host interfaces')
