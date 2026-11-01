#ifndef IOA_FB_PIXELS_H
#define IOA_FB_PIXELS_H // FB pixels and touches use the original unscaled surface coordinates.
#include <stdint.h>
#include <stddef.h>
#include <limits.h>


/* Clip source and destination independently; native buffer padding is never image data. */
static void
ioa_fb_copy(void *bits, int width, int height, int stride, int format,
    const unsigned char *source, int sourcewidth, int sourceheight)
{
    int x, y, bytes, copywidth, copyheight;
    unsigned char *row;
    const unsigned char *pixel;

    bytes = format == WINDOW_FORMAT_RGB_565 ? 2 :
        (format == WINDOW_FORMAT_RGBA_8888 || format == WINDOW_FORMAT_RGBX_8888) ? 4 : 0;
    if(bits == NULL || bytes == 0 || width <= 0 || height <= 0 || stride < width ||
       (size_t)stride > SIZE_MAX/(size_t)height/(size_t)bytes)
        return;
    copywidth = sourcewidth < width ? sourcewidth : width;
    copyheight = sourceheight < height ? sourceheight : height;
    if(sourcewidth <= 0 || sourceheight <= 0 ||
       (size_t)sourcewidth > SIZE_MAX/(size_t)sourceheight/4 || sourcewidth > INT_MAX/4/sourceheight)
        source = NULL;
    for(y=0; y<height; y++){
        row = (unsigned char*)bits+(size_t)y*stride*bytes;
        for(x=0; x<width; x++){
            unsigned int r = 0, g = 0, b = 0;
            if(source != NULL && x < copywidth && y < copyheight){
                pixel = source+((size_t)y*sourcewidth+x)*4;
                r = pixel[2]; g = pixel[1]; b = pixel[0];
            }
            if(bytes == 4){
                row[x*4] = r; row[x*4+1] = g; row[x*4+2] = b;
                row[x*4+3] = 255;
            }else{
                uint16_t packed = (uint16_t)(((r>>3)<<11)|((g>>2)<<5)|(b>>3));
                row[x*2] = packed; row[x*2+1] = packed>>8;
            }
        }
    }
}
#endif
