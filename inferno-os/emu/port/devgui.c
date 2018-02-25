#include	"dat.h"
#include	"fns.h"
#include	"error.h"
//#include	"audio.h"

#include "interp.h"

#include "draw.h"
#include "tk.h"

#include "../libtk/canvs.h"
#include "isa.h"
#include "../libinterp/runt.h"

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
//#define QIDgetRV(q)	( (ulong)( (uvlong)(q).path >> (sizeof(ulong)*8) ) )
//#define QIDsetRV(q, v)	( (uvlong)(q).path | (uvlong)v << (sizeof(ulong)*8) )




typedef struct _rslt_string rslt_string;
struct _rslt_string {
	rslt_string *next;
	ulong		path;
	char 		str[1];
};

rslt_string *root_rslt_strings = nil;



extern char rootdir[];


void guictl_wr_pars(char* in, int count);


extern TkMethod *tkmethod[];
extern TkCimeth tkcimethod[];

extern char* tksinglecmd(TkTop *t, char *arg, char **val);
//extern char* tkwidgetcmd(TkTop *t, Tk *tk, char *arg, char **val);



static Tk* 
qid2tk(Qid *qid, TkTop *t){
	ulong path = QID(*qid); //PATH(c->qid) >> QSHIFT;
	int i;
	Tk *tkr, *tk;
	
	tkr = t->root;
	
	for( i = 1, tk = tkr; i < path; i++, tk = tk->siblings ){
		if(tk == nil){
			return nil;
		}
	}
	return tk;
}

static int 
tk2idx(TkTop *t, Tk *tk){
	int i;
	Tk *tkr, *tk2;
	
	tkr = t->root;
	
	for( i = 1, tk2 = tkr; tk2 != tk; tk2 = tk2->siblings, i++){
		if(tk2 == nil){
			return -1;
		}
	}
	return i;
}

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

		tk = qid2tk(&c->qid, t);
		if(tk == nil){
			error(Enonexist);
		}
		if(tk)
			tk = tk->master;

		if( !tk /*|| tk == tkr*/){
			mkqid(&qid, Qdir, 0, QTDIR);
			devdir(c, qid, "#G", 0, eve, DMDIR|0555, dp);
			return 1;
		}

		n = tk2idx(t, tk);
		if(n == -1){
			error(Enonexist);
		}

		snprint(up->genbuf, 127, "%s", 
				tk->name_tail
				? tk->name_tail
				: tkname(tk)
		);
		mkqid(&qid, (ulong)n | PATH(c->qid), c->qid.vers, QTDIR);
		o =  p->osenv;
		devdir(c, qid, up->genbuf, 0,  o->user, DMDIR|0777, dp);
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
		devdir(c, qid, up->genbuf, 0, o->user, DMDIR|0777, dp);
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

			tk = qid2tk(&c->qid, t);
			if(tk == nil){
				release();
				return -1;
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
							: tkname(tk2) ) 
					){
						break;
					}
				}
				if(pr != nil)
					*pr = '.';
				if(tk2 == nil){
					release();
					return -1;
				}
				
				n = tk2idx(t, tk2);
				if(n == -1){
					release();
					return -1;
				}
			}else{
				n = 0;
			}

		}
		else{
			t = p->tktop;
		
			tkr = t->root;
			n = path;
			
			tk = qid2tk(&c->qid, t);
			if(tk == nil){
				release();
				return -1;
			}

			if(s > 0){
				for( i = 1, tk2 = tk->slave; tk2 && i < s; i++, tk2 = tk2->next);
				if(tk2 == nil){
					release();
					return -1;
				}

				n = tk2idx(t, tk2);
				if(n == -1){
					release();
					return -1;
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
				: tkname(tk2),
				tkmethod[tk2->type]->name
		);
		if(name != nil && strcmp(name, up->genbuf) != 0){
			release();
			return -1;
		}
		if(tk2->slave) 
			tk2->is_container = 1;
		mkqid(&qid, (ulong)n | PATH(c->qid), c->qid.vers, (tk2->is_container) ? QTDIR : QTFILE);
		devdir(c, qid, up->genbuf, 0, o->user, (tk2->is_container) ? DMDIR|0777 : 0664, dp);
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
	rslt_string *r, *or;

	if((c->flag & COPEN) == 0)
		return;

	for(r = root_rslt_strings, or = nil; r != nil && r->path != (ulong)c->qid.path; or = r, r = r->next);
	if(r != nil){
		if(or == nil)
			root_rslt_strings = r->next;
		else
			or->next = r->next;
		
		free(r);
	}
}


void
guicreate(Chan *c, char *name, int mode, ulong perm)
{
	Prog *p;
	
	TkTop *t;
	Tk    *tk;

	char *rt, *type;

	Tk *tk2 = nil;	
	

	if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
		error(Efilename);
	
	if((ulong)c->qid.path != Qdir) {
		TkMethod *tkm;
		int i;
	
		type = nil;
		
		for(rt = name; *rt != '\0' && *rt != '.'; rt++);
		if(*rt){
			*rt = '\0';
			type = rt+1;
		}else{
			rt = nil;
		}
		if(type == nil){
			error(Eperm);
			return;
		}

		for(i=0, tkm = nil; i < TKwidgets; i++){
			tkm = tkmethod[i];
			if( !strcmp(tkm->name, type) )
				break;
		}
		if(tkm == nil){
			if(rt)
				*rt = '.';
			error(Eperm);
			return;
		}
	
		acquire();
		p = progpid(PID(c->qid));
		if(p == nil) {
			if(rt)
				*rt = '.';
			release();
			return;
		}
		t = p->tktop;

		if(!t){
			F_Tk_toplevel tf;
			F_Display_allocate df;
			//Draw_Display *dd;
			void *df_ret = H;
			void *tf_ret = H;

			df.ret = &df_ret;
			df.dev = H;
			Display_allocate( &df );

			tf.ret = &tf_ret;
			tf.d = *df.ret;
			tf.arg = H;
			Tk_toplevel( &tf );

			t = *tf.ret;
			poolimmutable(D2H(t));

			p->tktop = t;
			t->prog = p;
			//destroy(df_ret);
		}

		tk = qid2tk(&c->qid, t);
		if(tk == nil){
			if(rt)
				*rt = '.';
			error(Eperm);
			release();
			return;
		}

		{
			char buf[100];
			char *e, *rv;
			char *par_tkname = tkname(tk);
			
			if(par_tkname){
				snprint(buf, sizeof(buf), "%s %s%s%s", 
							type, 
							par_tkname, 
							(*par_tkname == '.' && *(char*)(par_tkname+1) == '\0') 
											? "" 
											: ".", 
							name
				);
				rv = nil;
				e = tksinglecmd(t, buf, &rv);
				if(!e){
					if(rv){
						LOGI("AFTER CR %s", rv);
						free(rv);
					}
					
					snprint(buf, sizeof(buf), "pack %s%s%s -side left",
								par_tkname, 
								(*par_tkname == '.' && *(char*)(par_tkname+1) == '\0') 
												? "" 
												: ".", 
								name
					);
					e = tksinglecmd(t, buf, nil);
					if(!e){
						tksinglecmd(t, "update", nil);

						for( tk2 = tk->slave; tk2; tk2 = tk2->next){
							if( !strcmp(name, 
									tk2->name_tail
									? tk2->name_tail
									: tkname(tk2) ) 
							){
								break;
							}
						}
						if(rt != nil)
							*rt = '.';
						if(tk2 == nil){
							release();
							return;
						}
						if(perm & DMDIR)
							tk2->is_container = 1;
					}			
				}
			}
		}

		if(tk2){
			int n = tk2idx(t, tk2);
			if(n == -1){
				release();
				return;
			}
			mkqid(&c->qid, (ulong)n | PATH(c->qid), c->qid.vers, (tk2->is_container) ? QTDIR : QTFILE);
			c->mode = openmode(mode);
			c->offset = 0;
			c->flag |= COPEN;
		}

		if(rt)
			*rt = '.';
		release();
		return;

		
//	o = p->osenv;
//	sprint(up->genbuf, "%lud", pid);
//	if(name != nil && strcmp(name, up->genbuf) != 0){
//		release();
//		return -1;
//	}
	}
}


void
guiremove(Chan *c)
{
	Prog *p;
	
	TkTop *t;
	Tk    *tk;
	Tk *tk2 = nil;	

	char *rt;
	char *name = c->name->s;

	if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
		error(Efilename);
	
	if((ulong)c->qid.path != Qdir) {
		acquire();
		p = progpid(PID(c->qid));
		if(p == nil) {
			release();
			return;
		}
		t = p->tktop;

		tk = qid2tk(&c->qid, t);
		if(tk == nil){
			release();
			error(Eperm);
			return;
		}
		else{
			char buf[100];
			char *e, *rv;
			char *par_tkname = tkname(tk);
			
			if(par_tkname){
				snprint(buf, sizeof(buf), "destroy %s", par_tkname );
				rv = nil;
				e = tksinglecmd(t, buf, &rv);
				if(!e){
					if(rv){
						free(rv);
					}
					tksinglecmd(t, "update", nil);
				}
			}
		}
	}

	release();
}


static long
guiread(Chan *c, void *va, long count, vlong offset)
{
	Prog *p;
	char *buf;
	int n;
	
	int len = 0;

	Osenv *o;

	rslt_string *r, *or;

	
	if(c->qid.type & QTDIR)
		return devdirread(c, (char*)va, count, 0, 0, guigen);

	for(r = root_rslt_strings, or = nil; r != nil && r->path != (ulong)c->qid.path; or = r, r = r->next);
	if(r != nil){
		char *rv = r->str;
		int l = strlen(rv);
		
		if(l > count)
			l = count;
		memcpy(va, rv, l);

		if(or == nil)
			root_rslt_strings = r->next;
		else
			or->next = r->next;
		
		free(r);

		return l;
	}


	acquire();
	if (waserror()) {
		release();
		nexterror();
	}
	p = progpid(PID(c->qid));
	if(p == nil)
		error(Ethread);

	if(offset == 0 && p->tktop){
		TkTop *t;
		Tk *tkr, *tk, *tk2;
		int i, j, k, n;

		t = p->tktop;
		
		tkr = t->root;
		n = QID(c->qid);
		
		tk = qid2tk(&c->qid, t);
		if(tk == nil){
			release();
			return 0;
		}

		tk2 = tk;
		if(tk2){
			char *va2 = va;
			TkOption **opts;
		
			TkCmdtab *cmd = tkmethod[tk2->type]->cmd;
			char *rv;
			
			i = 0;
		
			if((uint)tk2->type < TKwidgets)
				i += snprint(va2+i, count-i, "# type=%s\n", tkmethod[tk2->type]->name);
			else
				i += snprint(va2+i, count-i, "# type=TYPE#%#ux\n", tk2->type);
			
			if(tk2->name == nil || (ulong)tk2->name < 512)
				i += snprint(va2+i, count-i, "# name=%p\n", tk2->name);
			else
				i += snprint(va2+i, count-i, "# name='%s'\n", tkname(tk2));

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
							i += snprint(va2+i, count-i, "\"configure -%s \t%s\"\n", opt->o, rv);
							free(rv);
						}
					}
				}
				i += snprint(va2+i, count-i, "\n");
			}

			if(cmd != nil){
				i += snprint(va2+i, count-i, "\n# Other Data:\n# -----------\n\n");
				
				for(j = 0; cmd[j].name != nil; j++){
					if(cmd[j].flag == TK_CMD_OUT){
						char *e;

						rv = nil;
						e = cmd[j].fn(tk2, "", &rv);
						if(!e)
							i += snprint(va2+i, count-i, "\"%s %s\"\n", cmd[j].name, rv);
						if(rv)
							free(rv);
					}
				}
			}
			
//			i += snprint(va2+i, count-i, "# tk %#p; \nflag=%#ux; \ngrid=%#p; \n", tk2, tk2->flag, tk2->grid);

			if(tk2->slave != nil){
				Tk *sl;
				i += snprint(va2+i, count-i, "\n# Slaves:\n# -------\n\n");
				for(sl = tk2->slave; sl != nil; sl = sl->next)
					i += snprint(va2+i, count-i, "# [%q %s]\n", tkname(sl), tkmethod[sl->type]->name);
			}
			i += snprint(va2+i, count-i, "\n");

			tk = tk2;
			len = i;
			n = i;
			if(tk->type == TKtext)
			{
				char buf[256];
				char *rv = nil;

				snprint(buf, 255, "%s get 1.0 end", tkname(tk) );
				tksinglecmd(t, buf, &rv);
				if(rv){
					n += snprint(va2+n, count-n, "\"insert end '%s\"\n", rv);
					free(rv);
				}
			}else
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
				n += snprint(va2+n, count-n, "configure -width %s -height %s\n", v1, v2);
				n += snprint(va2+n, count-n, "# focus %#p mouse %#p grab %#p\n\n", c->focus, c->mouse, c->grab);

				for(it = c->head; it != nil; it = it->next){
					n += snprint(va2+n, count-n, "create %q", tkcimethod[it->type].name);
					for(i = 0; i < it->p.npoint; i++){
						tkfprint(v1, it->p.parampt[i].x);
						tkfprint(v2, it->p.parampt[i].y);
						n += snprint(va2+n, count-n, " %s %s", v1, v2);
					}
					n += snprint(va2+n, count-n, "\n");
					
					if(it->type == TkCVwindow){
						w = TKobj(TkCwind, it);
						if(w->sub != nil)
							n += snprint(va2+n, count-n, " -window %q", tkname(w->sub));
						n += snprint(va2+n, count-n, " # item %#p id %d sub %#p focus [%#p %q]\n", it, it->id, w->sub, w->focus, tkname(w->focus));
					}else
						n += snprint(va2+n, count-n, "# item %#p id %d\n", it, it->id);
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
	int totl = 0;

	if(c->qid.type & QTDIR)
		error(Eisdir);

	acquire();
	if(waserror()) {
		release();
		nexterror();
	}
	p = progpid(PID(c->qid));
	if(p == nil){
		error(Ethread);
	}
	
	if(offset == 0 && count > 0 && p->tktop){
		TkTop *t;
		Tk *tkr, *tk;
		int i, j, n;
		char *args[100], *rvs[100];
		char *va2 = va;

		int pars = 0;
		int cmnt = 0;

		j = 0; rvs[0] = nil; args[0] = nil;
		
		for(i = 0, j = 0; i < count && va2[i] != '\0' && j < 100-1; i++){
			char c = va2[i];
			
			if(c == '"'){
				pars ^= 1;
				va2[i] = '\0';
			}else
			if(
				(!pars) && 
				(c == '\n' || c == '\r')
			){
				cmnt = 0;
				va2[i] = '\0';
				if(args[j] != nil){
					j++;
					args[j] = nil;
				}
			}else{
				if(args[j] == nil){
					if(c == '#' || cmnt){
						cmnt = 1;
					}else{
						args[j] = &va2[i];
						args[j+1] = nil;
					}
				}
			}
		}
		if(j < 100){
			j++;
			args[j] = nil;
		}
	
		t = p->tktop;
		
		tkr = t->root;
		n = QID(c->qid);
		
		tk = qid2tk(&c->qid, t);
		if(tk == nil){
			release();
			return 0;
		}
		
		{
			TkOption **opts = tkmethod[tk->type]->opts;
			TkCmdtab *cmd = tkmethod[tk->type]->cmd;	
			rslt_string *r = nil;
			int rl = 0;

			for(i = 0, j = 0; args[i] != nil; i++){
				char *buf;
				int blen;
				char *rv = nil;
				char *arg = args[i];
				char *tknm = tkname(tk);
				
				blen = strlen( tknm ) + strlen( arg ) + 2 + 2;
				buf = malloc( blen );
				
				snprint(buf, blen, "%s %s", tknm, arg);

				if( !tksinglecmd(t, buf, &rv) )
					tksinglecmd(t, "update", nil);
				free(buf);

				if(rv != nil){
					rl += strlen(rv) + 1;
					
					rvs[j] = rv;
					j++;
					rvs[j] = nil;
				}
			}

			r = malloc(sizeof(rslt_string) + rl + 2);

			rl = 0;
			for(i = 0; rvs[i] != 0 && i < j; i++){
				int l = strlen( rvs[i] );
				
				memcpy(&(r->str[rl]), rvs[i], l);
				rl += l;
				r->str[rl] = '\n';
				rl++;

				free(rvs[i]);
			}
			r->str[rl] = '\0';
			
			//QIDsetRV(c->qid, r);
			r->next = root_rslt_strings;
			r->path = (ulong)c->qid.path;
			root_rslt_strings = r;

			totl = count;
		}
	}
	poperror();
	release();

	return totl;
}


static int
guiwstat(Chan *c, uchar *db, int n)
{
	Dir d;
	Prog *p;
	char *u;
	Osenv *o;

	if(c->qid.type & QTDIR)
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
        guicreate,
        guiclose,
        guiread,
        devbread,
        guiwrite,
        devbwrite,
        guiremove,
        guiwstat
};

