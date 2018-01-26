
typedef union 	{
	Node*	node;
	Sym*	sym;
	Type*	type;
	struct
	{
		Type*	t;
		char	c;
	} tycl;
	struct
	{
		Type*	t1;
		Type*	t2;
	} tyty;
	struct
	{
		char*	s;
		long	l;
	} sval;
	long	lval;
	double	dval;
	vlong	vval;
}	YYSTYPE;
extern	YYSTYPE	yylval;
#define	LPE	57346
#define	LME	57347
#define	LMLE	57348
#define	LDVE	57349
#define	LMDE	57350
#define	LRSHE	57351
#define	LLSHE	57352
#define	LANDE	57353
#define	LXORE	57354
#define	LORE	57355
#define	LOROR	57356
#define	LANDAND	57357
#define	LEQ	57358
#define	LNE	57359
#define	LLE	57360
#define	LGE	57361
#define	LLSH	57362
#define	LRSH	57363
#define	LMM	57364
#define	LPP	57365
#define	LMG	57366
#define	LNAME	57367
#define	LCTYPE	57368
#define	LSTYPE	57369
#define	LFCONST	57370
#define	LDCONST	57371
#define	LCHARACTER	57372
#define	LCONST	57373
#define	LLCONST	57374
#define	LUCONST	57375
#define	LULCONST	57376
#define	LVLCONST	57377
#define	LUVLCONST	57378
#define	LSTRING	57379
#define	LLSTRING	57380
#define	LAUTO	57381
#define	LBREAK	57382
#define	LCASE	57383
#define	LCHAR	57384
#define	LCONTINUE	57385
#define	LDEFAULT	57386
#define	LDO	57387
#define	LDOUBLE	57388
#define	LELSE	57389
#define	LEXTERN	57390
#define	LFLOAT	57391
#define	LFOR	57392
#define	LGOTO	57393
#define	LIF	57394
#define	LINT	57395
#define	LLONG	57396
#define	LREGISTER	57397
#define	LRETURN	57398
#define	LSHORT	57399
#define	LSIZEOF	57400
#define	LUSED	57401
#define	LSTATIC	57402
#define	LSTRUCT	57403
#define	LSWITCH	57404
#define	LTYPEDEF	57405
#define	LUNION	57406
#define	LUNSIGNED	57407
#define	LWHILE	57408
#define	LVOID	57409
#define	LENUM	57410
#define	LSIGNED	57411
#define	LCONSTNT	57412
#define	LVOLATILE	57413
#define	LSET	57414
#define	LSIGNOF	57415
#define	LVLONG	57416
