#!/usr/bin/env python3
"""Execute the production FB copier with unequal extents, padded stride and guarded allocations."""
from pathlib import Path
import subprocess
import tempfile
ROOT=Path(__file__).resolve().parents[1]
SOURCE=r'''
#include <vector>
#include <cstdio>
#include <cstdlib>
#define WINDOW_FORMAT_RGB_565 4 // Native two-byte format.
#define WINDOW_FORMAT_RGBA_8888 1 // Native four-byte format.
#define WINDOW_FORMAT_RGBX_8888 2 // Native opaque four-byte format.
#include "inferno_fb_pixels.h"


/* Verify identity placement and complete source/destination guards for every tested layout. */
int main()
{
    int cases=0;
    for(int format : {1,2,4})
    for(int w : {1,4,11}) for(int h : {1,5})
    for(int sw : {1,7,16}) for(int sh : {1,3,9}){
        int bpp=format==4?2:4, stride=w+7;
        std::vector<unsigned char> dst((size_t)stride*h*bpp+32,0xa5);
        std::vector<unsigned char> src((size_t)sw*sh*4+32,0xcc);
        for(int y=0;y<sh;y++)for(int x=0;x<sw;x++){
            unsigned char *p=src.data()+16+((size_t)y*sw+x)*4;
            p[0]=x+3;p[1]=y+7;p[2]=x+y+81;p[3]=255;
        }
        auto saved=src;
        ioa_fb_copy(dst.data()+16,w,h,stride,format,src.data()+16,sw,sh);
        if(src!=saved)return 1;
        for(int i=0;i<16;i++)if(dst[i]!=0xa5||dst[dst.size()-1-i]!=0xa5)return 2;
        for(int y=0;y<h;y++)for(int x=0;x<stride;x++){
            unsigned char *p=dst.data()+16+((size_t)y*stride+x)*bpp;
            if(x>=w){for(int j=0;j<bpp;j++)if(p[j]!=0xa5)return 3;continue;}
            int r=0,g=0,b=0;
            if(x<sw&&y<sh){r=x+y+81;g=y+7;b=x+3;}
            if(bpp==4){if(p[0]!=r||p[1]!=g||p[2]!=b||p[3]!=255)return 4;}
            else if((p[0]|p[1]<<8)!=((r>>3)<<11|(g>>2)<<5|b>>3))return 5;
        }
        ioa_fb_copy(dst.data()+16,w,h,stride,format,NULL,sw,sh);
        cases++;
    }
    printf("PASS original FB identity coordinates: %d clipped/padded RGB layouts, complete guards\n",cases);
}
'''
with tempfile.TemporaryDirectory(prefix='fb-pixels-',dir=ROOT) as directory:
    p=Path(directory);(p/'test.cpp').write_text(SOURCE)
    subprocess.run(['c++','-std=c++11','-O2','-Wall','-Wextra','-Werror','-fsanitize=undefined','-fno-sanitize-recover=all','-I'+str(ROOT/'app/src/main/cpp'),str(p/'test.cpp'),'-o',str(p/'test')],check=True)
    subprocess.run([str(p/'test')],check=True)
