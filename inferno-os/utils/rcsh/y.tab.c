
#line	2	"syn.y"
#include "rc.h"

#line	19	"syn.y"
typedef union {
	Tree *tree;
} YYSTYPE;
extern	int	yyerrflag;
#ifndef	YYMAXDEPTH
#define	YYMAXDEPTH	150
#endif
YYSTYPE	yylval;
YYSTYPE	yyval;
#define	IF	57346
#define	WHILE	57347
#define	FOR	57348
#define	SWITCH	57349
#define	NOT	57350
#define	ANDAND	57351
#define	OROR	57352
#define	BANG	57353
#define	SUBSHELL	57354
#define	PIPE	57355
#define	COUNT	57356
#define	SUB	57357
#define	IN	57358
#define	TWIDDLE	57359
#define	FN	57360
#define	WORD	57361
#define	REDIR	57362
#define	DUP	57363
#define	SIMPLE	57364
#define	ARGLIST	57365
#define	WORDS	57366
#define	BRACE	57367
#define	PAREN	57368
#define	PCMD	57369
#define	PIPEFD	57370
#define YYEOFCODE 1
#define YYERRCODE 2
short	yyexca[] =
{-1, 0,
	1, 1,
	-2, 18,
-1, 1,
	1, -1,
	-2, 0,
};
#define	YYNPROD	70
#define	YYPRIVATE 57344
#define	YYLAST	371
short	yyact[] =
{
  64,   3,  39,  31,  32,   3,  63,  33,  62,  38,
   5,  68,  12,  58,  59,  60,  61,  40,  36,  21,
  89,  35,  17,  56,  28,  94,  90,  29,  30,  44,
  44,  44,  75,  76,  77,  67,  74,  73,  39,  44,
  19,  20,  44,  44,  44,  88,  81,  85,  33,  36,
  31,  32, 100,  37,  33,  42,  55,  57,  78,  85,
  44,  98,  41,  84,  99,  69,  86,  83,  70,  71,
  72,   2,  91,  87,  29,  30,  34, 106,  66,   4,
  96,  97,  44,   4, 101, 110,  82,  44,  44,  31,
  32,  80,  79,  33,  44, 102,   1,  43,  18,  10,
  13,  65,   0, 104,   0,  44,  44, 109, 105,   0,
   0, 111,   0,  92,  93,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  44,  44,   0,  48,  47,  45,
  53, 103,  49,   0,   0,  51,  52,   0,   0,  22,
  24,  23,   0,  46,  50,  54,  25,  19,  20,   0,
   0,   0,   0,   0,   0,   0,   6,   8,   7,   9,
   0,  27,   0,  26,  14,  15,   0,   0,  22,  24,
  23,   0,   0,  11,  16,  25,  19,  20,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  17,   0,
  27,   0,  26,  48,  47,  45,  53, 108,  49,   0,
   0,  51,  52,   0,   0,  22,  24,  23,   0,  46,
  50,  54,  25,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,  27,   0,  26,
  48,  47,  45,  53, 107,  49,   0,   0,  51,  52,
   0,   0,  22,  24,  23,   0,  46,  50,  54,  25,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  27,   0,  26,  48,  47,  45,
  53,  95,  49,   0,   0,  51,  52,   0,   0,  22,
  24,  23,   0,  46,  50,  54,  25,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,  48,  47,  45,
  53,  27,  49,  26,   0,  51,  52,   0,   0,  22,
  24,  23,   0,  46,  50,  54,  25,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,  17,
   0,  27,   0,  26,  48,  47,  45,  53,   0,  49,
   0,   0,  51,  52,   0,   0,  22,  24,  23,   0,
  46,  50,  54,  25,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  27,   0,
  26
};
short	yypact[] =
{
 152,-1000,  -9,  40, 152,  16,   0, -21, -36, 330,
 123, 330, 152, 152, 152, 152,-1000, 152,  -4, 330,
-1000,-1000, 330, 330, 330,-1000, -14,-1000,-1000,-1000,
-1000, 152, 152, 152,-1000,-1000,  16,-1000,-1000, 152,
 330,-1000,  32,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,  32,-1000,  32,  34,  34,
  34,  34, 293, -17,  -7, 152,-1000, 330, 330,  32,
   6,-1000,-1000,-1000, 263,  34,  34,-1000,-1000, 152,
 152,  53,  44, 152, -14, 330, 330,-1000,  32,-1000,
-1000,-1000,  32,-1000,-1000,-1000,  79,  79,-1000,-1000,
-1000,  79,-1000,-1000, 226, 189, 152,-1000,-1000,  79,
 152,  79
};
short	yypgo[] =
{
   0,  71,  53,  10,   6,  78, 101, 100,  21,  12,
   0,  99,  98,  45,  19,  97,   8,  96,  92,  91,
  85,  77,  67,  63
};
short	yyr1[] =
{
   0,  17,  17,   1,   1,   4,   4,   5,   5,   6,
   6,   3,   2,   7,   8,   8,   9,   9,  10,  10,
  18,  10,  19,  10,  20,  10,  21,  10,  22,  10,
  23,  10,  10,  10,  10,  10,  10,  10,  10,  10,
  10,  10,  10,  11,  11,  11,  12,  12,  13,  13,
  13,  14,  14,  14,  14,  14,  14,  14,  15,  15,
  15,  15,  15,  15,  15,  15,  15,  15,  16,  16
};
short	yyr2[] =
{
   0,   0,   2,   1,   2,   1,   2,   2,   2,   1,
   2,   3,   3,   3,   0,   2,   2,   1,   0,   2,
   0,   4,   0,   4,   0,   8,   0,   6,   0,   4,
   0,   4,   1,   3,   3,   3,   3,   2,   2,   2,
   2,   3,   2,   1,   2,   2,   1,   3,   1,   1,
   3,   2,   5,   2,   2,   1,   2,   3,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   0,   2
};
short	yychk[] =
{
-1000, -17,  -1, -10,  -5,  -3,   4,   6,   5,   7,
 -11,  21,  -9,  -7,  12,  13,  22,  36, -12,  24,
  25, -14,  16,  18,  17,  23,  40,  38,  33,  34,
  35,  10,  11,  14,  -1,  -8,  -9,  -2,   9,  38,
  38,  -2, -13, -15, -14,   6,  20,   5,   4,   9,
  21,  12,  13,   7,  22, -13,  -9, -13, -10, -10,
 -10, -10, -16,  -4, -10,  -6,  -5,  39,  15, -13,
 -13, -13, -13,  -3, -16, -10, -10, -10,  -8, -18,
 -19,  -4, -13, -22, -23,  15, -16,  -3, -13,  37,
  33,  -4, -13, -13,  19,   8, -10, -10,   8,  20,
   8, -10,  -3, -13, -16, -16, -21,   8,   8, -10,
 -20, -10
};
short	yydef[] =
{
  -2,  -2,   0,   3,  18,  14,   0,   0,   0,   0,
  32,   0,  18,  18,  18,  18,  68,  18,  43,   0,
  17,  46,   0,   0,   0,  55,   0,  68,   2,   7,
   8,  18,  18,  18,   4,  19,  14,  20,  22,  18,
   0,  28,  30,  48,  49,  58,  59,  60,  61,  62,
  63,  64,  65,  66,  67,  44,  45,  68,  37,  38,
  39,  40,  42,   0,   5,  18,   9,   0,   0,  16,
  51,  53,  54,  56,   0,  34,  35,  36,  15,  18,
  18,   0,   0,  18,   0,   0,  33,  41,  69,  11,
  10,   6,  13,  47,  68,  57,  21,  23,  12,  68,
  26,  29,  31,  50,   0,   0,  18,  52,  24,  27,
  18,  25
};
short	yytok1[] =
{
   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,
  33,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  18,   0,  16,   0,  35,   0,
  38,   8,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,  34,
   0,  39,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,  15,   0,  40,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,  36,   0,  37
};
short	yytok2[] =
{
   2,   3,   4,   5,   6,   7,   9,  10,  11,  12,
  13,  14,  17,  19,  20,  21,  22,  23,  24,  25,
  26,  27,  28,  29,  30,  31,  32
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
		
case 1:
#line	30	"syn.y"
{ return 1;} break;
case 2:
#line	31	"syn.y"
{return !compile(yypt[-1].yyv.tree);} break;
case 4:
#line	33	"syn.y"
{yyval.tree=tree2(';', yypt[-1].yyv.tree, yypt[-0].yyv.tree);} break;
case 6:
#line	35	"syn.y"
{yyval.tree=tree2(';', yypt[-1].yyv.tree, yypt[-0].yyv.tree);} break;
case 8:
#line	37	"syn.y"
{yyval.tree=tree1('&', yypt[-1].yyv.tree);} break;
case 11:
#line	40	"syn.y"
{yyval.tree=tree1(BRACE, yypt[-1].yyv.tree);} break;
case 12:
#line	41	"syn.y"
{yyval.tree=tree1(PCMD, yypt[-1].yyv.tree);} break;
case 13:
#line	42	"syn.y"
{yyval.tree=tree2('=', yypt[-2].yyv.tree, yypt[-0].yyv.tree);} break;
case 14:
#line	43	"syn.y"
{yyval.tree=0;} break;
case 15:
#line	44	"syn.y"
{yyval.tree=mung2(yypt[-1].yyv.tree, yypt[-1].yyv.tree->child[0], yypt[-0].yyv.tree);} break;
case 16:
#line	45	"syn.y"
{yyval.tree=mung1(yypt[-1].yyv.tree, yypt[-1].yyv.tree->rtype==HERE?heredoc(yypt[-0].yyv.tree):yypt[-0].yyv.tree);} break;
case 18:
#line	47	"syn.y"
{yyval.tree=0;} break;
case 19:
#line	48	"syn.y"
{yyval.tree=epimung(yypt[-1].yyv.tree, yypt[-0].yyv.tree);} break;
case 20:
#line	49	"syn.y"
{skipnl();} break;
case 21:
#line	50	"syn.y"
{yyval.tree=mung2(yypt[-3].yyv.tree, yypt[-2].yyv.tree, yypt[-0].yyv.tree);} break;
case 22:
#line	51	"syn.y"
{skipnl();} break;
case 23:
#line	51	"syn.y"
{yyval.tree=mung1(yypt[-2].yyv.tree, yypt[-0].yyv.tree);} break;
case 24:
#line	52	"syn.y"
{skipnl();} break;
case 25:
#line	53	"syn.y"
{yyval.tree=mung3(yypt[-7].yyv.tree, yypt[-5].yyv.tree, tree1(PAREN, yypt[-3].yyv.tree), yypt[-0].yyv.tree);} break;
case 26:
#line	54	"syn.y"
{skipnl();} break;
case 27:
#line	55	"syn.y"
{yyval.tree=mung3(yypt[-5].yyv.tree, yypt[-3].yyv.tree, 0, yypt[-0].yyv.tree);} break;
case 28:
#line	56	"syn.y"
{skipnl();} break;
case 29:
#line	57	"syn.y"
{yyval.tree=mung2(yypt[-3].yyv.tree, yypt[-2].yyv.tree, yypt[-0].yyv.tree);} break;
case 30:
#line	58	"syn.y"
{skipnl();} break;
case 31:
#line	59	"syn.y"
{yyval.tree=tree2(SWITCH, yypt[-2].yyv.tree, yypt[-0].yyv.tree);} break;
case 32:
#line	60	"syn.y"
{yyval.tree=simplemung(yypt[-0].yyv.tree);} break;
case 33:
#line	61	"syn.y"
{yyval.tree=mung2(yypt[-2].yyv.tree, yypt[-1].yyv.tree, yypt[-0].yyv.tree);} break;
case 34:
#line	62	"syn.y"
{yyval.tree=tree2(ANDAND, yypt[-2].yyv.tree, yypt[-0].yyv.tree);} break;
case 35:
#line	63	"syn.y"
{yyval.tree=tree2(OROR, yypt[-2].yyv.tree, yypt[-0].yyv.tree);} break;
case 36:
#line	64	"syn.y"
{yyval.tree=mung2(yypt[-1].yyv.tree, yypt[-2].yyv.tree, yypt[-0].yyv.tree);} break;
case 37:
#line	65	"syn.y"
{yyval.tree=mung2(yypt[-1].yyv.tree, yypt[-1].yyv.tree->child[0], yypt[-0].yyv.tree);} break;
case 38:
#line	66	"syn.y"
{yyval.tree=mung3(yypt[-1].yyv.tree, yypt[-1].yyv.tree->child[0], yypt[-1].yyv.tree->child[1], yypt[-0].yyv.tree);} break;
case 39:
#line	67	"syn.y"
{yyval.tree=mung1(yypt[-1].yyv.tree, yypt[-0].yyv.tree);} break;
case 40:
#line	68	"syn.y"
{yyval.tree=mung1(yypt[-1].yyv.tree, yypt[-0].yyv.tree);} break;
case 41:
#line	69	"syn.y"
{yyval.tree=tree2(FN, yypt[-1].yyv.tree, yypt[-0].yyv.tree);} break;
case 42:
#line	70	"syn.y"
{yyval.tree=tree1(FN, yypt[-0].yyv.tree);} break;
case 44:
#line	72	"syn.y"
{yyval.tree=tree2(ARGLIST, yypt[-1].yyv.tree, yypt[-0].yyv.tree);} break;
case 45:
#line	73	"syn.y"
{yyval.tree=tree2(ARGLIST, yypt[-1].yyv.tree, yypt[-0].yyv.tree);} break;
case 47:
#line	75	"syn.y"
{yyval.tree=tree2('^', yypt[-2].yyv.tree, yypt[-0].yyv.tree);} break;
case 48:
#line	76	"syn.y"
{yypt[-0].yyv.tree->type=WORD;} break;
case 50:
#line	78	"syn.y"
{yyval.tree=tree2('^', yypt[-2].yyv.tree, yypt[-0].yyv.tree);} break;
case 51:
#line	79	"syn.y"
{yyval.tree=tree1('$', yypt[-0].yyv.tree);} break;
case 52:
#line	80	"syn.y"
{yyval.tree=tree2(SUB, yypt[-3].yyv.tree, yypt[-1].yyv.tree);} break;
case 53:
#line	81	"syn.y"
{yyval.tree=tree1('"', yypt[-0].yyv.tree);} break;
case 54:
#line	82	"syn.y"
{yyval.tree=tree1(COUNT, yypt[-0].yyv.tree);} break;
case 56:
#line	84	"syn.y"
{yyval.tree=tree1('`', yypt[-0].yyv.tree);} break;
case 57:
#line	85	"syn.y"
{yyval.tree=tree1(PAREN, yypt[-1].yyv.tree);} break;
case 68:
#line	89	"syn.y"
{yyval.tree=0;} break;
case 69:
#line	90	"syn.y"
{yyval.tree=tree2(WORDS, yypt[-1].yyv.tree, yypt[-0].yyv.tree);} break;
	}
	goto yystack;  /* stack new state and value */
}
