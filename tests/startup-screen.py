#!/usr/bin/env python3
"""Exercise the actual font renderer against padded windows without installed assets."""
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SOURCE = r'''
#include <cstdio>
#include <cstdint>
#include <vector>
#include <cstdlib>
struct ANativeWindow_Buffer { int width, height, stride; void *bits; };
struct android_app { void *window; struct { int top; } contentRect; };
static ANativeWindow_Buffer surface;
static int posts;
#define WINDOW_FORMAT_RGBX_8888 2 // Native format boundary.
static int ANativeWindow_setBuffersGeometry(void*,int,int,int) { return 0; }
static int ANativeWindow_lock(void*,ANativeWindow_Buffer *b,void*) { *b=surface;return 0; }
static int ANativeWindow_unlockAndPost(void*) { posts++;return 0; }
#include "inferno_startup_screen.h"


/* Guard padding and surrounding pixels while rendering wrapped errors at several widths. */
int main()
{
    for(int width : {16, 320, 1080}){
        int height=900, stride=width+8;
        std::vector<uint32_t> pixels(stride*height+32,0xdeadbeef);
        surface={width,height,stride,pixels.data()+16};
        android_app app={(void*)1,{80}};
        ioa_status_screen(&app,"STORAGE ACCESS DENIED\nANDROID SETTINGS - FILES / STORAGE",0);
        ioa_fb_storage_progress(25,100,"dis/wm/awm.dis",&app);
        for(int i=0;i<16;i++)
            if(pixels[i]!=0xdeadbeef || pixels[pixels.size()-1-i]!=0xdeadbeef) return 1;
        for(int y=0;y<height;y++)
            for(int x=width;x<stride;x++)
                if(pixels[16+y*stride+x]!=0xdeadbeef) return 2;
        int white=0;
        for(int y=104;y<height;y++)
            for(int x=0;x<width;x++)
                if(pixels[16+y*stride+x]==0xffffffff) white++;
        if(width>=320 && white==0) return 3;
    }
    if(posts<4) return 4;
    puts("PASS actual native startup font: no assets, wrapped text, padded stride and bounds");
}
'''
with tempfile.TemporaryDirectory(prefix='startup-screen-',dir=ROOT) as directory:
    work=Path(directory);(work/'test.cpp').write_text(SOURCE)
    subprocess.run(['c++','-std=c++11','-Wall','-Wextra','-Werror','-fsanitize=undefined','-fno-sanitize-recover=all','-I'+str(ROOT/'app/src/main/cpp'),str(work/'test.cpp'),'-o',str(work/'test')],check=True)
    subprocess.run([str(work/'test')],check=True)
