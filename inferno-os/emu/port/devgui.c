#include	"dat.h"
#include	"fns.h"
#include	"error.h"
//#include	"audio.h"

#include "interp.h"

#include "draw.h"
#include "tk.h"
#include "../libtk/canvs.h"

//#include <stdbool.h>
//#define TRUE true
//#define FALSE false


#ifdef ANDROID_NO_DEF
#include <android/log.h>
	
#define  LOG_TAG    "Inferno GUI"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else
#define  LOGI(...)  print(__VA_ARGS__)
#define  LOGW(...)  print(__VA_ARGS__)
#define  LOGE(...)  print(__VA_ARGS__)
#endif


enum
{
	Qdir = 0,		/* must start at 0 representing a directory */
	Qgui,
	Qguictl
};



#define	QSHIFT		16	// 4		/* location in qid of pid */
#define	QID(q)		(((ulong)(q).path&0x00007ffF)>>0)
#define QPID(pid)	(((pid)<<QSHIFT))
#define	PID(q)		((q).vers)
#define PATH(q)		( (ulong)(q).path & ~((1<<QSHIFT)-1) )
#define QCTL_NAME	((ulong)0x00008000)





extern char rootdir[];


void guictl_wr_pars(char* in, int count);


extern TkMethod *tkmethod[];
extern TkCimeth tkcimethod[];

extern char* tksinglecmd(TkTop *t, char *arg, char **val);
//extern char* tkwidgetcmd(TkTop *t, Tk *tk, char *arg, char **val);



static int
guigen(Chan *c, char *name, Dirtab *tab, int ntab, int s, Dir *dp)
{
	Qid qid;
	Prog *p;
	char *e;
	Osenv *o;
	ulong pid, path, perm, len;

	TkTop *t;
	Tk *tk=nil, *tk2=nil, *tkr=nil;
	int i, j, n;
	

	USED(ntab);

	if(s == DEVDOTDOT){
		n = QID(c->qid);

		p = progpid(PID(c->qid));
		if(p == nil){
			error(Enonexist);
		}

		t = p->tktop;
		
		if(!t){			
			mkqid(&qid, Qdir, 0, QTDIR);
			devdir(c, qid, "#G", 0, eve, DMDIR|0555, dp);
			return 1;
		}

		tkr = t->root;

		for( i = 1, tk = tkr; i < n; i++, tk = tk->siblings ){
			if(tk == nil){
				error(Enonexist);
			}
		}
		if(tk)
			tk = tk->master;

		if( !tk /*|| tk == tkr*/){
			mkqid(&qid, Qdir, 0, QTDIR);
			devdir(c, qid, "#G", 0, eve, DMDIR|0555, dp);
			return 1;
		}

		for( n = 1, tk2 = t->root; tk2 != tk; tk2 = tk2->siblings, n++){
			if(tk2 == nil){
				error(Enonexist);
			}
		}

		snprint(up->genbuf, 127, "%s", 
				tk->name_tail
				? tk->name_tail
				: tk->name->name
		);
		mkqid(&qid, (ulong)n | PATH(c->qid), c->qid.vers, QTDIR);
		o =  p->osenv;
		devdir(c, qid, up->genbuf, 0,  o->user, DMDIR|0555, dp);
		return 1;
	}


	if((ulong)c->qid.path == Qdir) {
		if(name != nil){
			/* ignore s and use name to find pid */
			pid = strtoul(name, &e, 0);
			if(pid == 0 || *e != '\0')
				return -1;
			acquire();
			p = progpid(pid);
			if(p == nil){
				release();
				return -1;
			}
		}else{
			acquire();
			p = progn(s);
			if(p == nil) {
				release();
				return -1;
			}
			pid = p->pid;
		}
		o = p->osenv;
		sprint(up->genbuf, "%lud", pid);
		if(name != nil && strcmp(name, up->genbuf) != 0){
			release();
			return -1;
		}
		mkqid(&qid, pid << QSHIFT, pid, QTDIR);
		devdir(c, qid, up->genbuf, 0, o->user, DMDIR|0555, dp);
		release();
		return 1;
	}


	path = QID(c->qid); //PATH(c->qid) >> QSHIFT;

	acquire();
	p = progpid(PID(c->qid));
	if(p == nil) {
		release();
		return -1;
	}
	o = p->osenv;


	if(p->tktop == nil) {
		release();
		return -1;
	}
	else{
		if(name != nil){
			t = p->tktop;
		
			tkr = t->root;
			n = path;
			
			for( i = 1, tk = tkr; i < n; i++, tk = tk->siblings ){
				if(tk == nil){
					release();
					return -1;
				}
			}

			if( strcmp(name, ".self") ){
				char *p, *pr = nil;
				
				for(p = name; *p != '\0'; p++){
					if(*p == '.'){
						pr = p;
						*p = '\0';
						break;
					}
				}

				for( tk2 = tk->slave; tk2; tk2 = tk2->next){
					if( !strcmp(name, 
							tk2->name_tail
							? tk2->name_tail
							: tk2->name->name) 
					){
						break;
					}
				}
				if(tk2 == nil){
					release();
					return -1;
				}
				if(pr != nil)
					*pr = '.';
				
				for( n = 1, tk = t->root; tk != tk2; tk = tk->siblings, n++){
					if(tk == nil){
						release();
						return -1;
					}
				}
			}else{
				n = 0;
			}

		}
		else{
			t = p->tktop;
		
			tkr = t->root;
			n = path;
			
			for( i = 1, tk = tkr; i < n; i++, tk = tk->siblings ){
				if(tk == nil){
					release();
					return -1;
				}
			}

			if(s > 0){
				for( i = 1, tk2 = tk->slave; tk2 && i < s; i++, tk2 = tk2->next);
				if(tk2 == nil){
					release();
					return -1;
				}

				for( n = 1, tk = t->root; tk != tk2; tk = tk->siblings, n++){
					if(tk == nil){
						release();
						return -1;
					}
				}
			}else{
				n = 0;
			}
			
		}
	}

	if(n == 0){
		strcpy(up->genbuf, ".self");
		if(name != nil && strcmp(name, up->genbuf) != 0){
			release();
			return -1;
		}
		mkqid(&qid, (ulong)path | PATH(c->qid) | QCTL_NAME, c->qid.vers, QTFILE);
		devdir(c, qid, up->genbuf, 0, o->user, 0664, dp);
		release();
		return 1;
		
	}else if(tk2){
		snprint(up->genbuf, 127, "%s.%s", 
				tk2->name_tail
				? tk2->name_tail
				: tk2->name->name,
				tkmethod[tk2->type]->name
		);
		if(name != nil && strcmp(name, up->genbuf) != 0){
			release();
			return -1;
		}
		mkqid(&qid, (ulong)n | PATH(c->qid), c->qid.vers, (tk2->slave) ? QTDIR : QTFILE);
		devdir(c, qid, up->genbuf, 0, o->user, (tk2->slave) ? DMDIR|0555 : 0664, dp);
		release();
		return 1;
	}else{
		release();
		return -1;
	}

#if 0
		perm = tab->perm;
		if((perm & 7) == 0)
			perm = (perm|(perm>>3)|(perm>>6)) & o->pgrp->progmode;
		
		len = tab->length;
		mkqid(&qid, /*path|tab->qid.path*/ n, c->qid.vers, (tk2->slave) ? QTDIR : QTFILE);
		devdir(c, qid, tab->name, len, o->user, perm, dp);
		release();
		return 1;
#endif

#if 0
		{
			//tk = tkr->slave;
			//if (tk->name != nil){
			//	printf("(root (%d)) tk_el=%s, tk_flag=%d\n", PID(c->qid), tk->name->name, (tk->flag & Tkdestroy));
			//}
			if(tk->master == tkr){
				printf("\n");
				
				tk2 = tk; 
				i = 0;
				while( 1 ){
					printf("(%d) ", PID(c->qid));
					for(j = 0; j < i; j++)
						printf("|..");
					if (tk2->name != nil){
						printf(" %s, type=%d, tk_flag=%d", tk2->name->name, tk2->type, (tk2->flag & Tkdestroy));
					}
					printf("\n");
					
					if(tk2->slave){
						tk2 = tk2->slave;
						i++;
					}else if(tk2->next){
						tk2 = tk2->next;
					}else{
						tk2 = tk2->master;
						i--;
						if( tk2 == nil || tk2 == tkr)
							break;
						tk2 = tk2->next;
						if( tk2 == nil )
							break;
					}
				}
				printf("\n");
			}
		}
	
	}
//	release();


	}
#endif










#if 0
	if(s >= nelem(guitab))
		return -1;
	tab = &guitab[s];
	path = PATH(c->qid);

	acquire();
	p = progpid(PID(c->qid));
	if(p == nil) {
		release();
		return -1;
	}

	o = p->osenv;

	perm = tab->perm;
	if((perm & 7) == 0)
		perm = (perm|(perm>>3)|(perm>>6)) & o->pgrp->progmode;

	len = tab->length;
	mkqid(&qid, path|tab->qid.path, c->qid.vers, /*QTDIR*/QTFILE);
	devdir(c, qid, tab->name, len, o->user, perm, dp);
	release();
	return 1;
	
#endif
}





static void
guiinit(void)
{
	//gui_file_init();
}


static void
guishutdown(void)
{
}


static Chan*
guiattach(char *spec)
{
	return devattach('G', spec);
}


static Walkqid*
guiwalk(Chan *c, Chan *nc, char **name, int nname)
{
	return devwalk(c, nc, name, nname, 0, 0, guigen);
}


static int
guistat(Chan *c, uchar *db, int n)
{
	return devstat(c, db, n, 0, 0, guigen);
}


static Chan*
guiopen(Chan *c, int omode)
{
	Prog *p;
	Osenv *o;
//	Progctl *ctl;
	int perm;

	if(c->qid.type & QTDIR)
		return devopen(c, omode, 0, 0, guigen);

	acquire();
	if (waserror()) {
		release();
		nexterror();
	}
	p = progpid(PID(c->qid));
	if(p == nil)
		error(Ethread);
	o = p->osenv;
	perm = 0777; //progdir[QID(c->qid)-1].perm;
	if((perm & 7) == 0)
		perm = (perm|(perm>>3)|(perm>>6)) & o->pgrp->progmode;
	devpermcheck(o->user, perm, omode);
	omode = openmode(omode);

//LOGI("%s: %d 3 path=%d", /*__func__*/"guiopen", __LINE__, c->qid.path);
//	switch(c->qid.path) {
#if 0
	switch(QID(c->qid)){
	case Qdir:
	case Qguictl:
		break;
	case Qgui:
LOGI("%s: %d 3 omode=%d\n", /*__func__*/"guiopen", __LINE__, omode);
		_pid = 0;
		switch(omode & 3){
			case OREAD:
				break;
			
			case OWRITE:
				break;
		}
		
		//gui_file_open(c, c->mode);
		break;
	default:
		error(Egreg);
	}
#endif

	poperror();
	release();
	c->offset = 0;
	c->mode = omode;
	c->flag |= COPEN;
	return c;
}


static void
guiclose(Chan *c)
{
	if((c->flag & COPEN) == 0)
		return;

#if 0
//	switch(c->qid.path) {
	switch(QID(c->qid)){
	case Qdir:
	case Qguictl:
		break;
	case Qgui:
		_pid = 0;
		//gui_file_close(c);
		break;
	default:
		error(Egreg);
	}
#endif
}


static long
guiread(Chan *c, void *va, long count, vlong offset)
{
	Prog *p;
	char *buf;
	int n;
	
	int len = 0;

	Osenv *o;

	
	if(c->qid.type & QTDIR)
		return devdirread(c, (char*)va, count, 0, 0, guigen);


	acquire();
	if (waserror()) {
		release();
		nexterror();
	}
	p = progpid(PID(c->qid));
	if(p == nil)
		error(Ethread);

#if 0
//	switch(c->qid.path) {
	switch(QID(c->qid)){
	case Qgui:
		acquire();
		p = progpid(PID(c->qid));
		if(p == nil || p->state == Pexiting || p->R.M == H) {
			release();
			snprint(up->genbuf, sizeof(up->genbuf), "%8lud %8d %s %#p",
				PID(c->qid),
				0,
//				eve,
//				progtime(0, timebuf, timebuf+sizeof(timebuf)),
//				progstate[Pexiting],
//				0,
				"[$Sys]",
				nil);
			return readstr(offset, va, n, up->genbuf);
		}
		modstatus(&p->R, mbuf, sizeof(mbuf));
		o = p->osenv;
		snprint(up->genbuf, sizeof(up->genbuf), "%8d %8d %10s %s %#p", //"%8d %8d %10s %s %10s %5dK %s",
			p->pid,
			p->group!=nil? p->group->id: 0,
			o->user,
//			progtime(p->ticks, timebuf, timebuf+sizeof(timebuf)),
//			progstate[p->state],
//			progsize(p),
			mbuf,
			p->tktop);

		printf("\n-- (%d) --\n", PID(c->qid));

		if(p->tktop){
			TkTop *t = p->tktop;
			Tk *tk, *tk2, *tkr;
			int i, j;

			tkr = t->root;
			//for( tk = t->root; tk; tk = tk->siblings )
			{
				tk = tkr->slave;
				//if (tk->name != nil){
				//	printf("(root (%d)) tk_el=%s, tk_flag=%d\n", PID(c->qid), tk->name->name, (tk->flag & Tkdestroy));
				//}
				if(tk->master == tkr){
					printf("\n");
					
					tk2 = tk; 
					i = 0;
					while( 1 ){
						printf("(%d) ", PID(c->qid));
						for(j = 0; j < i; j++)
							printf("|..");
						if (tk2->name != nil){
							printf(" %s, type=%d, tk_flag=%d", tk2->name->name, tk2->type, (tk2->flag & Tkdestroy));
						}
						printf("\n");
						
						if(tk2->slave){
							tk2 = tk2->slave;
							i++;
						}else if(tk2->next){
							tk2 = tk2->next;
						}else{
							tk2 = tk2->master;
							i--;
							if( tk2 == nil || tk2 == tkr)
								break;
							tk2 = tk2->next;
							if( tk2 == nil )
								break;
						}
					}
					printf("\n");
				}
			}

		}
		release();
		return readstr(offset, va, n, up->genbuf);
//LOGI("\n%s: %d, (currun()=%p) tktop=%p\n", /*__func__*/"guiread", __LINE__, 
//							currun(), currun() ? (currun())->tktop : 0 );
//LOGI("%s: %d, (up=%p) tktop=%p\n", /*__func__*/"guiread", __LINE__, up, (up)->tktop);
//		return 0; //count;
	
	case Qguictl:
		buf = smalloc(READSTR);
		if(waserror()){
			free(buf);
			nexterror();
		}
		n = 0; //ctlsummary(buf, READSTR, getguidev());
		count = readstr(offset, va, n, buf);
		poperror();
		free(buf);
		return count;
	}
	return 0;
#endif

	if(offset == 0 && p->tktop){
		TkTop *t;
		Tk *tkr, *tk, *tk2;
		int i, j, k, n;

		t = p->tktop;
		
		tkr = t->root;
		n = QID(c->qid);
		
		for( i = 1, tk = tkr; i < n; i++, tk = tk->siblings ){
			if(tk == nil){
				release();
				return -1;
			}
		}

		tk2 = tk;
		
		if(tk2){
			char *va2 = va;
			TkOption **opts;
			
			i = 0;
		
			if((uint)tk2->type < TKwidgets)
				i += snprint(va2+i, count-i, "type=%s;\n", tkmethod[tk2->type]->name);
			else
				i += snprint(va2+i, count-i, "type=TYPE#%#ux;\n", tk2->type);
			
			if(tk2->name == nil || (ulong)tk2->name < 512)
				i += snprint(va2+i, count-i, "name=%p;\n", tk2->name);
			else
				i += snprint(va2+i, count-i, "name='%s';\n", tkname(tk2));

//			i += snprint(va2+i, count-i, "x=%d; y=%d; w=%d; h=%d;\n", 
//										tk2->act.x, tk2->act.y, tk2->act.width, tk2->act.height);

			i += snprint(va2+i, count-i, "\n# Options:\n# --------\n\n");
			opts = tkmethod[tk2->type]->opts;
			for(j=0; opts[j] != nil; j++){
				for(k=0; opts[j][k].o != nil; k++ ){
					TkOption *opt = &opts[j][k];
					char buf[256];
					char *rv = nil;

					if(opt->o != nil){
						snprint(buf, 255, "%s cget %s", tkname(tk2), opt->o);
						tksinglecmd(t, buf, &rv);
						if(rv){
							i += snprint(va2+i, count-i, "%s=%s;\n", opt->o, rv);
							free(rv);
						}
					}
				}
				i += snprint(va2+i, count-i, "\n");
			}

//			i += snprint(va2+i, count-i, "# tk %#p; \nflag=%#ux; \ngrid=%#p; \n", tk2, tk2->flag, tk2->grid);
			
//			if(tk2->parent != nil)
//				i += snprint(va2+i, count-i, "parent=[%#p %q];\n", tk2->parent, tkname(tk2->parent));
			
//			if(tk2->master != nil)
//				i += snprint(va2+i, count-i, "master=[%#p %q];\n", tk2->master, tkname(tk2->master));

/**/
			if(tk2->slave != nil){
				Tk *sl;
				i += snprint(va2+i, count-i, "\n# Slaves:\n# -------\n\n");
				for(sl = tk2->slave; sl != nil; sl = sl->next)
					i += snprint(va2+i, count-i, "# [%q %s];\n", tkname(sl), tkmethod[sl->type]->name);
			}
			i += snprint(va2+i, count-i, "\n");
/**/

			tk = tk2;
			len = i;
			n = i;
			if(tk->type == TKcanvas)
			{
				TkCanvas *c;
				TkCitem *it;
				TkCwind *w;
				char v1[Tkminitem], v2[Tkminitem];
				int i;
			
				if(tk == nil)
					return len;
				
				n += snprint(va2+n, count-n, "\n# Canvas cmds:\n# ------------\n\n");
				
				c = TKobj(TkCanvas, tk);
				tkfprint(v1, c->width);
				tkfprint(v2, c->height);
				n += snprint(va2+n, count-n, "configure -width %s -height %s;\n", v1, v2);
				n += snprint(va2+n, count-n, "# focus %#p mouse %#p grab %#p\n\n", c->focus, c->mouse, c->grab);

				for(it = c->head; it != nil; it = it->next){
					n += snprint(va2+n, count-n, "create %q", tkcimethod[it->type].name);
					for(i = 0; i < it->p.npoint; i++){
						tkfprint(v1, it->p.parampt[i].x);
						tkfprint(v2, it->p.parampt[i].y);
						n += snprint(va2+n, count-n, " %s %s", v1, v2);
					}
					n += snprint(va2+n, count-n, ";\n");
					
					if(it->type == TkCVwindow){
						w = TKobj(TkCwind, it);
						if(w->sub != nil)
							n += snprint(va2+n, count-n, " -window %q", tkname(w->sub));
						n += snprint(va2+n, count-n, " # item %#p id %d sub %#p focus [%#p %q];\n", it, it->id, w->sub, w->focus, tkname(w->focus));
					}else
						n += snprint(va2+n, count-n, "# item %#p id %d;\n", it, it->id);
				}
			}
//			tkcvsdump(tk);

			len = n;
		}
		
	}

	poperror();
	release();

	return len;

}


static long
guiwrite(Chan *c, void *va, long count, vlong offset)
{
	Prog *p;

	if(c->qid.type & QTDIR)
		error(Eisdir);

	acquire();
	if(waserror()) {
		release();
		nexterror();
	}
	p = progpid(PID(c->qid));
	if(p == nil)
		error(Ethread);

/*
	switch(QID(c->qid)){
	case Qgui:
		if(count > 0){
//			_pid = atoi((char*)va);
		}
//LOGI("%s: %d", __func__, __LINE__);
		return count; //gui_file_write(c, va, count, offset);

	case Qguictl:
		return count;
		//return gui_ctl_write(c, va, count, offset);
	}
*/
	return 0;
}


static int
guiwstat(Chan *c, uchar *db, int n)
{
	Dir d;
	Prog *p;
	char *u;
	Osenv *o;

	if(c->qid.type&QTDIR)
		error(Eperm);
	acquire();
	p = progpid(PID(c->qid));
	if(p == nil) {
		release();
		error(Ethread);
	}

	u = up->env->user;
	o = p->osenv;
	if(strcmp(u, o->user) != 0 && strcmp(u, eve) != 0) {
		release();
		error(Eperm);
	}

	n = convM2D(db, n, &d, nil);
	if(n == 0){
		release();
		error(Eshortstat);
	}
	if(d.mode != ~0UL)
		o->pgrp->progmode = d.mode&0777;
	release();
	return n;
}


#if 0
static int
str2val(svp_t* t, char* s, ulong *v)
{
	if(t == nil || s == nil)
		return 0;
	for(; t->s != nil; t++) {
		if(strncmp(t->s, s, strlen(t->s)) == 0) {
			*v = t->v;
			return 1;
		}
	}
	return 0;
}

static char*
val2str(svp_t* t, ulong v)
{
	if(t == nil)
		return nil;
	for(; t->s != nil; t++)
		if(t->v == v)
			return t->s;
	return nil;
}

static int 
sval(char* buf, ulong* v, ulong max, ulong min)
{
	unsigned long val = strtoul(buf, 0, 10);

	if(val > max || val < min)
		return 0;
	*v = val;
	return 1;
}
#endif

Dev guidevtab = {
        'G',
        "gui",

        guiinit,
        guiattach,
        guiwalk,
        guistat,
        guiopen,
        devcreate,
        guiclose,
        guiread,
        devbread,
        guiwrite,
        devbwrite,
        devremove,
        guiwstat
};

