#!/usr/bin/env python3
"""Check actual append-only native diagnostic redirection in an isolated child process."""
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT/('app/jni' if (ROOT/'app/jni').is_dir() else 'app/src/main/cpp')
SOURCE = r'''
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "inferno_storage.h"
static const char *destination; // Child-only stand-in for the shared startup log.
int __real_open(const char*,int,...);


/* Translate only the one fixed log path and preserve the actual native open flags. */
int
__wrap_open(const char *path, int flags, ...)
{
    va_list arguments;
    int mode=0;
    if(flags&O_CREAT){ va_start(arguments,flags);mode=va_arg(arguments,int);va_end(arguments); }
    return __real_open(strcmp(path,"/sdcard/Inferno/startup.log")==0?destination:path,flags,mode);
}


/* Redirect only this child's stdout/stderr through the actual production logger. */
int
main(int argc,char **argv)
{
    if(argc!=2)return 1;
    destination=argv[1];
    if(ioa_startup_log()!=0)return 2;
    fprintf(stdout,"VM output marker\n");
    fprintf(stderr,"VM error marker\n");
    return 0;
}
'''


# Existing diagnostics must survive both launches, and both output streams must be readable afterward.
def main():
    with tempfile.TemporaryDirectory(prefix='startup-log-', dir=ROOT) as directory:
        work=Path(directory);source=work/'test.c';source.write_text(SOURCE);binary=work/'test';log=work/'startup.log'
        log.write_text('existing user log\n')
        subprocess.run(['cc','-O2','-Wall','-Wextra','-Werror','-I'+str(BASE),str(source),str(BASE/'inferno_storage.c'),'-Wl,--wrap=open','-o',str(binary)],check=True)
        for _ in range(2):
            subprocess.run([str(binary),str(log)],check=True)
        text=log.read_text()
        if not text.startswith('existing user log\n') or text.count('VM output marker')!=2 or text.count('VM error marker')!=2:
            raise RuntimeError('Native startup diagnostics were lost or replaced')
        print('PASS shared native startup log: append-only; stdout/stderr captured in child processes')


if __name__=='__main__':
    main()
