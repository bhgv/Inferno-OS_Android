#define Unknown win_Unknown
#define UNICODE
#include	<windows.h>
#include <winbase.h>
#include	<winsock.h>
#undef Unknown
#include	<excpt.h>
#include	"dat.h"
#include	"fns.h"
#include	"error.h"
#include	"r16.h"
#include	"ieplugin.h"

extern int	SYS_SLEEP = 2;
extern int SOCK_SELECT = 3;
#define	MAXSLEEPERS	1500

extern Plugin*	plugin;
extern void	newiop();
extern int		sendiop();

DWORD		PlatformId;
static char*	path;
static HANDLE	kbdh = INVALID_HANDLE_VALUE;
static HANDLE	conh = INVALID_HANDLE_VALUE;
static int		sleepers;

static ulong erendezvous(void*, ulong);

__declspec(thread)       Proc    *up;

HANDLE	ntfd2h(int);
int	nth2fd(HANDLE);
char *hosttype = "Nt";

static void
pfree(Proc *p)
{
	Osenv *e;

	lock(&procs.l);
	if(p->prev)
		p->prev->next = p->next;
	else
		procs.head = p->next;

	if(p->next)
		p->next->prev = p->prev;
	else
		procs.tail = p->prev;
	unlock(&procs.l);

	e = p->env;
	if(e != nil) {
		closefgrp(e->fgrp);
		closepgrp(e->pgrp);
		closeegrp(e->egrp);
		closesigs(e->sigs);
	}
	free(e->user);
	free(p->prog);
	free(p);
}

void
osblock(void)
{
	erendezvous(up, 0);
}

void
osready(Proc *p)
{
	erendezvous(p, 0);
}


void
pexit(char *msg, int t)
{
	pfree(up);
	ExitThread(0);
}

LONG TrapHandler(LPEXCEPTION_POINTERS ureg);

__cdecl
Exhandler(EXCEPTION_RECORD *rec, void *frame, CONTEXT *context, void *dcon)
{
	EXCEPTION_POINTERS ep;
	ep.ExceptionRecord = rec;
	ep.ContextRecord = context;
	TrapHandler(&ep);
	return ExceptionContinueExecution;
}

DWORD WINAPI
tramp(LPVOID p)
{
	// install our own exception handler
	// replacing all others installed on this thread
	DWORD handler = (DWORD)Exhandler;
	_asm {
		mov eax,handler
		push eax
		mov eax,-1
		push eax
		mov fs:[0],esp
	}
		
	up = p;
	up->func(up->arg);
	pexit("", 0);
	// should never get here but tidy up anyway
	_asm {
		mov fs:[0],-1
		add esp, 8
	}
	return 0;
}

void
kproc(char *name, void (*func)(void*), void *arg, int flags)
{
	DWORD h;
	Proc *p;
	Pgrp *pg;
	Fgrp *fg;
	Egrp *eg;

	p = newproc();
	if(p == nil)
		panic("out of kernel processes");
		
	if(flags & KPDUPPG) {
		pg = up->env->pgrp;
		incref(&pg->r);
		p->env->pgrp = pg;
	}
	if(flags & KPDUPFDG) {
		fg = up->env->fgrp;
		incref(&fg->r);
		p->env->fgrp = fg;
	}
	if(flags & KPDUPENVG) {
		eg = up->env->egrp;
		incref(&eg->r);
		p->env->egrp = eg;
	}

	p->env->ui = up->env->ui;
	kstrdup(&p->env->user, up->env->user);
	strcpy(p->text, name);

	p->func = func;
	p->arg = arg;

	lock(&procs.l);
	if(procs.tail != nil) {
		p->prev = procs.tail;
		procs.tail->next = p;
	}
	else {
		procs.head = p;
		p->prev = nil;
	}
	procs.tail = p;
	unlock(&procs.l);

	p->pid = (int)CreateThread(0, 16384, tramp, p, 0, &h);
	if(p->pid <= 0)
		panic("ran out of kernel processes");
}

#if(_WIN32_WINNT >= 0x0400)
void APIENTRY sleepintr(DWORD param)
{
}
#endif

void
oshostintr(Proc *p)
{
	if (p->syscall == SOCK_SELECT)
		return;
	p->intwait = 0;
#if(_WIN32_WINNT >= 0x0400)
	if(p->syscall == SYS_SLEEP) {
		QueueUserAPC(sleepintr, (HANDLE) p->pid, (DWORD) p->pid);
	}
#endif
}

void
oslongjmp(void *regs, osjmpbuf env, int val)
{
	USED(regs);
	longjmp(env, val);
}

int
readkbd(void)
{
	DWORD r;
	char buf[1];

	if(ReadFile(plugin->conin, buf, sizeof(buf), &r, 0) == FALSE)
		panic("keyboard fail");
	if (r == 0)
		panic("keyboard EOF");

	if(buf[0] == '\r')
		buf[0] = '\n';
	return buf[0];
}

void
cleanexit(int x)
{
	newiop();
	IOP.op = Iquit;
	sendiop();
	ExitProcess(x);
}

struct ecodes {
	DWORD	code;
	char*	name;
} ecodes[] = {
	EXCEPTION_ACCESS_VIOLATION,		"Segmentation violation",
	EXCEPTION_DATATYPE_MISALIGNMENT,	"Data Alignment",
	EXCEPTION_BREAKPOINT,                	"Breakpoint",
	EXCEPTION_SINGLE_STEP,               	"SingleStep",
	EXCEPTION_ARRAY_BOUNDS_EXCEEDED,	"Array Bounds Check",
	EXCEPTION_FLT_DENORMAL_OPERAND,		"Denormalized Float",
	EXCEPTION_FLT_DIVIDE_BY_ZERO,		"Floating Point Divide by Zero",
	EXCEPTION_FLT_INEXACT_RESULT,		"Inexact Floating Point",
	EXCEPTION_FLT_INVALID_OPERATION,	"Invalid Floating Operation",
	EXCEPTION_FLT_OVERFLOW,			"Floating Point Result Overflow",
	EXCEPTION_FLT_STACK_CHECK,		"Floating Point Stack Check",
	EXCEPTION_FLT_UNDERFLOW,		"Floating Point Result Underflow",
	EXCEPTION_INT_DIVIDE_BY_ZERO,		"Divide by Zero",
	EXCEPTION_INT_OVERFLOW,			"Integer Overflow",
	EXCEPTION_PRIV_INSTRUCTION,		"Privileged Instruction",
	EXCEPTION_IN_PAGE_ERROR,		"Page-in Error",
	EXCEPTION_ILLEGAL_INSTRUCTION,		"Illegal Instruction",
	EXCEPTION_NONCONTINUABLE_EXCEPTION,	"Non-Continuable Exception",
	EXCEPTION_STACK_OVERFLOW,		"Stack Overflow",
	EXCEPTION_INVALID_DISPOSITION,		"Invalid Disposition",
	EXCEPTION_GUARD_PAGE,			"Guard Page Violation",
	0,					nil
};

void
dodisfault(void)
{
	disfault(nil, up->env->errstr);
}

typedef struct Ereg Ereg;
struct Ereg {
	Ereg *prev;
	FARPROC handler;
};

void
dumpex()
{
	Ereg *er;
	int i;
	_asm { mov eax,fs:[0] };
	_asm { mov [er],eax };

	i = 0;
	while ((unsigned)er != ~0) {
		print("handler %ux\n", er->handler);
		i++;
	er = er->prev;
	}
	print("EXCEPTION CHAIN LENGTH = %d\n", i);
}

LONG
TrapHandler(LPEXCEPTION_POINTERS ureg)
{
	int i;
	char *name;
	DWORD code;
	// WORD pc;
	char buf[ERRMAX];

	code = ureg->ExceptionRecord->ExceptionCode;
	// pc = ureg->ContextRecord->Eip;

	name = nil;
	for(i = 0; i < nelem(ecodes); i++) {
		if(ecodes[i].code == code) {
			name = ecodes[i].name;
			break;
		}
	}

	if(name == nil) {
		snprint(buf, sizeof(buf), "Unrecognized Machine Trap (%.8lux)\n", code);
		name = buf;
	}
/*
	if(pc != 0) {
		snprint(buf, sizeof(buf), "%s: pc=0x%lux", name, pc);
		name = buf;
	}
*/
	/* YUCK! */
	strncpy(up->env->errstr, name, ERRMAX);
	switch (code) {
	case EXCEPTION_FLT_DENORMAL_OPERAND:
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
	case EXCEPTION_FLT_INEXACT_RESULT:
	case EXCEPTION_FLT_INVALID_OPERATION:
	case EXCEPTION_FLT_OVERFLOW:
	case EXCEPTION_FLT_STACK_CHECK:
	case EXCEPTION_FLT_UNDERFLOW:
		/* clear exception flags and register stack */
		_asm { fnclex };
		ureg->ContextRecord->FloatSave.StatusWord = 0x0000;
		ureg->ContextRecord->FloatSave.TagWord = 0xffff;
	}
	ureg->ContextRecord->Eip = (DWORD)dodisfault;
	return EXCEPTION_CONTINUE_EXECUTION;
}

static	int	rebootok = 0;	/* is shutdown -r supported? */

void
osreboot(char *file, char **argv)
{
	if(rebootok){
		execvp(file, argv);
		panic("reboot failure");
	}else
		error("reboot option not supported on this system");
}

void
libinit(char *imod)
{
	WSADATA wasdat;
//	DWORD lasterror, namelen;
	OSVERSIONINFO os;
//	char sys[64];

	os.dwOSVersionInfoSize = sizeof(os);
	if(!GetVersionEx(&os))
		panic("can't get os version");
	PlatformId = os.dwPlatformId;
	if (PlatformId == VER_PLATFORM_WIN32_NT) {	/* true for NT and 2000 */
		rebootok = 1;
	} else {
		rebootok = 0;
	}

	if((int)INVALID_HANDLE_VALUE != -1 || sizeof(HANDLE) != sizeof(int))
		panic("invalid handle value or size");

	if(WSAStartup(MAKEWORD(1, 1), &wasdat) != 0)
		panic("no winsock.dll");

//	gethostname(sys, sizeof(sys));
//	kstrdup(&ossysname, sys);
	kstrdup(&ossysname, "plugin");

//	if(sflag == 0)
//		SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)TrapHandler);

	path = getenv("PATH");
	if(path == nil)
		path = ".";

	up = newproc();
	if(up == nil)
		panic("cannot create kernel process");

	kstrdup(&eve, "system");
	emuinit(imod);
}

enum
{
	NHLOG	= 7,
	NHASH	= (1<<NHLOG)
};

typedef struct Tag Tag;
struct Tag
{
	void*	tag;
	ulong	val;
	HANDLE	pid;
	Tag*	next;
};

static	Tag*	ht[NHASH];
static	Tag*	ft;
static	Lock	hlock;
static	int	nsema;

ulong
erendezvous(void *tag, ulong value)
{
	int h;
	ulong rval;
	Tag *t, **l, *f;


	h = (ulong)tag & (NHASH-1);

	lock(&hlock);
	l = &ht[h];
	for(t = ht[h]; t; t = t->next) {
		if(t->tag == tag) {
			rval = t->val;
			t->val = value;
			t->tag = 0;
			unlock(&hlock);
			if(SetEvent(t->pid) == FALSE)
				panic("Release failed\n");
			return rval;		
		}
	}

	t = ft;
	if(t == 0) {
		t = malloc(sizeof(Tag));
		if(t == nil)
			panic("rendezvous: no memory");
		t->pid = CreateEvent(0, 0, 0, 0);
	}
	else
		ft = t->next;

	t->tag = tag;
	t->val = value;
	t->next = *l;
	*l = t;
	unlock(&hlock);

	if(WaitForSingleObject(t->pid, INFINITE) != WAIT_OBJECT_0)
		panic("WaitForSingleObject failed\n");

	lock(&hlock);
	rval = t->val;
	for(f = *l; f; f = f->next) {
		if(f == t) {
			*l = f->next;
			break;
		}
		l = &f->next;
	}
	t->next = ft;
	ft = t;
	unlock(&hlock);

	return rval;
}

void
FPsave(void *fptr)
{
	_asm {
		mov	eax, fptr
		fstenv	[eax]
	}
}

void
FPrestore(void *fptr)
{
	_asm {
		mov	eax, fptr
		fldenv	[eax]
	}
}

ulong
umult(ulong a, ulong b, ulong *high)
{
	ulong lo, hi;

	_asm {
		mov	eax, a
		mov	ecx, b
		MUL	ecx
		mov	lo, eax
		mov	hi, edx
	}
	*high = hi;
	return lo;
}

int
close(int fd)
{
	if(fd != -1)
		CloseHandle(ntfd2h(fd));
	return 0;
}

int
read(int fd, void *buf, uint n)
{
	if(!ReadFile(ntfd2h(fd), buf, n, &n, NULL))
		return -1;
	return n;
}

int
write(int fd, void *buf, uint n)
{
	if(fd == 1 || fd == 2){
		int w;
		if (plugin->conout == NULL)
			return n;
		if (!WriteFile(plugin->conout, buf, n, &w, NULL) || n != w)
			abort();
		return n;
	}
	if(!WriteFile(ntfd2h(fd), buf, n, &n, NULL))
		return -1;
	return n;
}

/*
 * map handles and fds.
 * this code assumes sizeof(HANDLE) == sizeof(int),
 * that INVALID_HANDLE_VALUE is -1, and assumes
 * that all tests of invalid fds check only for -1, not < 0
 */
int
nth2fd(HANDLE h)
{
	return (int)h;
}

HANDLE
ntfd2h(int fd)
{
	return (HANDLE)fd;
}

void
oslopri(void)
{
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_BELOW_NORMAL);
}

/* Resolve system header name conflict */
#undef Sleep
void
sleep(int secs)
{
	Sleep(secs*1000);
}

void*
sbrk(int size)
{
	void *brk;

	brk = VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE); 	
	if(brk == 0)
		return (void*)-1;

	return brk;
}

ulong
getcallerpc(void *arg)
{
	ulong cpc;
	_asm {
		mov eax, dword ptr [ebp]
		mov eax, dword ptr [eax+4]
		mov dword ptr cpc, eax
	}
	return cpc;
}

/*
ulong
getpc(void *arg, ulong *narg)
{
	ulong *a = arg, *fp, pc;

	if(a == nil){
		*narg = 0;
		return 0;
	}
	fp = a-2;
	pc = fp[1];
	fp = *(ulong**)fp;
	if(fp == nil)
		*narg = 0;
	else
		*narg = (ulong)(fp+2);
	return pc;
}
*/
	
/*
 * Return an abitrary millisecond clock time
 */
long
osmillisec(void)
{
	return GetTickCount();
}

#define SEC2MIN 60L
#define SEC2HOUR (60L*SEC2MIN)
#define SEC2DAY (24L*SEC2HOUR)

/*
 *  days per month plus days/year
 */
static	int	dmsize[] =
{
	365, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};
static	int	ldmsize[] =
{
	366, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

/*
 *  return the days/month for the given year
 */
static int*
yrsize(int yr)
{
	/* a leap year is a multiple of 4, excluding centuries
	 * that are not multiples of 400 */
	if( (yr % 4 == 0) && (yr % 100 != 0 || yr % 400 == 0) )
		return ldmsize;
	else
		return dmsize;
}

static long
tm2sec(SYSTEMTIME *tm)
{
	long secs;
	int i, *d2m;

	secs = 0;

	/*
	 *  seconds per year
	 */
	for(i = 1970; i < tm->wYear; i++){
		d2m = yrsize(i);
		secs += d2m[0] * SEC2DAY;
	}

	/*
	 *  seconds per month
	 */
	d2m = yrsize(tm->wYear);
	for(i = 1; i < tm->wMonth; i++)
		secs += d2m[i] * SEC2DAY;

	/*
	 * secs in last month
	 */
	secs += (tm->wDay-1) * SEC2DAY;

	/*
	 * hours, minutes, seconds
	 */
	secs += tm->wHour * SEC2HOUR;
	secs += tm->wMinute * SEC2MIN;
	secs += tm->wSecond;

	return secs;
}

/*
 * Return the time since the epoch in microseconds
 * The epoch is defined at 1 Jan 1970
 */
vlong
osusectime(void)
{
	SYSTEMTIME tm;
	vlong secs;

	GetSystemTime(&tm);
	secs = tm2sec(&tm);
	return secs * 1000000 + tm.wMilliseconds * 1000;
}

vlong
osnsec(void)
{
	return osusectime()*1000;	/* TO DO better */
}

int
osmillisleep(ulong milsec)
{
	up->syscall = 1;
	SleepEx(milsec, FALSE);
	up->syscall = 0;
	return 0;
}

int
limbosleep(ulong milsec)
{
	if (sleepers > MAXSLEEPERS)
		return -1;
	sleepers++;
	up->syscall = SYS_SLEEP;
	SleepEx(milsec, TRUE);
	up->syscall = 0;
	sleepers--;
	return 0;
}

void
osyield(void)
{	
	sleep(0);
}

void
ospause(void)
{
      for(;;)
              sleep(1000000);
}

/*
 * these should never be called, and are included
 * as stubs since we are linking against a library which defines them
 */
int
open(const char *path, int how, ...)
{
	panic("open");
	return -1;
}

int
creat(const char *path, int how)
{
	panic("creat");
	return -1;
}

int
stat(const char *path, struct stat *sp)
{
	panic("stat");
	return -1;
}

int
chown(const char *path, int uid, int gid)
{
	panic("chown");
	return -1;
}

int
chmod(const char *path, int mode)
{
	panic("chmod");
	return -1;
}

void
link(char *path, char *next)
{
	panic("link");
}

int
segflush(void *a, ulong n)
{
	return 0;
}
