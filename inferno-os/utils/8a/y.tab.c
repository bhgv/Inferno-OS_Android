
#line	2	"a.y"
#include "a.h"

#line	4	"a.y"
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
} YYSTYPE;
extern	int	yyerrflag;
#ifndef	YYMAXDEPTH
#define	YYMAXDEPTH	150
#endif
YYSTYPE	yylval;
YYSTYPE	yyval;
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
#define YYEOFCODE 1
#define YYERRCODE 2
short	yyexca[] =
{-1, 1,
	1, -1,
	-2, 0,
};
#define	YYNPROD	121
#define	YYPRIVATE 57344
#define	yydebug	1
#define	YYLAST	529
short	yyact[] =
{
  43,  55,   2, 109,  41,  74,  34,  56, 185,  42,
  53, 153, 227,  75, 226,  64, 224, 104,  81,  80,
  45, 220,  79,  58,  78, 218,  98,  76,  63,  98,
  88,  90,  92, 210, 208, 197,  69, 196, 187, 186,
 154, 211, 205,  97, 184,  98,  99, 152,  54, 106,
 107, 108, 188, 157, 131, 123, 105, 114, 101,  33,
 202, 199,  60,  64, 198, 136, 135,  33,  98, 124,
 125,  49,  48,  77,  81,  80, 122, 115,  79, 128,
  78, 100, 130,  76, 129, 134, 132, 133, 127, 121,
  46, 120, 113,  30,  36,  38,  40,  37, 137, 138,
  39,  82,  66,  47,  28, 215,  27,  73,  44,  26,
  56,  50, 159, 160,  24, 201,  25, 200,  23,  98,
 106,  51, 165, 217, 214, 149, 151, 166, 168, 167,
 150, 207, 164, 156, 221, 100, 165, 173, 172, 126,
  98,  98,  98,  98,  98, 149, 151,  98,  98,  98,
 150, 222,  31, 219, 189,  35,  29, 174, 175, 176,
 177, 178, 195, 190, 181, 182, 183, 180, 194, 163,
 192,  85,  71, 111, 112,  84, 158, 193,  94, 179,
  98,  98, 169, 170, 171,   6, 206,  49,  48,  77,
  96, 209, 139, 140, 141, 142, 143, 203, 204,  95,
 212, 213,   1,  93, 216,  91,  46, 141, 142, 143,
  36,  38,  40,  37,  49,  48,  39,  82,  66,  47,
 223,  89,  87, 225,  44,  83,  56,  50, 110,  72,
 111, 112,  70,  46,  68,  59,  57,  36,  38,  40,
  37,  52,  61,  39,  51,   7,  47, 191,   0,   0,
   0,  44,   0,  56,  50,   0,   0,   9,  10,  11,
  12,  13,  17,  15,  18,  14,  16,  19,  20,  21,
  22,  49,  48, 147, 146, 144, 145, 139, 140, 141,
 142, 143,   4,   3,   8,   0,   5,   0,   0,   0,
  46,  49,  48,   0,  36,  38,  40,  37,   0,   0,
  39,  51,   0,  47,   0,   0,   0,  86,  44,   0,
  46,  50,   0,   0,  36,  38,  40,  37,  49,  48,
  39,  51,   0,  47,   0,   0,   0,  32,  44,   0,
   0,  50,   0,   0,   0,   0,   0,  46,  49,  48,
   0,  36,  38,  40,  37,   0,   0,  39,  51,   0,
  47,   0,   0,   0,   0,  44,   0,  46,  50,   0,
   0,  36,  38,  40,  37,   0,   0,  39,   0,   0,
  47,  49, 119,   0,   0,  44,   0,   0,  50, 148,
 147, 146, 144, 145, 139, 140, 141, 142, 143,   0,
  46,   0,   0,  49,  48,   0,   0,   0, 117, 116,
   0,  51,   0,  47,   0,   0,   0,   0, 118,  49,
  48,  50,  46,  49,  48,  49,  48,   0,   0,  49,
  48,   0, 155,  65,  66,  47,   0,   0,  46,  62,
  67,   0,  46,  50,  46,   0,   0, 102,  46,  65,
  66,  47, 103,  49,  48,  47,  67,  47,   0,  50,
  67,  47,  67,  50,  56,  50,  67,  49,  48,  50,
   0,   0,  46,  49,  48,   0,   0,   0,   0,   0,
 162,   0,   0,   0,   0,  47,  46,   0,   0,   0,
  67,   0,  46,  50, 161,   0,   0,   0,   0,  47,
   0,   0,   0,  51,  67,  47,   0,  50,   0,   0,
  44,   0,   0,  50, 148, 147, 146, 144, 145, 139,
 140, 141, 142, 143, 146, 144, 145, 139, 140, 141,
 142, 143, 144, 145, 139, 140, 141, 142, 143
};
short	yypact[] =
{
-1000, 243,-1000,  76,  72,-1000,  66,  63,  60,  48,
 282, 205, 205, 309, 384,  82, 454,  62, 262, 205,
 205, 205, 454,-1000,-1000, 410,-1000,-1000, 410,-1000,
-1000,-1000, 309,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,  12, 404,  10,-1000,-1000, 410, 410,
 410, 221,-1000,  47,-1000,-1000, 362,-1000,  46,-1000,
  44,-1000, 400,-1000,   9, 164, 164, 410,-1000, 127,
-1000,  43,-1000, 178,-1000,-1000,-1000, 329,-1000,-1000,
-1000,   8, 221,-1000,-1000,-1000, 309,-1000,  42,-1000,
  40,-1000,  21,-1000,  20, 243, 243, 500,-1000, 500,
-1000, 112,   0,  -7, 375, 100,-1000,-1000,-1000,   7,
 168, 410, 410,-1000,-1000,-1000,-1000,-1000, 448, 434,
 309, 205,-1000, 106,-1000,-1000, 410, 406,-1000,-1000,
-1000,  92,   7, 309, 309, 309, 406,-1000,-1000, 410,
 410, 410, 410, 410, 172, 159, 410, 410, 410,  -3,
  -8,  -9,   6, 410,-1000,-1000, 152, 139, 164,-1000,
-1000, -10,-1000,-1000,-1000, -12,  19,-1000,  16,  75,
  73,-1000,-1000,  15, 196, 196,-1000,-1000,-1000, 410,
 410, 515, 508, 268,  -4, 410,-1000,-1000,  98, -13,
 410, -14,-1000,-1000,-1000,  -5,-1000,-1000, -41, -41,
  91,  71, -41, 183, 183,  90, -22, 142,-1000, -26,
-1000, 103,-1000,-1000,-1000,-1000,-1000, 140,-1000, 410,
-1000, -31, 410, -33,-1000, -35,-1000,-1000
};
short	yypgo[] =
{
   0,   0,  17, 247,   3, 247, 155,   1, 247,   6,
  20,  13,  48,  10,   5,   4,   9, 156, 242, 152,
 241, 236, 235, 234, 232, 229, 225, 222, 221, 205,
 203, 202,   2, 199, 190, 185
};
short	yyr1[] =
{
   0,  31,  31,  33,  32,  34,  32,  32,  32,  32,
  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,
  35,  35,  35,  35,  35,  35,  17,  17,  21,  22,
  20,  20,  19,  19,  18,  18,  23,  24,  24,  25,
  25,  26,  26,  27,  27,  28,  28,  29,  29,  29,
  30,  30,  12,  12,  14,  14,  14,  14,  14,  14,
  14,  13,  13,  11,  11,  11,   9,   9,   9,   9,
   9,   7,   7,   7,   7,   7,   7,   8,   5,   5,
   5,   5,   6,   6,  15,  15,  15,  15,  15,  15,
  15,  15,  15,  15,  16,  16,  10,  10,   4,   4,
   4,   3,   3,   3,   1,   1,   1,   1,   1,   1,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   2,
   2
};
short	yyr2[] =
{
   0,   0,   2,   0,   4,   0,   4,   1,   2,   2,
   3,   3,   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   0,   1,   3,   3,
   2,   1,   2,   1,   2,   1,   5,   3,   5,   2,
   1,   1,   1,   3,   5,   3,   5,   2,   1,   3,
   3,   5,   1,   1,   1,   1,   2,   2,   1,   1,
   1,   1,   1,   4,   2,   2,   1,   1,   1,   1,
   1,   2,   2,   2,   2,   4,   3,   2,   1,   2,
   3,   4,   1,   1,   1,   4,   4,   6,   9,   3,
   3,   4,   5,   8,   1,   6,   5,   7,   0,   2,
   2,   1,   1,   1,   1,   1,   2,   2,   2,   3,
   1,   3,   3,   3,   3,   3,   4,   4,   3,   3,
   3
};
short	yychk[] =
{
-1000, -31, -32,  40,  39,  43, -35,   2,  41,  14,
  15,  16,  17,  18,  22,  20,  23,  19,  21,  24,
  25,  26,  27,  42,  42,  44,  43,  43,  44, -17,
  45, -19,  45, -12,  -9,  -6,  32,  35,  33,  38,
  34, -15, -16,  -1,  46, -10,  28,  41,  10,   9,
  49,  39, -20, -13, -12,  -7,  48, -21, -13, -22,
 -12, -18,  45, -11,  -1,  39,  40,  46, -23, -10,
 -24,  -6, -25,  45, -14, -11, -16,  11,  -9, -15,
  -7,  -1,  39, -26, -17, -19,  45, -27, -13, -28,
 -13, -29, -13, -30,  -6, -33, -34,  -2,  -1,  -2,
 -12,  46,  33,  38,  -2,  46,  -1,  -1,  -1,  -4,
   7,   9,  10,  45,  -1, -10,  37,  36,  46,  10,
  45,  45, -11,  46,  -4,  -4,  12,  45, -14,  -9,
 -15,  46,  -4,  45,  45,  45,  45, -32, -32,   9,
  10,  11,  12,  13,   7,   8,   6,   5,   4,  33,
  38,  34,  47,  11,  47,  47,  33,  46,   8,  -1,
  -1,  36,  36, -12, -13,  30,  -1,  -7,  -1, -12,
 -12, -12,  -7,  -1,  -2,  -2,  -2,  -2,  -2,   7,
   8,  -2,  -2,  -2,  47,  11,  47,  47,  46,  -1,
  11,  -3,  31,  38,  29,  -4,  47,  47,  45,  45,
  42,  42,  45,  -2,  -2,  46,  -1,  33,  47,  -1,
  47,  46,  -7,  -7,  33,  34,  -7,  33,  47,  11,
  47,  31,  11,  -1,  47,  -1,  47,  47
};
short	yydef[] =
{
   1,  -2,   2,   0,   0,   7,   0,   0,   0,  26,
   0,   0,   0,   0,   0,   0,   0,   0,  26,   0,
   0,   0,   0,   3,   5,   0,   8,   9,   0,  12,
  27,  13,   0,  33,  52,  53,  66,  67,  68,  69,
  70,  82,  83,  84,   0,  94, 104, 105,   0,   0,
   0,  98,  14,  31,  61,  62,   0,  15,   0,  16,
   0,  17,   0,  35,   0,  98,  98,   0,  18,   0,
  19,   0,  20,   0,  40,  54,  55,   0,  58,  59,
  60,  84,  98,  21,  41,  42,  27,  22,   0,  23,
   0,  24,  48,  25,   0,   0,   0,  10, 110,  11,
  32,   0,   0,   0,   0,   0, 106, 107, 108,   0,
   0,   0,   0,  30,  71,  72,  73,  74,   0,   0,
   0,   0,  34,   0,  64,  65,   0,   0,  39,  56,
  57,   0,  64,   0,   0,  47,   0,   4,   6,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,  89,   0,  90, 109,   0,   0,  98,  99,
 100,   0,  76,  28,  29,   0,   0,  37,   0,  43,
  45,  49,  50,   0, 111, 112, 113, 114, 115,   0,
   0, 118, 119, 120,  85,   0,  86,  91,   0,   0,
   0,   0, 101, 102, 103,   0,  75,  63,   0,   0,
   0,   0,   0, 116, 117,   0,   0,   0,  92,   0,
  96,   0,  36,  38,  44,  46,  51,   0,  87,   0,
  95,   0,   0,   0,  97,   0,  93,  88
};
short	yytok1[] =
{
   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,  48,  13,   6,   0,
  46,  47,  11,   9,  45,  10,   0,  12,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  42,  43,
   7,  44,   8,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   5,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   4,   0,  49
};
short	yytok2[] =
{
   2,   3,  14,  15,  16,  17,  18,  19,  20,  21,
  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
  32,  33,  34,  35,  36,  37,  38,  39,  40,  41
};
long	yytok3[] =
{
   0
};
#define YYFLAG 		-1000
#define	yyclearin	yychar = -1
#define	yyerrok		yyerrflag = 0

#ifdef	yydebug
#include	"y.debug"
#else
#define	yydebug		0
char*	yytoknames[1];		/* for debugging */
char*	yystates[1];		/* for debugging */
#endif

/*	parser for yacc output	*/

int	yynerrs = 0;		/* number of errors */
int	yyerrflag = 0;		/* error recovery flag */

extern	int	fprint(int, char*, ...);
extern	int	sprint(char*, char*, ...);

char*
yytokname(int yyc)
{
	static char x[16];

	if(yyc > 0 && yyc <= sizeof(yytoknames)/sizeof(yytoknames[0]))
	if(yytoknames[yyc-1])
		return yytoknames[yyc-1];
	sprint(x, "<%d>", yyc);
	return x;
}

char*
yystatname(int yys)
{
	static char x[16];

	if(yys >= 0 && yys < sizeof(yystates)/sizeof(yystates[0]))
	if(yystates[yys])
		return yystates[yys];
	sprint(x, "<%d>\n", yys);
	return x;
}

long
yylex1(void)
{
	long yychar;
	long *t3p;
	int c;

	yychar = yylex();
	if(yychar <= 0) {
		c = yytok1[0];
		goto out;
	}
	if(yychar < sizeof(yytok1)/sizeof(yytok1[0])) {
		c = yytok1[yychar];
		goto out;
	}
	if(yychar >= YYPRIVATE)
		if(yychar < YYPRIVATE+sizeof(yytok2)/sizeof(yytok2[0])) {
			c = yytok2[yychar-YYPRIVATE];
			goto out;
		}
	for(t3p=yytok3;; t3p+=2) {
		c = t3p[0];
		if(c == yychar) {
			c = t3p[1];
			goto out;
		}
		if(c == 0)
			break;
	}
	c = 0;

out:
	if(c == 0)
		c = yytok2[1];	/* unknown char */
	if(yydebug >= 3)
		fprint(2, "lex %.4lux %s\n", yychar, yytokname(c));
	return c;
}

int
yyparse(void)
{
	struct
	{
		YYSTYPE	yyv;
		int	yys;
	} yys[YYMAXDEPTH], *yyp, *yypt;
	short *yyxi;
	int yyj, yym, yystate, yyn, yyg;
	long yychar;
	YYSTYPE save1, save2;
	int save3, save4;

	save1 = yylval;
	save2 = yyval;
	save3 = yynerrs;
	save4 = yyerrflag;

	yystate = 0;
	yychar = -1;
	yynerrs = 0;
	yyerrflag = 0;
	yyp = &yys[-1];
	goto yystack;

ret0:
	yyn = 0;
	goto ret;

ret1:
	yyn = 1;
	goto ret;

ret:
	yylval = save1;
	yyval = save2;
	yynerrs = save3;
	yyerrflag = save4;
	return yyn;

yystack:
	/* put a state and value onto the stack */
	if(yydebug >= 4)
		fprint(2, "char %s in %s", yytokname(yychar), yystatname(yystate));

	yyp++;
	if(yyp >= &yys[YYMAXDEPTH]) {
		yyerror("yacc stack overflow");
		goto ret1;
	}
	yyp->yys = yystate;
	yyp->yyv = yyval;

yynewstate:
	yyn = yypact[yystate];
	if(yyn <= YYFLAG)
		goto yydefault; /* simple state */
	if(yychar < 0)
		yychar = yylex1();
	yyn += yychar;
	if(yyn < 0 || yyn >= YYLAST)
		goto yydefault;
	yyn = yyact[yyn];
	if(yychk[yyn] == yychar) { /* valid shift */
		yychar = -1;
		yyval = yylval;
		yystate = yyn;
		if(yyerrflag > 0)
			yyerrflag--;
		goto yystack;
	}

yydefault:
	/* default state action */
	yyn = yydef[yystate];
	if(yyn == -2) {
		if(yychar < 0)
			yychar = yylex1();

		/* look through exception table */
		for(yyxi=yyexca;; yyxi+=2)
			if(yyxi[0] == -1 && yyxi[1] == yystate)
				break;
		for(yyxi += 2;; yyxi += 2) {
			yyn = yyxi[0];
			if(yyn < 0 || yyn == yychar)
				break;
		}
		yyn = yyxi[1];
		if(yyn < 0)
			goto ret0;
	}
	if(yyn == 0) {
		/* error ... attempt to resume parsing */
		switch(yyerrflag) {
		case 0:   /* brand new error */
			yyerror("syntax error");
			yynerrs++;
			if(yydebug >= 1) {
				fprint(2, "%s", yystatname(yystate));
				fprint(2, "saw %s\n", yytokname(yychar));
			}

		case 1:
		case 2: /* incompletely recovered error ... try again */
			yyerrflag = 3;

			/* find a state where "error" is a legal shift action */
			while(yyp >= yys) {
				yyn = yypact[yyp->yys] + YYERRCODE;
				if(yyn >= 0 && yyn < YYLAST) {
					yystate = yyact[yyn];  /* simulate a shift of "error" */
					if(yychk[yystate] == YYERRCODE)
						goto yystack;
				}

				/* the current yyp has no shift onn "error", pop stack */
				if(yydebug >= 2)
					fprint(2, "error recovery pops state %d, uncovers %d\n",
						yyp->yys, (yyp-1)->yys );
				yyp--;
			}
			/* there is no state on the stack with an error shift ... abort */
			goto ret1;

		case 3:  /* no shift yet; clobber input char */
			if(yydebug >= 2)
				fprint(2, "error recovery discards %s\n", yytokname(yychar));
			if(yychar == YYEOFCODE)
				goto ret1;
			yychar = -1;
			goto yynewstate;   /* try again in the same state */
		}
	}

	/* reduction by production yyn */
	if(yydebug >= 2)
		fprint(2, "reduce %d in:\n\t%s", yyn, yystatname(yystate));

	yypt = yyp;
	yyp -= yyr2[yyn];
	yyval = (yyp+1)->yyv;
	yym = yyn;

	/* consult goto table to find next state */
	yyn = yyr1[yyn];
	yyg = yypgo[yyn];
	yyj = yyg + yyp->yys + 1;

	if(yyj >= YYLAST || yychk[yystate=yyact[yyj]] != -yyn)
		yystate = yyact[yyg];
	switch(yym) {
		
case 3:
#line	40	"a.y"
{
		if(yypt[-1].yyv.sym->value != pc)
			yyerror("redeclaration of %s", yypt[-1].yyv.sym->name);
		yypt[-1].yyv.sym->value = pc;
	} break;
case 5:
#line	47	"a.y"
{
		yypt[-1].yyv.sym->type = LLAB;
		yypt[-1].yyv.sym->value = pc;
	} break;
case 10:
#line	58	"a.y"
{
		yypt[-2].yyv.sym->type = LVAR;
		yypt[-2].yyv.sym->value = yypt[-0].yyv.lval;
	} break;
case 11:
#line	63	"a.y"
{
		if(yypt[-2].yyv.sym->value != yypt[-0].yyv.lval)
			yyerror("redeclaration of %s", yypt[-2].yyv.sym->name);
		yypt[-2].yyv.sym->value = yypt[-0].yyv.lval;
	} break;
case 12:
#line	68	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 13:
#line	69	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 14:
#line	70	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 15:
#line	71	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 16:
#line	72	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 17:
#line	73	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 18:
#line	74	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 19:
#line	75	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 20:
#line	76	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 21:
#line	77	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 22:
#line	78	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 23:
#line	79	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 24:
#line	80	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 25:
#line	81	"a.y"
{ outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen2); } break;
case 26:
#line	84	"a.y"
{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = nullgen;
	} break;
case 27:
#line	89	"a.y"
{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = nullgen;
	} break;
case 28:
#line	96	"a.y"
{
		yyval.gen2.from = yypt[-2].yyv.gen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 29:
#line	103	"a.y"
{
		yyval.gen2.from = yypt[-2].yyv.gen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 30:
#line	110	"a.y"
{
		yyval.gen2.from = yypt[-1].yyv.gen;
		yyval.gen2.to = nullgen;
	} break;
case 31:
#line	115	"a.y"
{
		yyval.gen2.from = yypt[-0].yyv.gen;
		yyval.gen2.to = nullgen;
	} break;
case 32:
#line	122	"a.y"
{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 33:
#line	127	"a.y"
{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 34:
#line	134	"a.y"
{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 35:
#line	139	"a.y"
{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 36:
#line	146	"a.y"
{
		yyval.gen2.from = yypt[-4].yyv.gen;
		yyval.gen2.from.scale = yypt[-2].yyv.lval;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 37:
#line	154	"a.y"
{
		yyval.gen2.from = yypt[-2].yyv.gen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 38:
#line	159	"a.y"
{
		yyval.gen2.from = yypt[-4].yyv.gen;
		yyval.gen2.from.scale = yypt[-2].yyv.lval;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 39:
#line	167	"a.y"
{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 40:
#line	172	"a.y"
{
		yyval.gen2.from = nullgen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 43:
#line	183	"a.y"
{
		yyval.gen2.from = yypt[-2].yyv.gen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 44:
#line	188	"a.y"
{
		yyval.gen2.from = yypt[-4].yyv.gen;
		yyval.gen2.to = yypt[-2].yyv.gen;
		if(yyval.gen2.from.index != D_NONE)
			yyerror("dp shift with lhs index");
		yyval.gen2.from.index = yypt[-0].yyv.lval;
	} break;
case 45:
#line	198	"a.y"
{
		yyval.gen2.from = yypt[-2].yyv.gen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 46:
#line	203	"a.y"
{
		yyval.gen2.from = yypt[-4].yyv.gen;
		yyval.gen2.to = yypt[-2].yyv.gen;
		if(yyval.gen2.to.index != D_NONE)
			yyerror("dp move with lhs index");
		yyval.gen2.to.index = yypt[-0].yyv.lval;
	} break;
case 47:
#line	213	"a.y"
{
		yyval.gen2.from = yypt[-1].yyv.gen;
		yyval.gen2.to = nullgen;
	} break;
case 48:
#line	218	"a.y"
{
		yyval.gen2.from = yypt[-0].yyv.gen;
		yyval.gen2.to = nullgen;
	} break;
case 49:
#line	223	"a.y"
{
		yyval.gen2.from = yypt[-2].yyv.gen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 50:
#line	230	"a.y"
{
		yyval.gen2.from = yypt[-2].yyv.gen;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 51:
#line	235	"a.y"
{
		yyval.gen2.from = yypt[-4].yyv.gen;
		yyval.gen2.from.scale = yypt[-2].yyv.lval;
		yyval.gen2.to = yypt[-0].yyv.gen;
	} break;
case 56:
#line	249	"a.y"
{
		yyval.gen = yypt[-0].yyv.gen;
	} break;
case 57:
#line	253	"a.y"
{
		yyval.gen = yypt[-0].yyv.gen;
	} break;
case 63:
#line	266	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.offset = yypt[-3].yyv.lval + pc;
	} break;
case 64:
#line	272	"a.y"
{
		yyval.gen = nullgen;
		if(pass == 2)
			yyerror("undefined label: %s", yypt[-1].yyv.sym->name);
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yypt[-1].yyv.sym;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 65:
#line	281	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yypt[-1].yyv.sym;
		yyval.gen.offset = yypt[-1].yyv.sym->value + yypt[-0].yyv.lval;
	} break;
case 66:
#line	290	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = yypt[-0].yyv.lval;
	} break;
case 67:
#line	295	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = yypt[-0].yyv.lval;
	} break;
case 68:
#line	300	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = yypt[-0].yyv.lval;
	} break;
case 69:
#line	305	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SP;
	} break;
case 70:
#line	310	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = yypt[-0].yyv.lval;
	} break;
case 71:
#line	317	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_CONST;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 72:
#line	323	"a.y"
{
		yyval.gen = yypt[-0].yyv.gen;
		yyval.gen.index = yypt[-0].yyv.gen.type;
		yyval.gen.type = D_ADDR;
		/*
		if($2.type == D_AUTO || $2.type == D_PARAM)
			yyerror("constant cannot be automatic: %s",
				$2.sym->name);
		 */
	} break;
case 73:
#line	334	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SCONST;
		memcpy(yyval.gen.sval, yypt[-0].yyv.sval, sizeof(yyval.gen.sval));
	} break;
case 74:
#line	340	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = yypt[-0].yyv.dval;
	} break;
case 75:
#line	346	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = yypt[-1].yyv.dval;
	} break;
case 76:
#line	352	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = -yypt[-0].yyv.dval;
	} break;
case 77:
#line	360	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_CONST2;
		yyval.gen.offset = yypt[-0].yyv.con2.v1;
		yyval.gen.offset2 = yypt[-0].yyv.con2.v2;
	} break;
case 78:
#line	369	"a.y"
{
		yyval.con2.v1 = yypt[-0].yyv.lval;
		yyval.con2.v2 = 0;
	} break;
case 79:
#line	374	"a.y"
{
		yyval.con2.v1 = -yypt[-0].yyv.lval;
		yyval.con2.v2 = 0;
	} break;
case 80:
#line	379	"a.y"
{
		yyval.con2.v1 = yypt[-2].yyv.lval;
		yyval.con2.v2 = yypt[-0].yyv.lval;
	} break;
case 81:
#line	384	"a.y"
{
		yyval.con2.v1 = -yypt[-2].yyv.lval;
		yyval.con2.v2 = yypt[-0].yyv.lval;
	} break;
case 84:
#line	395	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_NONE;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 85:
#line	401	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yypt[-1].yyv.lval;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 86:
#line	407	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_SP;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 87:
#line	413	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_NONE;
		yyval.gen.offset = yypt[-5].yyv.lval;
		yyval.gen.index = yypt[-3].yyv.lval;
		yyval.gen.scale = yypt[-1].yyv.lval;
		checkscale(yyval.gen.scale);
	} break;
case 88:
#line	422	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yypt[-6].yyv.lval;
		yyval.gen.offset = yypt[-8].yyv.lval;
		yyval.gen.index = yypt[-3].yyv.lval;
		yyval.gen.scale = yypt[-1].yyv.lval;
		checkscale(yyval.gen.scale);
	} break;
case 89:
#line	431	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yypt[-1].yyv.lval;
	} break;
case 90:
#line	436	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_SP;
	} break;
case 91:
#line	441	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yypt[-1].yyv.lval;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 92:
#line	447	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+D_NONE;
		yyval.gen.index = yypt[-3].yyv.lval;
		yyval.gen.scale = yypt[-1].yyv.lval;
		checkscale(yyval.gen.scale);
	} break;
case 93:
#line	455	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_INDIR+yypt[-6].yyv.lval;
		yyval.gen.index = yypt[-3].yyv.lval;
		yyval.gen.scale = yypt[-1].yyv.lval;
		checkscale(yyval.gen.scale);
	} break;
case 94:
#line	465	"a.y"
{
		yyval.gen = yypt[-0].yyv.gen;
	} break;
case 95:
#line	469	"a.y"
{
		yyval.gen = yypt[-5].yyv.gen;
		yyval.gen.index = yypt[-3].yyv.lval;
		yyval.gen.scale = yypt[-1].yyv.lval;
		checkscale(yyval.gen.scale);
	} break;
case 96:
#line	478	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = yypt[-1].yyv.lval;
		yyval.gen.sym = yypt[-4].yyv.sym;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 97:
#line	485	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_STATIC;
		yyval.gen.sym = yypt[-6].yyv.sym;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 98:
#line	493	"a.y"
{
		yyval.lval = 0;
	} break;
case 99:
#line	497	"a.y"
{
		yyval.lval = yypt[-0].yyv.lval;
	} break;
case 100:
#line	501	"a.y"
{
		yyval.lval = -yypt[-0].yyv.lval;
	} break;
case 102:
#line	508	"a.y"
{
		yyval.lval = D_AUTO;
	} break;
case 105:
#line	516	"a.y"
{
		yyval.lval = yypt[-0].yyv.sym->value;
	} break;
case 106:
#line	520	"a.y"
{
		yyval.lval = -yypt[-0].yyv.lval;
	} break;
case 107:
#line	524	"a.y"
{
		yyval.lval = yypt[-0].yyv.lval;
	} break;
case 108:
#line	528	"a.y"
{
		yyval.lval = ~yypt[-0].yyv.lval;
	} break;
case 109:
#line	532	"a.y"
{
		yyval.lval = yypt[-1].yyv.lval;
	} break;
case 111:
#line	539	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval + yypt[-0].yyv.lval;
	} break;
case 112:
#line	543	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval - yypt[-0].yyv.lval;
	} break;
case 113:
#line	547	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval * yypt[-0].yyv.lval;
	} break;
case 114:
#line	551	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval / yypt[-0].yyv.lval;
	} break;
case 115:
#line	555	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval % yypt[-0].yyv.lval;
	} break;
case 116:
#line	559	"a.y"
{
		yyval.lval = yypt[-3].yyv.lval << yypt[-0].yyv.lval;
	} break;
case 117:
#line	563	"a.y"
{
		yyval.lval = yypt[-3].yyv.lval >> yypt[-0].yyv.lval;
	} break;
case 118:
#line	567	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval & yypt[-0].yyv.lval;
	} break;
case 119:
#line	571	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval ^ yypt[-0].yyv.lval;
	} break;
case 120:
#line	575	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval | yypt[-0].yyv.lval;
	} break;
	}
	goto yystack;  /* stack new state and value */
}
