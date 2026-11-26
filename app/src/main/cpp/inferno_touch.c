#include "inferno_touch.h"
#include <math.h>
#include <stdlib.h>

enum { Left = 1, Middle = 2, Right = 4, WheelUp = 8, WheelDown = 16, Double = 1 << 8 };
enum { TapDistance = 12, TapTime = 300000000 }; /* Pixels and nanoseconds. */
enum { MaxWheelSteps = 4 };

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

static int
begin_click(IoaTouch *state, int64_t time)
{
	int doubleclick = quick(time, state->tap_time) &&
	                  near(state->x, state->y, state->tapx, state->tapy);
	state->downx = state->x;
	state->downy = state->y;
	state->down_time = time;
	state->tap_candidate = !doubleclick;
	state->tap_time = 0;
	return doubleclick ? Double : 0;
}

static void
finish_click(IoaTouch *state, int64_t time)
{
	if(state->tap_candidate && quick(time, state->down_time)){
		state->tap_time = time;
		state->tapx = state->x;
		state->tapy = state->y;
	}
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
		touch->buttons = Left;
		send(touch->x, touch->y, Left | begin_click(touch, time));
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
		finish_click(touch, time);
		send(touch->x, touch->y, 0);
		touch->buttons = 0;
		break;
	}
	return 1;
}

static int
mouse_buttons(int32_t state)
{
	return ((state & AMOTION_EVENT_BUTTON_PRIMARY) ? Left : 0) |
	       ((state & AMOTION_EVENT_BUTTON_TERTIARY) ? Middle : 0) |
	       ((state & AMOTION_EVENT_BUTTON_SECONDARY) ? Right : 0);
}

static void
mouse_wheel(IoaInput *input, float delta, IoaPointer *send)
{
	IoaTouch *mouse = &input->mouse;
	if(!isfinite(delta) || delta == 0)
		return;
	mouse->tap_time = 0;
	mouse->tap_candidate = 0;
	/* Keep fractional ticks and bound bursts sent to the pointer queue. */
	float total = input->wheel + delta;
	if(total > MaxWheelSteps)
		total = MaxWheelSteps;
	if(total < -MaxWheelSteps)
		total = -MaxWheelSteps;
	int steps = (int)total;
	input->wheel = total - steps;
	int button = steps > 0 ? WheelUp : WheelDown;
	for(int i = 0; i < abs(steps); i++){
		send(mouse->x, mouse->y, mouse->buttons | button);
		send(mouse->x, mouse->y, mouse->buttons);
	}
}

static int
mouse_motion(IoaInput *input, const AInputEvent *event, int width, int height,
             IoaPointer *send)
{
	IoaTouch *mouse = &input->mouse;
	int action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
	switch(action){
	case AMOTION_EVENT_ACTION_CANCEL:
		ioa_touch_reset(mouse, send);
		input->wheel = 0;
		return 1;
	case AMOTION_EVENT_ACTION_DOWN:
	case AMOTION_EVENT_ACTION_UP:
	case AMOTION_EVENT_ACTION_MOVE:
	case AMOTION_EVENT_ACTION_HOVER_ENTER:
	case AMOTION_EVENT_ACTION_HOVER_MOVE:
	case AMOTION_EVENT_ACTION_HOVER_EXIT:
	case AMOTION_EVENT_ACTION_BUTTON_PRESS:
	case AMOTION_EVENT_ACTION_BUTTON_RELEASE:
	case AMOTION_EVENT_ACTION_SCROLL:
		break;
	default:
		return 0;
	}
	if(width <= 0 || height <= 0 || AMotionEvent_getPointerCount(event) == 0)
		return 0;

	int oldx = mouse->x, oldy = mouse->y;
	int oldbuttons = mouse->buttons;
	int buttons = mouse_buttons(AMotionEvent_getButtonState(event));
	/* A held button from a gesture we did not start cannot acquire a grab. */
	if(buttons && !oldbuttons && action != AMOTION_EVENT_ACTION_DOWN &&
	   action != AMOTION_EVENT_ACTION_BUTTON_PRESS)
		return 1;
	int64_t time = AMotionEvent_getEventTime(event);
	position(mouse, event, 0, width, height);
	mouse->tap_candidate &= near(mouse->x, mouse->y, mouse->downx, mouse->downy);
	int click = 0;
	if((oldbuttons | buttons) & (Middle | Right)){
		mouse->tap_time = 0;
		mouse->tap_candidate = 0;
	}else if(buttons == Left && oldbuttons == 0)
		click = begin_click(mouse, time);
	else if(buttons == 0 && oldbuttons == Left)
		finish_click(mouse, time);
	mouse->buttons = buttons;
	if(buttons != oldbuttons || mouse->x != oldx || mouse->y != oldy)
		send(mouse->x, mouse->y, buttons | click);
	if(action == AMOTION_EVENT_ACTION_SCROLL)
		mouse_wheel(input, AMotionEvent_getAxisValue(event, AMOTION_EVENT_AXIS_VSCROLL, 0), send);
	return 1;
}

int
ioa_pointer_motion(IoaInput *input, const AInputEvent *event, int width, int height,
                   IoaPointer *send)
{
	/* An active button grab owns the Inferno pointer until release. */
	if((AInputEvent_getSource(event) & AINPUT_SOURCE_MOUSE) == AINPUT_SOURCE_MOUSE){
		if(input->touch.buttons)
			return 1;
		return mouse_motion(input, event, width, height, send);
	}
	if(input->mouse.buttons)
		return 1;
	return ioa_touch_motion(&input->touch, event, width, height, send);
}

void
ioa_pointer_reset(IoaInput *input, IoaPointer *send)
{
	ioa_touch_reset(&input->touch, send);
	ioa_touch_reset(&input->mouse, send);
	input->wheel = 0;
}
