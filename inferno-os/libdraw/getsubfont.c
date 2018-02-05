#include "lib9.h"
#include "kernel.h"
#include "draw.h"


extern Subfont*
readsubfont_ft(Display*d, char *name, int fnt_size, int dolock);


/*
 * Default version: treat as file name
 */

Subfont*
_getsubfont(Display *d, char *name)
{
	int fd;
	Subfont *f;

	{
		char c1, c2, c3, c4;
		
		int i = strlen(name) - 1;
		
		for( ; i >= 0 && name[i] != '.'; i--);
		if(i >= 0){
			c1 = name[i];
			c2 = name[i+1];
			c3 = name[i+2];
			c4 = name[i+3];
		}else{
			c1 = c2 = c3 = c4 = '\0';
		}
		if(c1 == '.' && 
			(c2 == 't' || c2 == 'T') &&
			(c3 == 't' || c3 == 'T') &&
			(c4 == 'f' || c4 == 'F')
		){
			if(d->local == 0)
				unlockdisplay(d);
			f = readsubfont_ft(d, name, 16, d->local == 0);
			if(d->local == 0)
				lockdisplay(d);
			if(f == 0)
				_drawprint(2, "getsubfont: can't read %s: %r\n", name);
			return f;
		}
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
