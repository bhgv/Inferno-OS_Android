#ifndef IOA_STARTUP_SCREEN_H
#define IOA_STARTUP_SCREEN_H // Asset-independent native startup diagnostics.
#include <stdint.h>
#include <errno.h>

/* Seven rows per ASCII glyph; diagnostics remain usable before fonts are installed. */
static const unsigned char ioa_status_font[128][7] = {
    {0,0,0,0,0,0,0}, // 0
    {0,0,0,0,0,0,0}, // 1
    {0,0,0,0,0,0,0}, // 2
    {0,0,0,0,0,0,0}, // 3
    {0,0,0,0,0,0,0}, // 4
    {0,0,0,0,0,0,0}, // 5
    {0,0,0,0,0,0,0}, // 6
    {0,0,0,0,0,0,0}, // 7
    {0,0,0,0,0,0,0}, // 8
    {0,0,0,0,0,0,0}, // 9
    {0,0,0,0,0,0,0}, // 10
    {0,0,0,0,0,0,0}, // 11
    {0,0,0,0,0,0,0}, // 12
    {0,0,0,0,0,0,0}, // 13
    {0,0,0,0,0,0,0}, // 14
    {0,0,0,0,0,0,0}, // 15
    {0,0,0,0,0,0,0}, // 16
    {0,0,0,0,0,0,0}, // 17
    {0,0,0,0,0,0,0}, // 18
    {0,0,0,0,0,0,0}, // 19
    {0,0,0,0,0,0,0}, // 20
    {0,0,0,0,0,0,0}, // 21
    {0,0,0,0,0,0,0}, // 22
    {0,0,0,0,0,0,0}, // 23
    {0,0,0,0,0,0,0}, // 24
    {0,0,0,0,0,0,0}, // 25
    {0,0,0,0,0,0,0}, // 26
    {0,0,0,0,0,0,0}, // 27
    {0,0,0,0,0,0,0}, // 28
    {0,0,0,0,0,0,0}, // 29
    {0,0,0,0,0,0,0}, // 30
    {0,0,0,0,0,0,0}, // 31
    {0,0,0,0,0,0,0}, // 32
    {0,0,0,0,0,0,0}, // 33
    {0,0,0,0,0,0,0}, // 34
    {0,0,0,0,0,0,0}, // 35
    {0,0,0,0,0,0,0}, // 36
    {25,26,4,4,8,22,6}, // 37
    {0,0,0,0,0,0,0}, // 38
    {0,0,0,0,0,0,0}, // 39
    {0,0,0,0,0,0,0}, // 40
    {0,0,0,0,0,0,0}, // 41
    {0,0,0,0,0,0,0}, // 42
    {0,0,0,0,0,0,0}, // 43
    {0,0,0,0,0,0,0}, // 44
    {0,0,0,31,0,0,0}, // 45
    {0,0,0,0,0,6,6}, // 46
    {1,2,2,4,8,8,16}, // 47
    {14,17,19,21,25,17,14}, // 48
    {4,12,4,4,4,4,14}, // 49
    {14,17,1,2,4,8,31}, // 50
    {30,1,1,14,1,1,30}, // 51
    {2,6,10,18,31,2,2}, // 52
    {31,16,16,30,1,1,30}, // 53
    {14,16,16,30,17,17,14}, // 54
    {31,1,2,4,8,8,8}, // 55
    {14,17,17,14,17,17,14}, // 56
    {14,17,17,15,1,1,14}, // 57
    {0,6,6,0,6,6,0}, // 58
    {0,0,0,0,0,0,0}, // 59
    {0,0,0,0,0,0,0}, // 60
    {0,0,0,0,0,0,0}, // 61
    {0,0,0,0,0,0,0}, // 62
    {0,0,0,0,0,0,0}, // 63
    {0,0,0,0,0,0,0}, // 64
    {14,17,17,31,17,17,17}, // 65
    {30,17,17,30,17,17,30}, // 66
    {15,16,16,16,16,16,15}, // 67
    {30,17,17,17,17,17,30}, // 68
    {31,16,16,30,16,16,31}, // 69
    {31,16,16,30,16,16,16}, // 70
    {15,16,16,23,17,17,15}, // 71
    {17,17,17,31,17,17,17}, // 72
    {31,4,4,4,4,4,31}, // 73
    {7,2,2,2,18,18,12}, // 74
    {17,18,20,24,20,18,17}, // 75
    {16,16,16,16,16,16,31}, // 76
    {17,27,21,21,17,17,17}, // 77
    {17,25,21,19,17,17,17}, // 78
    {14,17,17,17,17,17,14}, // 79
    {30,17,17,30,16,16,16}, // 80
    {14,17,17,17,21,18,13}, // 81
    {30,17,17,30,20,18,17}, // 82
    {15,16,16,14,1,1,30}, // 83
    {31,4,4,4,4,4,4}, // 84
    {17,17,17,17,17,17,14}, // 85
    {17,17,17,17,17,10,4}, // 86
    {17,17,17,21,21,21,10}, // 87
    {17,17,10,4,10,17,17}, // 88
    {17,17,10,4,4,4,4}, // 89
    {31,1,2,4,8,16,31}, // 90
    {0,0,0,0,0,0,0}, // 91
    {0,0,0,0,0,0,0}, // 92
    {0,0,0,0,0,0,0}, // 93
    {0,0,0,0,0,0,0}, // 94
    {0,0,0,0,0,0,0}, // 95
    {0,0,0,0,0,0,0}, // 96
    {0,0,0,0,0,0,0}, // 97
    {0,0,0,0,0,0,0}, // 98
    {0,0,0,0,0,0,0}, // 99
    {0,0,0,0,0,0,0}, // 100
    {0,0,0,0,0,0,0}, // 101
    {0,0,0,0,0,0,0}, // 102
    {0,0,0,0,0,0,0}, // 103
    {0,0,0,0,0,0,0}, // 104
    {0,0,0,0,0,0,0}, // 105
    {0,0,0,0,0,0,0}, // 106
    {0,0,0,0,0,0,0}, // 107
    {0,0,0,0,0,0,0}, // 108
    {0,0,0,0,0,0,0}, // 109
    {0,0,0,0,0,0,0}, // 110
    {0,0,0,0,0,0,0}, // 111
    {0,0,0,0,0,0,0}, // 112
    {0,0,0,0,0,0,0}, // 113
    {0,0,0,0,0,0,0}, // 114
    {0,0,0,0,0,0,0}, // 115
    {0,0,0,0,0,0,0}, // 116
    {0,0,0,0,0,0,0}, // 117
    {0,0,0,0,0,0,0}, // 118
    {0,0,0,0,0,0,0}, // 119
    {0,0,0,0,0,0,0}, // 120
    {0,0,0,0,0,0,0}, // 121
    {0,0,0,0,0,0,0}, // 122
    {0,0,0,0,0,0,0}, // 123
    {0,0,0,0,0,0,0}, // 124
    {0,0,0,0,0,0,0}, // 125
    {0,0,0,0,0,0,0}, // 126
    {0,0,0,0,0,0,0}, // 127
};


/* Paint directly into the native window; no VM framebuffer or installed font is needed. */
static void
ioa_status_screen(struct android_app *app, const char *text, unsigned int percent)
{
    ANativeWindow_Buffer buffer;
    int scale, x, y, row, col, dx, dy;
    const unsigned char *cursor = reinterpret_cast<const unsigned char*>(text);

    if(app->window == NULL)
        return;
    ANativeWindow_setBuffersGeometry(app->window, 0, 0, WINDOW_FORMAT_RGBX_8888);
    if(ANativeWindow_lock(app->window, &buffer, NULL) != 0)
        return;
    scale = buffer.width >= 600 ? 3 : 2;
    for(y = 0; y < buffer.height; y++)
        for(x = 0; x < buffer.width; x++)
            static_cast<uint32_t*>(buffer.bits)[y*buffer.stride+x] = 0xff202020;
    x = 12; y = app->contentRect.top + 24;
    for(; *cursor != 0; cursor++){
        unsigned char c = *cursor;
        if(c >= 'a' && c <= 'z') c -= 'a'-'A';
        if(c == '\n' || x+6*scale >= buffer.width){
            x = 12; y += 10*scale;
            if(c == '\n') continue;
        }
        if(c >= 128) c = ' ';
        for(row = 0; row < 7; row++)
            for(col = 0; col < 5; col++)
                if(ioa_status_font[c][row] & (1 << (4-col)))
                    for(dy = 0; dy < scale; dy++)
                        for(dx = 0; dx < scale; dx++){
                            int px = x+col*scale+dx, py = y+row*scale+dy;
                            if(px >= 0 && px < buffer.width && py >= 0 && py < buffer.height)
                                static_cast<uint32_t*>(buffer.bits)[py*buffer.stride+px] = 0xffffffff;
                        }
        x += 6*scale;
    }
    for(y = buffer.height-32; y < buffer.height-16; y++)
        for(x = 12; x < 12+(buffer.width-24)*static_cast<int>(percent > 100 ? 100 : percent)/100; x++)
            if(y >= 0)
                static_cast<uint32_t*>(buffer.bits)[y*buffer.stride+x] = 0xfff0b450;
    ANativeWindow_unlockAndPost(app->window);
}


/* Show progress even while the destination tree and its fonts do not exist. */
static int
ioa_fb_storage_progress(unsigned int done, unsigned int total, const char *path, void *argument)
{
    static unsigned int previous = 101; // Draw only changed percentages, keeping extraction bounded.
    char message[512];
    unsigned int percent = total == 0 ? 0 : static_cast<unsigned int>(100ULL*done/total);

    if(total != 0 && percent == previous && done != total)
        return 1;
    previous = percent;
    snprintf(message, sizeof(message), "PREPARING /SDCARD/INFERNO\n%u%%  %u / %u FILES\n%s", percent, done, total, path);
    ioa_status_screen(static_cast<struct android_app*>(argument), message, percent);
    return 1;
}
#endif
