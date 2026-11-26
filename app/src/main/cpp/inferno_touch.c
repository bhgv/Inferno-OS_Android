#include "inferno_touch.h"
#include <stdlib.h>

enum { Left = 1, Middle = 2, Right = 4, Double = 1 << 8 };
enum { TapDistance = 12, TapTime = 300000000 }; /* Pixels and nanoseconds. */

static int
coordinate(float value, int span)
{
	if(!(value > 0))
		return 0;
	if(value >= span - 1)
		return span - 1;
	return (int)value;
}

static void
position(IoaTouch *touch, const AInputEvent *event, size_t index, int width, int height)
{
	touch->x = coordinate(AMotionEvent_getX(event, index), width);
	touch->y = coordinate(AMotionEvent_getY(event, index), height);
}

static int
near(int x, int y, int otherx, int othery)
{
	return abs(x - otherx) <= TapDistance && abs(y - othery) <= TapDistance;
}

static int
quick(int64_t now, int64_t before)
{
	return before > 0 && now >= before && now - before <= TapTime;
}

void
ioa_touch_reset(IoaTouch *touch, IoaPointer *send)
{
	if(touch->buttons)
		send(touch->x, touch->y, 0);
	touch->buttons = 0;
	touch->tap_time = 0;
	touch->tap_candidate = 0;
}

int
ioa_touch_motion(IoaTouch *touch, const AInputEvent *event, int width, int height,
                 IoaPointer *send)
{
	int action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
	size_t count = AMotionEvent_getPointerCount(event);
	int64_t time = AMotionEvent_getEventTime(event);

	if(action == AMOTION_EVENT_ACTION_CANCEL){
		ioa_touch_reset(touch, send);
		return 1;
	}
	if(width <= 0 || height <= 0)
		return 0;
	if(action == AMOTION_EVENT_ACTION_DOWN){
		if(touch->buttons || count != 1)
			ioa_touch_reset(touch, send);
		if(count != 1)
			return 1;
		touch->primary = AMotionEvent_getPointerId(event, 0);
		position(touch, event, 0, width, height);
		int doubletap = quick(time, touch->tap_time) &&
		                near(touch->x, touch->y, touch->tapx, touch->tapy);
		touch->buttons = Left;
		touch->downx = touch->x;
		touch->downy = touch->y;
		touch->down_time = time;
		touch->tap_candidate = !doubletap;
		touch->tap_time = 0;
		send(touch->x, touch->y, Left | (doubletap ? Double : 0));
		return 1;
	}

	switch(action){
	case AMOTION_EVENT_ACTION_MOVE:
	case AMOTION_EVENT_ACTION_POINTER_DOWN:
	case AMOTION_EVENT_ACTION_POINTER_UP:
	case AMOTION_EVENT_ACTION_UP:
		break;
	default:
		return 0;
	}
	if(!touch->buttons)
		return 1;
	size_t index;
	for(index = 0; index < count; index++)
		if(AMotionEvent_getPointerId(event, index) == touch->primary)
			break;
	if(index == count){
		ioa_touch_reset(touch, send);
		return 1;
	}
	position(touch, event, index, width, height);
	touch->tap_candidate &= near(touch->x, touch->y, touch->downx, touch->downy);

	switch(action){
	case AMOTION_EVENT_ACTION_MOVE:
		send(touch->x, touch->y, touch->buttons);
		break;
	case AMOTION_EVENT_ACTION_POINTER_DOWN: {
		int buttons = count == 2 ? Middle : Right;
		touch->tap_candidate = 0;
		if(buttons != touch->buttons){
			send(touch->x, touch->y, 0);
			touch->buttons = buttons;
			send(touch->x, touch->y, buttons);
		}
		break;
	}
	case AMOTION_EVENT_ACTION_POINTER_UP:
		/* End a chord without pressing a new button for the remaining fingers. */
		ioa_touch_reset(touch, send);
		break;
	case AMOTION_EVENT_ACTION_UP:
		if(touch->tap_candidate && quick(time, touch->down_time)){
			touch->tap_time = time;
			touch->tapx = touch->x;
			touch->tapy = touch->y;
		}
		send(touch->x, touch->y, 0);
		touch->buttons = 0;
		break;
	}
	return 1;
}
