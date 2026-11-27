#ifndef INFERNO_VIEWPORT_H
#define INFERNO_VIEWPORT_H

#include <android/configuration.h>
#include <android/rect.h>
#include <limits.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	ARect frame;
	int width, height;
} IoaViewport;

/* The native buffer covers the window. Its content can have system insets. */
static inline ARect
ioa_content_bounds(int width, int height, ARect content)
{
	ARect full = {0, 0, width, height};
	if(content.left < 0)
		content.left = 0;
	if(content.top < 0)
		content.top = 0;
	if(content.right > width)
		content.right = width;
	if(content.bottom > height)
		content.bottom = height;
	if(content.right <= content.left || content.bottom <= content.top)
		return full;
	return content;
}

/* Leave space for an AWM Files window on compact phones. */
static inline int
ioa_screen_size(ARect content, int density, int *width, int *height)
{
	int w = content.right - content.left, h = content.bottom - content.top;
	if(w <= 0 || h <= 0)
		return 0;
	if(density <= 0 || density >= ACONFIGURATION_DENSITY_ANY)
		density = ACONFIGURATION_DENSITY_MEDIUM;
	int64_t logical_width = (int64_t)w * ACONFIGURATION_DENSITY_MEDIUM / density;
	if(logical_width < 416)
		logical_width = 416;
	logical_width &= ~INT64_C(3);
	if(logical_width > INT_MAX / 4)
		return 0;
	int64_t logical_height = (logical_width * h + w / 2) / w;
	if(logical_height <= 0 || logical_height > INT_MAX ||
	   logical_width > INT_MAX / 4 / logical_height)
		return 0;
	*width = (int)logical_width;
	*height = (int)logical_height;
	return 1;
}

/* Fit the existing desktop into the current content rectangle after resize. */
static inline IoaViewport
ioa_viewport(ARect content, int width, int height)
{
	IoaViewport view = {{0, 0, 0, 0}, width, height};
	int w = content.right - content.left, h = content.bottom - content.top;
	if(w <= 0 || h <= 0 || width <= 0 || height <= 0)
		return view;
	int fitw = w, fith = h;
	if((int64_t)w * height > (int64_t)h * width)
		fitw = (int)(((int64_t)h * width + height / 2) / height);
	else
		fith = (int)(((int64_t)w * height + width / 2) / width);
	view.frame.left = content.left + (w - fitw) / 2;
	view.frame.top = content.top + (h - fith) / 2;
	view.frame.right = view.frame.left + fitw;
	view.frame.bottom = view.frame.top + fith;
	return view;
}

static inline int
ioa_viewport_contains(const IoaViewport *view, float x, float y)
{
	ARect r = view->frame;
	return x >= r.left && x < r.right && y >= r.top && y < r.bottom;
}

#ifdef __cplusplus
}
#endif
#endif
