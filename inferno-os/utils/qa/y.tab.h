
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
#define	LMOVB	57347
#define	LABS	57348
#define	LLOGW	57349
#define	LSHW	57350
#define	LADDW	57351
#define	LCMP	57352
#define	LCROP	57353
#define	LBRA	57354
#define	LFMOV	57355
#define	LFCONV	57356
#define	LFCMP	57357
#define	LFADD	57358
#define	LFMA	57359
#define	LTRAP	57360
#define	LXORW	57361
#define	LNOP	57362
#define	LEND	57363
#define	LRETT	57364
#define	LWORD	57365
#define	LTEXT	57366
#define	LDATA	57367
#define	LRETRN	57368
#define	LCONST	57369
#define	LSP	57370
#define	LSB	57371
#define	LFP	57372
#define	LPC	57373
#define	LCREG	57374
#define	LFLUSH	57375
#define	LREG	57376
#define	LFREG	57377
#define	LR	57378
#define	LCR	57379
#define	LF	57380
#define	LFPSCR	57381
#define	LLR	57382
#define	LCTR	57383
#define	LSPR	57384
#define	LSPREG	57385
#define	LSEG	57386
#define	LMSR	57387
#define	LDCR	57388
#define	LSCHED	57389
#define	LXLD	57390
#define	LXST	57391
#define	LXOP	57392
#define	LXMV	57393
#define	LRLWM	57394
#define	LMOVMW	57395
#define	LMOVEM	57396
#define	LMOVFL	57397
#define	LMTFSB	57398
#define	LMA	57399
#define	LFMOVX	57400
#define	LFCONST	57401
#define	LSCONST	57402
#define	LNAME	57403
#define	LLAB	57404
#define	LVAR	57405
