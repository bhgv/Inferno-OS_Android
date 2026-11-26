#ifndef INFERNO_TOUCH_H
#define INFERNO_TOUCH_H

#include <android/input.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void IoaPointer(int x, int y, int buttons);

typedef struct {
	int primary;
	int buttons;
	int x, y;
	int downx, downy;
	int tapx, tapy;
	int tap_candidate;
	int64_t down_time, tap_time;
} IoaTouch;

int ioa_touch_motion(IoaTouch*, const AInputEvent*, int width, int height, IoaPointer*);
void ioa_touch_reset(IoaTouch*, IoaPointer*);

#ifdef __cplusplus
}
#endif

#endif
