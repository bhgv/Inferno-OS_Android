#ifndef IOA_FB_PIXELS_H
#define IOA_FB_PIXELS_H
#include "inferno_viewport.h"
#include <stdint.h>
#include <stddef.h>
#include <limits.h>


/* Scale into the viewport and clear insets without touching native buffer padding. */
static void
ioa_fb_copy(void *bits, int width, int height, int stride, int format,
    const unsigned char *source, const IoaViewport *view)
{
    int x, y, bytes;
    int sourcewidth = view->width, sourceheight = view->height;
    ARect frame = view->frame;
    int framewidth = frame.right - frame.left, frameheight = frame.bottom - frame.top;
    unsigned char *row;
    const unsigned char *pixel;

    bytes = format == WINDOW_FORMAT_RGB_565 ? 2 :
        (format == WINDOW_FORMAT_RGBA_8888 || format == WINDOW_FORMAT_RGBX_8888) ? 4 : 0;
    if(bits == NULL || bytes == 0 || width <= 0 || height <= 0 || stride < width ||
       (size_t)stride > SIZE_MAX/(size_t)height/(size_t)bytes)
        return;
    if(sourcewidth <= 0 || sourceheight <= 0 || sourcewidth > INT_MAX/4/sourceheight ||
       framewidth <= 0 || frameheight <= 0)
        source = NULL;
    for(y=0; y<height; y++){
        row = (unsigned char*)bits+(size_t)y*stride*bytes;
        const unsigned char *scan = NULL;
        if(source != NULL && y >= frame.top && y < frame.bottom){
            size_t sy = (int64_t)(y - frame.top) * sourceheight / frameheight;
            scan = source + sy * sourcewidth * 4;
        }
        for(x=0; x<width; x++){
            unsigned char *dest = row + (size_t)x * bytes;
            unsigned int r = 0, g = 0, b = 0;
            if(scan != NULL && x >= frame.left && x < frame.right){
                size_t sx = (int64_t)(x - frame.left) * sourcewidth / framewidth;
                pixel = scan + sx * 4;
                r = pixel[2]; g = pixel[1]; b = pixel[0];
            }
            if(bytes == 4){
                dest[0] = r; dest[1] = g; dest[2] = b;
                dest[3] = 255;
            }else{
                uint16_t packed = (uint16_t)(((r>>3)<<11)|((g>>2)<<5)|(b>>3));
                dest[0] = packed; dest[1] = packed>>8;
            }
        }
    }
}
#endif
