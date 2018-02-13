#include "lib9.h"
#include "kernel.h"
#include "draw.h"


#ifdef ANDROID
#include <android/log.h>

#define  LOG_TAG    "inferno RSF"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
#define  LOGI(...)  printf(__VA_ARGS__)
#define  LOGW(...)  
#define  LOGE(...)  
#endif


extern Subfont*
readsubfont_ft(Display*d, char *name, int fnt_size, int dolock);


/*
 * Default version: treat as file name
 */

Subfont*
_getsubfont(Display *d, char *name, int font_size)
{
	int fd;
	Subfont *f;

	if( is_subfont_ft(name) )
	{
		if(d->local == 0)
			unlockdisplay(d);
LOGI("pre rsf_ft (%s)", name);
		f = readsubfont_ft(d, name, font_size, d->local == 0);
		if(d->local == 0)
			lockdisplay(d);
		if(f == 0)
			_drawprint(2, "getsubfont: can't read %s: %r\n", name);
		return f;
	}

	fd = libopen(name, OREAD);
		
	if(fd < 0){
		_drawprint(2, "getsubfont: can't open %s: %r\n", name);
		return 0;
	}
	/*
	 * unlock display so i/o happens with display released, unless
	 * user is doing his own locking, in which case this could break things.
	 * _getsubfont is called only from string.c and stringwidth.c,
	 * which are known to be safe to have this done.
	 */
	if(d->local == 0)
		unlockdisplay(d);
	f = readsubfont(d, name, fd, d->local == 0);
	if(d->local == 0)
		lockdisplay(d);
	if(f == 0)
		_drawprint(2, "getsubfont: can't read %s: %r\n", name);
	libclose(fd);
	return f;
}
