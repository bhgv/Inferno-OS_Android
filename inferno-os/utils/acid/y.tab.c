
#line	2	"dbg.y"
#include <lib9.h>
#include <bio.h>
#include "mach.h"
#define Extern extern
#include "acid.h"

#line	9	"dbg.y"
typedef union 
{
	Node	*node;
	Lsym	*sym;
	ulong	ival;
	float	fval;
	String	*string;
} YYSTYPE;
extern	int	yyerrflag;
#ifndef	YYMAXDEPTH
#define	YYMAXDEPTH	150
#endif
YYSTYPE	yylval;
YYSTYPE	yyval;
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
#define YYEOFCODE 1
#define YYERRCODE 2
short	yyexca[] =
{-1, 1,
	1, -1,
	-2, 30,
};
#define	YYNPROD	86
#define	YYPRIVATE 57344
#define	YYLAST	705
short	yyact[] =
{
  43,  41,   3, 167,  15, 142, 141, 144, 131,   6,
  42,  36,  97,  31, 137, 158,  97,  44, 104,  38,
 103, 104, 136,  80,  82,  83,  84,  85,  86,  87,
  88,  89,  90,  91,  92,  93, 111, 157, 165,  97,
 104, 176, 101,  99, 146, 143, 146, 143, 171,  20,
  21,  18, 163, 100,  22,  23, 146, 107, 152,  16,
  36,  32,  33,  34,   8, 145, 173, 145,  10,   9,
  24,  25,  26,  36,  11,  12,  45,  35,  27,  30,
 135,   7, 184, 134,  19,  28,  29, 146, 161, 105,
  96, 146, 143,  60,  61,  62,  63,  59,  58,  56,
  57,  53,  54,  55, 107, 138,  52, 149, 107, 140,
 151, 139, 145, 159, 148,  39,  37,  98,  94, 100,
  68,  67,  66,  64,  65,  60,  61,  62,  63,  59,
  58,  56,  57,  53,  54,  55, 153,  53,  54,  55,
 183, 155, 156, 181,  13, 180, 178, 160, 168, 169,
 147, 162, 164,  46,  48,  49,  50,  40,   2,   1,
  95,  74,  51,  14,  17,   0, 174, 175,   0, 170,
 160, 172, 177,  76,  79,  78,  77,  75, 182, 179,
   0,   0,   0, 101,  66,  64,  65,  60,  61,  62,
  63,  59,  58,  56,  57,  53,  54,  55, 112, 113,
 114, 115, 116, 117, 118, 119, 120, 121, 122, 123,
 124, 125, 126, 127, 128, 129, 130,   0,   0,   0,
 133,   0,  20,  21,  18,   0,  74,  22,  23,   0,
   0,   0,  16,  36,  32,  33,  34,   8,   0,   0,
   0,  10,   9,  24,  25,  26,   0,  11,  12,  45,
  35,  27,  30, 150,   7, 102,   0,  19,  28,  29,
  20,  21,  18,   0,   0,  22,  23,   0,   0,   0,
  16,  36,  32,  33,  34,   8,   0,   0,   0,  10,
   9,  24,  25,  26,   4,  11,  12,   5,  35,  27,
  30,   0,   7,   0,   0,  19,  28,  29,  20,  21,
  18,   0,   0,  22,  23,   0,   0,   0,  16,  36,
  32,  33,  34,   8,   0,   0,   0,  10,   9,  24,
  25,  26,   0,  11,  12,  45,  35,  27,  30,   0,
   7,   0,   0,  19,  28,  29,  71,  72,  70,  69,
  68,  67,  66,  64,  65,  60,  61,  62,  63,  59,
  58,  56,  57,  53,  54,  55,  20,  21,  18,   0,
   0,  22,  23,   0,   0,   0,  81,  36,  32,  33,
  34,  56,  57,  53,  54,  55,   0,  24,  25,  26,
   0,   0,   0,   0,  35,  27,  30,   0,  47, 154,
   0,  19,  28,  29,  20,  21,  18,   0,   0,  22,
  23,   0,   0,   0,  16,  36,  32,  33,  34,   0,
   0,   0,   0,   0,   0,  24,  25,  26,   0,   0,
   0,   0,  35,  27,  30,   0,  47,   0,   0,  19,
  28,  29,  20,  21,  18,   0,   0,  22,  23,   0,
   0,   0,  16,  73,  32,  33,  34,   0,   0,   0,
   0,   0,   0,  24,  25,  26,   0,   0,   0,   0,
  35,  27,  30,   0,  47,   0,   0,  19,  28,  29,
  71,  72,  70,  69,  68,  67,  66,  64,  65,  60,
  61,  62,  63,  59,  58,  56,  57,  53,  54,  55,
  71,  72,  70,  69,  68,  67,  66,  64,  65,  60,
  61,  62,  63,  59,  58,  56,  57,  53,  54,  55,
  59,  58,  56,  57,  53,  54,  55,   0,   0, 108,
  67,  66,  64,  65,  60,  61,  62,  63,  59,  58,
  56,  57,  53,  54,  55,   0, 132,  71,  72,  70,
  69,  68,  67,  66,  64,  65,  60,  61,  62,  63,
  59,  58,  56,  57,  53,  54,  55,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0, 106,
  71,  72,  70,  69,  68,  67,  66,  64,  65,  60,
  61,  62,  63,  59,  58,  56,  57,  53,  54,  55,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0, 166,  71,  72,  70,  69,  68,  67,  66,  64,
  65,  60,  61,  62,  63,  59,  58,  56,  57,  53,
  54,  55,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0, 109, 110,  71,  72,  70,  69,  68,
  67,  66,  64,  65,  60,  61,  62,  63,  59,  58,
  56,  57,  53,  54,  55,  71,  72,  70,  69,  68,
  67,  66,  64,  65,  60,  61,  62,  63,  59,  58,
  56,  57,  53,  54,  55,  69,  68,  67,  66,  64,
  65,  60,  61,  62,  63,  59,  58,  56,  57,  53,
  54,  55,  64,  65,  60,  61,  62,  63,  59,  58,
  56,  57,  53,  54,  55
};
short	yypact[] =
{
-1000, 240,-1000,-1000,  85,  84, 153, 278, 374, 374,
 374, 374,  75, 650,-1000,-1000, 412, 148, 336, 336,
 336, 336, 336, 336, 336, 336, 336, 336, 336, 336,
 336,  88,-1000,-1000,-1000,  59, -47,  87,  -9, -20,
-1000, 202, -33,-1000, 153,  58, 532, 374, 465, 597,
 630, -18,-1000, 374, 374, 374, 374, 374, 374, 374,
 374, 374, 374, 374, 374, 374, 374, 374, 374, 374,
 374, 374,-1000, -43, 485, 374,-1000,  52,  49,-1000,
-1000, 374,-1000,-1000,-1000,-1000,-1000,-1000,-1000, -32,
 -40,-1000,-1000,-1000, 374,-1000,-1000,  42, 374,  15,
 146,-1000,-1000,-1000, 374,  42, 278,-1000, 374, 278,
-1000,  27,-1000,-1000,-1000, 115, 115, 351, 351, 492,
 492, 492, 492,  79,  79, 680, 173, 510, 111, 667,
 650, 336,-1000, 331,-1000,-1000, 336, 336, -14,-1000,
 -36,  60,-1000,  56,  20,  15,-1000,-1000,-1000,   0,
 565,-1000,-1000,-1000,-1000,-1000,-1000,-1000, 144, 145,
-1000,  25,  16,  25,  13, 278, 278, -11, 144,-1000,
 142,  25, 141, 139,-1000,-1000, 278,-1000,-1000, 136,
-1000,-1000,  29,-1000,-1000
};
short	yypgo[] =
{
   0, 144,   4, 164,   0,  13,  10,   9,   1,   5,
   6,   7, 163, 162, 160, 159, 158,   3
};
short	yyr1[] =
{
   0,  15,  15,  16,  16,  16,  17,  17,  10,  10,
  11,   9,   9,   9,   9,  14,  14,   8,   8,   4,
   4,   4,   4,   4,   4,   4,   4,   4,  13,  13,
   7,   7,   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,  12,  12,   2,   2,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,   2,   3,
   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
   3,   3,   5,   5,   6,   6
};
short	yyr2[] =
{
   0,   0,   2,   1,   9,   6,   0,   2,   1,   2,
   1,   4,   5,   4,   4,   0,   1,   1,   2,   2,
   3,   4,   6,   6,   4,   3,   2,   4,   1,   3,
   0,   1,   1,   3,   3,   3,   3,   3,   3,   3,
   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
   3,   3,   2,   1,   4,   1,   2,   2,   2,   2,
   2,   2,   2,   2,   4,   4,   2,   2,   2,   3,
   3,   4,   2,   3,   3,   2,   4,   1,   1,   1,
   1,   2,   1,   3,   1,   3
};
short	yychk[] =
{
-1000, -15, -16,  -4,  44,  47,  -7,  52,  35,  40,
  39,  45,  46,  -1, -12,  -2,  30,  -3,  22,  55,
  20,  21,  25,  26,  41,  42,  43,  49,  56,  57,
  50,  -5,  32,  33,  34,  48,  31,  31,  -5,  31,
   4,  -8,  -6,  -4,  -7,  47,  -1,  52,  -1,  -1,
  -1, -13,  31,  22,  23,  24,  20,  21,  19,  18,
  14,  15,  16,  17,  12,  13,  11,  10,   9,   8,
   7,   5,   6,  31,  -1,  29,  25,  28,  27,  26,
  -2,  30,  -2,  -2,  -2,  -2,  -2,  -2,  -2,  -2,
  -2,  -2,  -2,  -2,  30, -14,  31,  59,  30,  52,
  -5,  -4,  53,  53,  54,  31,  37,  -7,  54,  36,
   4,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
  -1,  51,  51,  -1,  31,  31,  54,  54,  -6,  -5,
  -6, -10,  -9,  32, -11,  52,  31,   4,  -7,  -4,
  -1,  -4,  31,  -2,  58,  -2,  -2,  51,  51,  53,
  -9,  32, -11,  32, -10,  38,  36, -17,   4,   4,
 -11,  32, -11,  53,  -4,  -4,  52, -17,   4, -11,
   4,   4,  -8,   4,  53
};
short	yydef[] =
{
   1,  -2,   2,   3,   0,   0,   0,  30,   0,   0,
   0,   0,   0,  31,  32,  53,   0,  55,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,  77,  78,  79,  80,  15,  82,   0,   0,  82,
  19,  30,   0,  17,  84,   0,   0,  30,   0,   0,
   0,  26,  28,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,  52,  82,   0,   0,  72,   0,   0,  75,
  56,   0,  57,  58,  59,  60,  61,  62,  63,   0,
   0,  66,  67,  68,  30,  81,  16,   0,  30,   0,
   0,  18,  20,  70,  30,   0,  30,  84,   0,  30,
  25,   0,  33,  34,  35,  36,  37,  38,  39,  40,
  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,
  51,   0,  69,   0,  73,  74,   0,   0,   0,  83,
   0,   0,   8,   0,   0,   0,  10,  27,  85,  21,
   0,  24,  29,  54,  71,  64,  65,  76,   6,   0,
   9,   0,   0,   0,   0,  30,  30,   0,   6,   5,
   0,   0,   0,   0,  22,  23,  30,   7,  11,   0,
  13,  14,  30,  12,   4
};
short	yytok1[] =
{
   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,  56,   0,   0,   0,  24,  11,   0,
  30,  51,  22,  20,  54,  21,  28,  23,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  59,   4,
  14,   5,  15,   0,  55,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,  29,   0,  58,  10,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,  52,   9,  53,  57
};
short	yytok2[] =
{
   2,   3,   6,   7,   8,  12,  13,  16,  17,  18,
  19,  25,  26,  27,  31,  32,  33,  34,  35,  36,
  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,
  47,  48,  49,  50
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
#line	51	"dbg.y"
{
			execute(yypt[-0].yyv.node);
			gc();
			if(interactive)
				Bprint(bout, "acid: ");
		} break;
case 4:
#line	58	"dbg.y"
{
			if(yypt[-7].yyv.sym->builtin)
				print("warning: %s() is a builtin; definition ignored\n", yypt[-7].yyv.sym->name);
			else
				yypt[-7].yyv.sym->proc = an(OLIST, yypt[-5].yyv.node, yypt[-1].yyv.node);
		} break;
case 5:
#line	65	"dbg.y"
{
			defcomplex(yypt[-4].yyv.node, yypt[-2].yyv.node);
		} break;
case 9:
#line	75	"dbg.y"
{
			yyval.node = an(OLIST, yypt[-1].yyv.node, yypt[-0].yyv.node);
		} break;
case 10:
#line	81	"dbg.y"
{
			yyval.node = an(ONAME, ZN, ZN);
			yyval.node->sym = yypt[-0].yyv.sym;
		} break;
case 11:
#line	88	"dbg.y"
{
			yypt[-1].yyv.node->nstore.u0.sival = yypt[-2].yyv.ival;
			yypt[-1].yyv.node->nstore.fmt = yypt[-3].yyv.ival;
			yyval.node = yypt[-1].yyv.node;
		} break;
case 12:
#line	94	"dbg.y"
{
			yypt[-1].yyv.node->nstore.u0.sival = yypt[-2].yyv.ival;
			yypt[-1].yyv.node->nstore.fmt = yypt[-4].yyv.ival;
			yypt[-1].yyv.node->right = yypt[-3].yyv.node;
			yyval.node = yypt[-1].yyv.node;
		} break;
case 13:
#line	101	"dbg.y"
{
			yypt[-1].yyv.node->nstore.u0.sival = yypt[-2].yyv.ival;
			yypt[-1].yyv.node->left = yypt[-3].yyv.node;
			yyval.node = yypt[-1].yyv.node;
		} break;
case 14:
#line	107	"dbg.y"
{
			yyval.node = an(OCTRUCT, yypt[-2].yyv.node, ZN);
		} break;
case 15:
#line	113	"dbg.y"
{ yyval.sym = 0; } break;
case 18:
#line	119	"dbg.y"
{
			yyval.node = an(OLIST, yypt[-1].yyv.node, yypt[-0].yyv.node);
		} break;
case 20:
#line	126	"dbg.y"
{
			yyval.node = yypt[-1].yyv.node;
		} break;
case 21:
#line	130	"dbg.y"
{
			yyval.node = an(OIF, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 22:
#line	134	"dbg.y"
{
			yyval.node = an(OIF, yypt[-4].yyv.node, an(OELSE, yypt[-2].yyv.node, yypt[-0].yyv.node));
		} break;
case 23:
#line	138	"dbg.y"
{
			yyval.node = an(ODO, an(OLIST, yypt[-4].yyv.node, yypt[-2].yyv.node), yypt[-0].yyv.node);
		} break;
case 24:
#line	142	"dbg.y"
{
			yyval.node = an(OWHILE, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 25:
#line	146	"dbg.y"
{
			yyval.node = an(ORET, yypt[-1].yyv.node, ZN);
		} break;
case 26:
#line	150	"dbg.y"
{
			yyval.node = an(OLOCAL, yypt[-0].yyv.node, ZN);
		} break;
case 27:
#line	154	"dbg.y"
{
			yyval.node = an(OCOMPLEX, yypt[-1].yyv.node, ZN);
			yyval.node->sym = yypt[-2].yyv.sym;
		} break;
case 28:
#line	161	"dbg.y"
{
			yyval.node = an(ONAME, ZN, ZN);
			yyval.node->sym = yypt[-0].yyv.sym;
		} break;
case 29:
#line	166	"dbg.y"
{
			yyval.node = an(ONAME, yypt[-2].yyv.node, ZN);
			yyval.node->sym = yypt[-0].yyv.sym;
		} break;
case 30:
#line	173	"dbg.y"
{ yyval.node = 0; } break;
case 33:
#line	179	"dbg.y"
{
			yyval.node = an(OMUL, yypt[-2].yyv.node, yypt[-0].yyv.node); 
		} break;
case 34:
#line	183	"dbg.y"
{
			yyval.node = an(ODIV, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 35:
#line	187	"dbg.y"
{
			yyval.node = an(OMOD, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 36:
#line	191	"dbg.y"
{
			yyval.node = an(OADD, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 37:
#line	195	"dbg.y"
{
			yyval.node = an(OSUB, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 38:
#line	199	"dbg.y"
{
			yyval.node = an(ORSH, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 39:
#line	203	"dbg.y"
{
			yyval.node = an(OLSH, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 40:
#line	207	"dbg.y"
{
			yyval.node = an(OLT, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 41:
#line	211	"dbg.y"
{
			yyval.node = an(OGT, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 42:
#line	215	"dbg.y"
{
			yyval.node = an(OLEQ, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 43:
#line	219	"dbg.y"
{
			yyval.node = an(OGEQ, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 44:
#line	223	"dbg.y"
{
			yyval.node = an(OEQ, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 45:
#line	227	"dbg.y"
{
			yyval.node = an(ONEQ, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 46:
#line	231	"dbg.y"
{
			yyval.node = an(OLAND, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 47:
#line	235	"dbg.y"
{
			yyval.node = an(OXOR, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 48:
#line	239	"dbg.y"
{
			yyval.node = an(OLOR, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 49:
#line	243	"dbg.y"
{
			yyval.node = an(OCAND, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 50:
#line	247	"dbg.y"
{
			yyval.node = an(OCOR, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 51:
#line	251	"dbg.y"
{
			yyval.node = an(OASGN, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 52:
#line	255	"dbg.y"
{
			yyval.node = an(OFMT, yypt[-1].yyv.node, con(yypt[-0].yyv.ival));
		} break;
case 54:
#line	262	"dbg.y"
{
			yyval.node = an(OCAST, yypt[-0].yyv.node, ZN);
			yyval.node->sym = yypt[-2].yyv.sym;
		} break;
case 56:
#line	270	"dbg.y"
{
			yyval.node = an(OINDM, yypt[-0].yyv.node, ZN);
		} break;
case 57:
#line	274	"dbg.y"
{
			yyval.node = an(OINDC, yypt[-0].yyv.node, ZN);
		} break;
case 58:
#line	278	"dbg.y"
{
			yyval.node = con(0);
			yyval.node = an(OADD, yypt[-0].yyv.node, yyval.node);
		} break;
case 59:
#line	283	"dbg.y"
{
			yyval.node = con(0);
			yyval.node = an(OSUB, yyval.node, yypt[-0].yyv.node);
		} break;
case 60:
#line	288	"dbg.y"
{
			yyval.node = an(OEDEC, yypt[-0].yyv.node, ZN);
		} break;
case 61:
#line	292	"dbg.y"
{
			yyval.node = an(OEINC, yypt[-0].yyv.node, ZN);
		} break;
case 62:
#line	296	"dbg.y"
{
			yyval.node = an(OHEAD, yypt[-0].yyv.node, ZN);
		} break;
case 63:
#line	300	"dbg.y"
{
			yyval.node = an(OTAIL, yypt[-0].yyv.node, ZN);
		} break;
case 64:
#line	304	"dbg.y"
{
			yyval.node = an(OAPPEND, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 65:
#line	308	"dbg.y"
{
			yyval.node = an(ODELETE, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
case 66:
#line	312	"dbg.y"
{
			yyval.node = an(ONOT, yypt[-0].yyv.node, ZN);
		} break;
case 67:
#line	316	"dbg.y"
{
			yyval.node = an(OXOR, yypt[-0].yyv.node, con(-1));
		} break;
case 68:
#line	320	"dbg.y"
{
			yyval.node = an(OEVAL, yypt[-0].yyv.node, ZN);	
		} break;
case 69:
#line	326	"dbg.y"
{
			yyval.node = yypt[-1].yyv.node;
		} break;
case 70:
#line	330	"dbg.y"
{
			yyval.node = an(OCTRUCT, yypt[-1].yyv.node, ZN);
		} break;
case 71:
#line	334	"dbg.y"
{
			yyval.node = an(OINDEX, yypt[-3].yyv.node, yypt[-1].yyv.node);
		} break;
case 72:
#line	338	"dbg.y"
{
			yyval.node = an(OPDEC, yypt[-1].yyv.node, ZN);
		} break;
case 73:
#line	342	"dbg.y"
{
			yyval.node = an(ODOT, yypt[-2].yyv.node, ZN);
			yyval.node->sym = yypt[-0].yyv.sym;
		} break;
case 74:
#line	347	"dbg.y"
{
			yyval.node = an(ODOT, an(OINDM, yypt[-2].yyv.node, ZN), ZN);
			yyval.node->sym = yypt[-0].yyv.sym;
		} break;
case 75:
#line	352	"dbg.y"
{
			yyval.node = an(OPINC, yypt[-1].yyv.node, ZN);
		} break;
case 76:
#line	356	"dbg.y"
{
			yyval.node = an(OCALL, yypt[-3].yyv.node, yypt[-1].yyv.node);
		} break;
case 78:
#line	361	"dbg.y"
{
			yyval.node = con(yypt[-0].yyv.ival);
		} break;
case 79:
#line	365	"dbg.y"
{
			yyval.node = an(OCONST, ZN, ZN);
			yyval.node->type = TFLOAT;
			yyval.node->nstore.fmt = 'f';
			yyval.node->nstore.u0.sfval = yypt[-0].yyv.fval;
		} break;
case 80:
#line	372	"dbg.y"
{
			yyval.node = an(OCONST, ZN, ZN);
			yyval.node->type = TSTRING;
			yyval.node->nstore.u0.sstring = yypt[-0].yyv.string;
			yyval.node->nstore.fmt = 's';
		} break;
case 81:
#line	379	"dbg.y"
{
			yyval.node = an(OWHAT, ZN, ZN);
			yyval.node->sym = yypt[-0].yyv.sym;
		} break;
case 82:
#line	386	"dbg.y"
{
			yyval.node = an(ONAME, ZN, ZN);
			yyval.node->sym = yypt[-0].yyv.sym;
		} break;
case 83:
#line	391	"dbg.y"
{
			yyval.node = an(OFRAME, yypt[-0].yyv.node, ZN);
			yyval.node->sym = yypt[-2].yyv.sym;
		} break;
case 85:
#line	399	"dbg.y"
{
			yyval.node = an(OLIST, yypt[-2].yyv.node, yypt[-0].yyv.node);
		} break;
	}
	goto yystack;  /* stack new state and value */
}
