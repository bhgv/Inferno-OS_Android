#include "lib9.h"
#include "draw.h"
#include "memdraw.h"

int
hwdraw(Memdrawparam *par)
{
//	USED(par);
	int m, y, dy, dx, op;
	ulong v;
	Memimage *src;
	Memimage *dst;
	void *ext_win;

	dx = Dx(par->r);
	dy = Dy(par->r);
	src = par->src;
	dst = par->dst;

	ext_win = dst->ext_win;

	if(ext_win){
		uchar *sp, *dp;
		long swid, dwid, nb;
		int dir;

		print(">>> dst=%x, ext_win=%x, w=%d, h=%d\n", dst, ext_win, Dx(dst->r), Dy(dst->r));
#ifdef CLUTTER
		swid = src->width*sizeof(ulong);
//		dwid = dst->width*sizeof(ulong);
		sp = byteaddr(src, par->sr.min);
//		dp = byteaddr(dst, par->r.min);
//		if(dir == -1){
//			sp += (dy-1)*swid;
//			dp += (dy-1)*dwid;
//			swid = -swid;
//			dwid = -dwid;
//		}
		nb = (dx*src->depth)/8;
//		for(y=0; y<dy; y++, sp+=swid, dp+=dwid)
//			memmove(dp, sp, nb);

		clutter_ext_win_draw(par->r.min.x, par->r.min.y, sp, nb, dy, swid); 
		return 1;
#endif
	}
	return 0;	/* could not satisfy request */
}

