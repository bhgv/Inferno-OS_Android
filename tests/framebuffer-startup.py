#!/usr/bin/env python3
"""Run the actual framebuffer libinit wrapper through a separate caller archive."""
from pathlib import Path
import subprocess
import tempfile

ROOT=Path(__file__).resolve().parents[1]


# Retain the complete production body rather than rewriting its allocation decisions in the fixture.
def wrapper():
    source=(ROOT/'app/src/main/cpp/inferno_os_app.cpp').read_text()
    start=source.index('extern "C" void\n__wrap_libinit(')
    brace=source.index('{',start)
    depth=0
    for index in range(brace,len(source)):
        if source[index]=='{': depth+=1
        elif source[index]=='}':
            depth-=1
            if depth==0: return source[start:index+1]
    raise RuntimeError('Incomplete production wrapper')


# Verify final parsed geometry, repeat rejection and overflow guards with active checks under optimization.
def main():
    source=r'''
#include <cstdlib>
#include <climits>
#define ANDROID_LOG_ERROR 1 // Native logging category only; no Android runtime is emulated.
int Xsize,Ysize;
unsigned char *xscreendata;
static int started;
extern "C" void __real_libinit(void *);
extern "C" void fixture_start(int,int);


/* Keep logging separate from the startup outcome predicates. */
int __android_log_print(int,const char*,const char*,...) { return 0; }


/* Require a complete final allocation before the real interpreter entry is reached. */
extern "C" void libinit(void *)
{
    if(!xscreendata) std::exit(2);
    xscreendata[static_cast<size_t>(Xsize)*Ysize*4-1]=7;
    started++;
}
WRAPPER


/* Keep all outcome checks active independently of assert/NDEBUG. */
int main()
{
    fixture_start(643,479);
    if(started!=1 || Xsize!=640 || Ysize!=479) return 3;
    fixture_start(640,479);
    if(started!=1) return 4;
    free(xscreendata);xscreendata=NULL;
    fixture_start(3,479);
    fixture_start(INT_MAX,INT_MAX);
    fixture_start(-4,8);
    if(started!=1 || xscreendata!=NULL) return 5;
    return 0;
}
'''.replace('WRAPPER',wrapper())
    caller='extern "C" { extern int Xsize,Ysize; void libinit(void*);\n/* Model separately compiled amain after option parsing. */\nvoid fixture_start(int x,int y){Xsize=x;Ysize=y;libinit(NULL);} }\n'
    caller='#include <cstddef>\n'+caller
    with tempfile.TemporaryDirectory(prefix='fb-startup-',dir=ROOT) as directory:
        work=Path(directory)
        (work/'main.cpp').write_text(source);(work/'caller.cpp').write_text(caller)
        subprocess.run(['c++','-c',str(work/'caller.cpp'),'-o',str(work/'caller.o')],check=True)
        subprocess.run(['ar','rcs',str(work/'emu.a'),str(work/'caller.o')],check=True)
        subprocess.run(['c++','-O3','-DNDEBUG','-fsanitize=undefined','-fno-sanitize-recover=all',str(work/'main.cpp'),str(work/'emu.a'),'-Wl,--wrap=libinit','-o',str(work/'run')],check=True)
        subprocess.run([str(work/'run')],check=True)
    print('PASS actual framebuffer startup wrapper: archived caller, final geometry/alignment, repeat and invalid/overflow rejection')


if __name__=='__main__':
    main()
