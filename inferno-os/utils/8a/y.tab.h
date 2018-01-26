
typedef union 	{
	Sym	*sym;
	long	lval;
	struct {
		long v1;
		long v2;
	} con2;
	double	dval;
	char	sval[8];
	Gen	gen;
	Gen2	gen2;
}	YYSTYPE;
extern	YYSTYPE	yylval;
#define	LTYPE0	57346
#define	LTYPE1	57347
#define	LTYPE2	57348
#define	LTYPE3	57349
#define	LTYPE4	57350
#define	LTYPEC	57351
#define	LTYPED	57352
#define	LTYPEN	57353
#define	LTYPER	57354
#define	LTYPET	57355
#define	LTYPES	57356
#define	LTYPEM	57357
#define	LTYPEI	57358
#define	LTYPEG	57359
#define	LCONST	57360
#define	LFP	57361
#define	LPC	57362
#define	LSB	57363
#define	LBREG	57364
#define	LLREG	57365
#define	LSREG	57366
#define	LFREG	57367
#define	LFCONST	57368
#define	LSCONST	57369
#define	LSP	57370
#define	LNAME	57371
#define	LLAB	57372
#define	LVAR	57373
