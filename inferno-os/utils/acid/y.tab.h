
typedef union 
{
	Node	*node;
	Lsym	*sym;
	ulong	ival;
	float	fval;
	String	*string;
}	YYSTYPE;
extern	YYSTYPE	yylval;
#define	Tfmt	57346
#define	Toror	57347
#define	Tandand	57348
#define	Teq	57349
#define	Tneq	57350
#define	Tleq	57351
#define	Tgeq	57352
#define	Tlsh	57353
#define	Trsh	57354
#define	Tdec	57355
#define	Tinc	57356
#define	Tindir	57357
#define	Tid	57358
#define	Tconst	57359
#define	Tfconst	57360
#define	Tstring	57361
#define	Tif	57362
#define	Tdo	57363
#define	Tthen	57364
#define	Telse	57365
#define	Twhile	57366
#define	Tloop	57367
#define	Thead	57368
#define	Ttail	57369
#define	Tappend	57370
#define	Tfn	57371
#define	Tret	57372
#define	Tlocal	57373
#define	Tcomplex	57374
#define	Twhat	57375
#define	Tdelete	57376
#define	Teval	57377
