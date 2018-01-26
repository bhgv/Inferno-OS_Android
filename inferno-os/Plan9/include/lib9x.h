#include <u.h>
typedef usize size_t;

#define	Runeerror xRuneerror
#define	Rendez	xRendez
#include <libc.h>
#undef Runeerror
#undef Rendez


enum
{
	Runeerror	= 0x80,		/* decoding error in UTF */
};
/*
 *	Extensions for Inferno to basic libc.h
 */

#define	setbinmode()
#define	USE_FPdbleword
