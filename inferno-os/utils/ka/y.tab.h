
typedef union 
{
	Sym	*sym;
	long	lval;
	double	dval;
	char	sval[8];
	Gen	gen;
}	YYSTYPE;
extern	YYSTYPE	yylval;
#define	LMOVW	57346
#define	LMOVD	57347
#define	LMOVB	57348
#define	LSWAP	57349
#define	LADDW	57350
#define	LCMP	57351
#define	LBRA	57352
#define	LFMOV	57353
#define	LFCONV	57354
#define	LFADD	57355
#define	LCPOP	57356
#define	LTRAP	57357
#define	LJMPL	57358
#define	LXORW	57359
#define	LNOP	57360
#define	LEND	57361
#define	LRETT	57362
#define	LUNIMP	57363
#define	LTEXT	57364
#define	LDATA	57365
#define	LRETRN	57366
#define	LCONST	57367
#define	LSP	57368
#define	LSB	57369
#define	LFP	57370
#define	LPC	57371
#define	LCREG	57372
#define	LFLUSH	57373
#define	LREG	57374
#define	LFREG	57375
#define	LR	57376
#define	LC	57377
#define	LF	57378
#define	LFSR	57379
#define	LFPQ	57380
#define	LPSR	57381
#define	LSCHED	57382
#define	LFCONST	57383
#define	LSCONST	57384
#define	LNAME	57385
#define	LLAB	57386
#define	LVAR	57387
