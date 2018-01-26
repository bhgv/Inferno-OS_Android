
#line	2	"a.y"
#include "a.h"

#line	4	"a.y"
typedef union 
{
	Sym	*sym;
	long	lval;
	double	dval;
	char	sval[8];
	Gen	gen;
} YYSTYPE;
extern	int	yyerrflag;
#ifndef	YYMAXDEPTH
#define	YYMAXDEPTH	150
#endif
YYSTYPE	yylval;
YYSTYPE	yyval;
#define	LTYPE1	57346
#define	LTYPE2	57347
#define	LTYPE3	57348
#define	LTYPE4	57349
#define	LTYPE5	57350
#define	LTYPE6	57351
#define	LTYPE7	57352
#define	LTYPE8	57353
#define	LTYPE9	57354
#define	LTYPEA	57355
#define	LTYPEB	57356
#define	LTYPEC	57357
#define	LTYPED	57358
#define	LTYPEE	57359
#define	LTYPEF	57360
#define	LTYPEG	57361
#define	LTYPEH	57362
#define	LTYPEI	57363
#define	LTYPEJ	57364
#define	LTYPEK	57365
#define	LTYPEL	57366
#define	LTYPEM	57367
#define	LTYPEN	57368
#define	LTYPEBX	57369
#define	LCONST	57370
#define	LSP	57371
#define	LSB	57372
#define	LFP	57373
#define	LPC	57374
#define	LTYPEX	57375
#define	LR	57376
#define	LREG	57377
#define	LF	57378
#define	LFREG	57379
#define	LC	57380
#define	LCREG	57381
#define	LPSR	57382
#define	LFCR	57383
#define	LCOND	57384
#define	LS	57385
#define	LAT	57386
#define	LFCONST	57387
#define	LSCONST	57388
#define	LNAME	57389
#define	LLAB	57390
#define	LVAR	57391
#define YYEOFCODE 1
#define YYERRCODE 2
short	yyexca[] =
{-1, 1,
	1, -1,
	-2, 0,
-1, 190,
	65, 57,
	-2, 45,
};
#define	YYNPROD	128
#define	YYPRIVATE 57344
#define	yydebug	1
#define	YYLAST	659
short	yyact[] =
{
 130, 119, 310, 100,  94,  76,  89, 107,  77, 265,
 196, 123,  87,  96,  78,  95, 103,  80,  81, 189,
 235,  41,  43, 108,   2, 320, 306,  82, 288, 278,
  84,  60,  85,  83,  70,  72, 277, 276,  67,  79,
  79,  79, 273, 272, 251,  88, 237,  79, 104, 316,
 114,  42, 112, 117,  90, 118, 120, 304, 105, 167,
  99, 289, 200, 106, 240, 132, 191, 133, 183,  55,
  54, 141, 142, 176, 175, 166, 163, 134, 136, 139,
 122,  49,  58, 297, 102, 101,  55, 173, 170, 245,
  74,  75, 246, 143, 144, 244,  74,  75,  52,  82,
 174, 169,  84, 322,  85,  83, 138,  42, 174, 315,
 313, 309,  55,  54,  79,  52, 307, 190,  88,  53,
 295, 181, 184, 185, 294, 186,  57,  90, 177,  56,
 194,  42, 172, 171,  51, 193,  53, 291, 284, 281,
 206,  52, 264,  98, 254,  42,  56, 214, 215, 216,
 217, 218, 250, 249, 221, 222, 223, 213, 236, 224,
  71, 212,  53, 225, 230, 182,  36,  79, 233,  57,
 231,  88,  56, 211, 210, 208, 207, 192, 232, 188,
  90,  50,  50, 187, 165, 164, 234, 157, 121, 243,
  35,  97, 241,  34, 238,  32,  33,  31, 247, 209,
  93, 236, 312, 311, 109, 102, 101, 116, 242, 248,
 234, 252, 259, 253, 300, 127, 128, 129, 260, 261,
 262, 263, 131, 255, 256, 140, 258, 229, 266, 266,
 266, 266, 102, 257,  55,  54, 228, 268, 269, 270,
 274, 162, 125, 126, 172, 227, 190, 220, 282, 190,
 201, 279,  55,  54, 137, 286, 285, 168, 226, 287,
 219, 290,   7,  52, 280, 179, 292, 283,  69,  68,
 296,  55,  54,  93,   1,  55,  54,  74,  75, 178,
 135,  52, 195, 303,  53, 298, 202, 203, 321, 115,
 299,  98, 205,  82,  56, 302,  84,   0,  85,  83,
  52, 305,  53,   0,  52,   0, 308, 301,   0,  57,
   0, 314,  56,   0,   0, 317,   0, 319, 318, 180,
 111,  53,   0, 324,   0,  53,  93,  84,  98,  85,
  83,  56,  98,   0, 127,  56,   0, 239,   8, 155,
 154, 153, 151, 152, 146, 147, 148, 149, 150,   0,
   9,  10,  11,  12,  14,  15,  16,  17,  18,  19,
  20,  21,  22,  30,   0,   0,  23,  24,  27,  25,
  26,  28,  29,  13,  55,  54, 155, 154, 153, 151,
 152, 146, 147, 148, 149, 150,  73, 267, 267, 267,
 267,   0,   0,   4,   3,   5, 275,   0,   6, 102,
 101,   0, 323,  52,  82,  74,  75,  84,   0,  85,
  83, 102, 101,   0,   0,  91,  92,  74,  75,  55,
  54,   0,  51,  82,  53,  86,  84,   0,  85,  83,
   0,  98, 113,  96,  56,   0,  74,  75, 124, 271,
 125, 126, 116,   0,  55,  54,   0,  42,  52,  82,
   0,   0,  84,   0,  85,  83, 102, 101,   0,   0,
  91,  92,  55,  54, 198, 197, 199,  51,   0,  53,
  55,  54,   0,  52,  55,  54,  98,   0,  96,  56,
 155, 154, 153, 151, 152, 146, 147, 148, 149, 150,
   0,  52, 110, 111,  53,   0,  55,  54,   0,  52,
   0,  57,   0,  52,  56,  74,  75, 158, 159,   0,
 160,   0,  53, 198, 197, 199, 242,   0,  51,  57,
  53,   0,  56,  82,  53,  52,  84,  98,  85,  83,
  56,  57,   0,  80,  56,  82,  74,  75,  84,   0,
  85,  83,   0, 204,  51,   0,  53,   0,  74,  75,
   0,   0,  80,  57, 161,   0,  56, 155, 154, 153,
 151, 152, 146, 147, 148, 149, 150, 155, 154, 153,
 151, 152, 146, 147, 148, 149, 150, 155, 154, 153,
 151, 152, 146, 147, 148, 149, 150, 198, 197, 199,
  84,   0,  85,  83,  37, 155, 154, 153, 151, 152,
 146, 147, 148, 149, 150,  38,  39,  40,   0,   0,
  44,  45,  46,  47,  48,   0, 293,  59,   0,  61,
  62,  63,  64,  65,  66, 156, 154, 153, 151, 152,
 146, 147, 148, 149, 150, 145, 153, 151, 152, 146,
 147, 148, 149, 150, 151, 152, 146, 147, 148, 149,
 150, 146, 147, 148, 149, 150, 148, 149, 150
};
short	yypact[] =
{
-1000, 336,-1000, 137, 135, 132,-1000, 128, 104,-1000,
-1000,-1000,-1000,  68,  68,-1000,-1000,-1000,-1000,-1000,
 487, 487,-1000,  68,-1000,-1000,-1000,-1000,-1000,-1000,
  68,-1000,-1000, 243, 243,-1000,-1000, 484, 484, 365,
  44,  -3,  68, 435,  44, 484, 225, 384,  44, 125,
  14, 431,-1000,-1000, 243, 243, 243, 243, 210, 496,
 -55, 353,  38, 353, 453, 496, 496,-1000, 336, 336,
 573,-1000, 563, 124,-1000,-1000,-1000,-1000,-1000, 500,
 243,-1000,-1000,-1000,-1000,  10, 122, 121,-1000,-1000,
   9,-1000,-1000,  -7,-1000,-1000,  77,-1000,  60,   8,
-1000,-1000,   7,-1000, 262,-1000, 254,-1000,-1000,   2,
 233, 233, 410, 120, 116, 254,   0, 114,  -3,-1000,
-1000, 465, 425,  -4, 242, 243, 243,-1000,-1000,-1000,
 476, 243,  68,-1000, 113, 112,-1000,-1000, 189, 111,
 110,  98,  94,-1000,-1000,-1000, 243, 243, 243, 243,
 243, 253, 239, 243, 243, 243,-1000, 254, 251, 237,
 228, 219,-1000, 243, 254, 410, 254, 548,  -7,-1000,
 -48,-1000,-1000, 103, -21, 285, 243,-1000,-1000,  -2,
 431,-1000,-1000, 166,-1000,-1000,-1000, 254,  31,  24,
  82, 285,  -3,  90,-1000,  89, -23,-1000,-1000,-1000,
 425, 233,-1000,-1000,-1000,  81,-1000, 159, 186, 146,
 159, 243, 254, 254, 645, 645,-1000,-1000,-1000, 243,
 243, 637, 630, 621,  79,-1000,  60,  60,  60,  60,
 372,-1000,-1000, -24, -25, 461,-1000,-1000, -30, -31,
 474,  -4, -38,  68, 254,  76, 254, 254,  75, 254,
 -51,-1000, -39,  -5, -55,-1000,-1000,  74,  68, 553,
  61,  57, 642, 642, 254,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,  -7,-1000,-1000,-1000,-1000,
  18, 266,-1000,-1000, -12,-1000,-1000,-1000,-1000, 174,
-1000, 159,-1000, 254,  -9, 254,-1000,-1000,-1000,-1000,
 -41,-1000,  53,-1000, 254,  48,-1000, 154,  47, 254,
  46,-1000, -17, 254,-1000, 154, 243, -42,  40, 335,
-1000,-1000, 243,-1000, 591
};
short	yypgo[] =
{
   0, 160,   0, 288,  10,  11,  18,   1,   2,   9,
 594,  19,  12,  23,   5, 283,  15,  14, 191, 280,
   8,   6,  60,   4,  16, 279,   3, 386, 274,  24,
 269, 268, 262,   7
};
short	yyr1[] =
{
   0,  28,  28,  30,  29,  31,  29,  29,  29,  29,
  29,  29,  32,  32,  32,  32,  32,  32,  32,  32,
  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
  32,  32,  32,  32,  32,  32,  32,  32,  32,  32,
  32,  32,  10,  10,  10,  33,  33,  13,  13,  13,
  21,  21,  21,  21,  21,  18,  18,  11,  11,  11,
  12,  12,  12,  12,  12,  12,  12,  12,  12,  25,
  25,  24,  26,  26,  23,  23,  23,  27,  27,  27,
  20,  14,  15,  17,  17,  17,  17,   9,   9,   6,
   6,   6,   7,   7,   8,   8,  19,  19,  16,  16,
  22,  22,  22,   5,   5,   5,   4,   4,   4,   1,
   1,   1,   1,   1,   1,   3,   3,   2,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2
};
short	yyr2[] =
{
   0,   0,   2,   0,   4,   0,   4,   4,   4,   1,
   2,   2,   7,   6,   5,   5,   5,   4,   4,   3,
   3,   4,   6,   7,   7,   7,   6,   6,   3,   4,
   6,   6,   4,   3,   5,   5,   7,   6,  12,   7,
   9,   2,   0,   2,   2,   0,   2,   4,   2,   2,
   2,   2,   4,   2,   1,   2,   3,   1,   3,   3,
   1,   1,   1,   4,   1,   1,   1,   1,   1,   1,
   1,   3,   1,   4,   1,   4,   1,   1,   1,   1,
   2,   1,   5,   4,   4,   4,   4,   1,   1,   1,
   1,   4,   1,   1,   1,   4,   1,   1,   1,   4,
   4,   5,   7,   0,   2,   2,   1,   1,   1,   1,
   1,   2,   2,   2,   3,   0,   2,   1,   3,   3,
   3,   3,   3,   4,   4,   3,   3,   3
};
short	yychk[] =
{
-1000, -28, -29,  58,  57,  59,  62, -32,   2,  14,
  15,  16,  17,  37,  18,  19,  20,  21,  22,  23,
  24,  25,  26,  30,  31,  33,  34,  32,  35,  36,
  27,  60,  60,  61,  61,  62,  62, -10, -10, -10,
 -10, -33,  63, -33, -10, -10, -10, -10, -10, -22,
  -1,  57,  38,  59,  10,   9,  69,  66, -22, -10,
 -33, -10, -10, -10, -10, -10, -10, -33, -30, -31,
  -2,  -1,  -2, -27,  52,  53, -14, -20, -17,  -7,
  68,  -6,  39,  45,  42,  44, -27, -12, -14, -21,
 -17,  50,  51,  -1, -23, -16,  68, -18,  66, -22,
 -26,  47,  46, -24, -33, -24,  66, -33, -13,  -1,
  57,  58, -33, -27, -26,  64,  -1, -14, -33,  -7,
 -33,  63,  66,  -5,   7,   9,  10,  -1,  -1,  -1,
  -2,  12, -14, -21, -16, -19, -16, -18,  68, -16,
  -1, -14, -14, -29, -29,  62,   9,  10,  11,  12,
  13,   7,   8,   6,   5,   4,  62,  63,   7,   8,
  10,  54,  -1,  66,  63,  63,  66,  66,  -1, -23,
  11,  56,  55,  10,  -7,  66,  66, -13, -25,  -1,
  57, -24, -22,  66,  -5,  -5, -12,  63,  63, -11,
  -7,  66,  63, -24, -20,  -1,  -4,  40,  39,  41,
  66,   8,  -1,  -1,  67,  -1, -33,  63,  63,  10,
  63,  63,  63,  63,  -2,  -2,  -2,  -2,  -2,   7,
   8,  -2,  -2,  -2,  -7, -14,   7,   8,   8,   8,
  -2, -14, -12,  -7,  -6,  68,  55,  67,  -6,  -1,
  66,  -5,  42,  -7,  64,  65,  10, -33, -24,  63,
  63,  67,  -4,  -5,  63, -16, -16,  47, -16,  -2,
 -14, -14,  -2,  -2,  63,  -9,  -7,  -1,  -9,  -9,
  -9,  67,  67,  67, -23,  -1,  67,  67,  67, -33,
 -11,  63,  -7, -11,  63, -33, -14, -20,  67,  66,
 -21,  63, -33,  63,  63,  63, -14,  65, -26, -14,
  40, -16,  -7, -15,  66, -14,  67,  63,  -7,  63,
  -8,  49,  48,  63,  -7,  63,  66,  -7,  -8,  -2,
  67,  -3,  63,  67,  -2
};
short	yydef[] =
{
   1,  -2,   2,   0,   0,   0,   9,   0,   0,  42,
  42,  42,  42,  45,  45,  42,  42,  42,  42,  42,
   0,   0,  42,  45,  42,  42,  42,  42,  42,  42,
  45,   3,   5,   0,   0,  10,  11,   0,   0,   0,
  45,   0,  45,   0,  45,   0,   0,  45,  45,   0,
   0, 103, 109, 110,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,  41,   0,   0,
   0, 117,   0,   0,  43,  44,  77,  78,  79,  81,
   0,  92,  93,  89,  90,   0,   0,   0,  60,  61,
  62,  64,  65,  66,  67,  68,   0,  54,   0,  74,
  76,  98,   0,  72,   0,  19,   0,  46,  20,   0,
 103, 103,   0,   0,   0,   0,   0,   0,   0,  81,
  28,   0,   0,   0,   0,   0,   0, 111, 112, 113,
   0,   0,  45,  33,   0,   0,  96,  97,   0,   0,
   0,   0,   0,   4,   6,   7,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   8,   0,   0,   0,
   0,   0,  80,   0,   0,   0,   0,   0,  50,  51,
   0,  53,  55,   0,   0,   0,   0,  17,  18,   0,
 103,  69,  70,   0,  48,  49,  21,   0,   0,   0,
  -2,   0,   0,   0,  29,   0,   0, 106, 107, 108,
   0, 103, 104, 105, 114,   0,  32,   0,   0,   0,
   0,   0,   0,   0, 118, 119, 120, 121, 122,   0,
   0, 125, 126, 127,  81,  14,   0,   0,   0,   0,
   0,  15,  16,   0,   0,   0,  56,  71,   0,   0,
   0,  48,   0,  45,   0,   0,   0,   0,  45,   0,
   0, 100,   0,   0,   0,  34,  35,  98,  45,   0,
   0,   0, 123, 124,  13,  83,  87,  88,  84,  85,
  86,  91,  63,  73,  52,   0,  75,  99,  47,  22,
   0,   0,  58,  59,  45,  26,  27,  30, 101,   0,
  31,   0,  37,   0,   0,   0,  12,  23,  24,  25,
   0,  36,   0,  39,   0,   0, 102,   0,   0,   0,
   0,  94,   0,   0,  40,   0,   0,   0, 115,   0,
  82,  38,   0,  95, 116
};
short	yytok1[] =
{
   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,  68,  13,   6,   0,
  66,  67,  11,   9,  63,  10,   0,  12,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  60,  62,
   7,  61,   8,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,  64,   0,  65,   5,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   4,   0,  69
};
short	yytok2[] =
{
   2,   3,  14,  15,  16,  17,  18,  19,  20,  21,
  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,
  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,
  52,  53,  54,  55,  56,  57,  58,  59
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
#line	39	"a.y"
{
		if(yypt[-1].yyv.sym->value != pc)
			yyerror("redeclaration of %s", yypt[-1].yyv.sym->name);
		yypt[-1].yyv.sym->value = pc;
	} break;
case 5:
#line	46	"a.y"
{
		yypt[-1].yyv.sym->type = LLAB;
		yypt[-1].yyv.sym->value = pc;
	} break;
case 7:
#line	52	"a.y"
{
		yypt[-3].yyv.sym->type = LVAR;
		yypt[-3].yyv.sym->value = yypt[-1].yyv.lval;
	} break;
case 8:
#line	57	"a.y"
{
		if(yypt[-3].yyv.sym->value != yypt[-1].yyv.lval)
			yyerror("redeclaration of %s", yypt[-3].yyv.sym->name);
		yypt[-3].yyv.sym->value = yypt[-1].yyv.lval;
	} break;
case 12:
#line	71	"a.y"
{
		outcode(yypt[-6].yyv.lval, yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 13:
#line	75	"a.y"
{
		outcode(yypt[-5].yyv.lval, yypt[-4].yyv.lval, &yypt[-3].yyv.gen, yypt[-1].yyv.lval, &nullgen);
	} break;
case 14:
#line	79	"a.y"
{
		outcode(yypt[-4].yyv.lval, yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 15:
#line	86	"a.y"
{
		outcode(yypt[-4].yyv.lval, yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 16:
#line	93	"a.y"
{
		outcode(yypt[-4].yyv.lval, yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 17:
#line	100	"a.y"
{
		outcode(yypt[-3].yyv.lval, yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 18:
#line	104	"a.y"
{
		outcode(yypt[-3].yyv.lval, yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 19:
#line	111	"a.y"
{
		outcode(yypt[-2].yyv.lval, Always, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 20:
#line	118	"a.y"
{
		outcode(yypt[-2].yyv.lval, Always, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 21:
#line	125	"a.y"
{
		outcode(yypt[-3].yyv.lval, yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 22:
#line	132	"a.y"
{
		outcode(yypt[-5].yyv.lval, yypt[-4].yyv.lval, &yypt[-3].yyv.gen, yypt[-1].yyv.lval, &nullgen);
	} break;
case 23:
#line	139	"a.y"
{
		Gen g;

		g = nullgen;
		g.type = D_CONST;
		g.offset = yypt[-1].yyv.lval;
		outcode(yypt[-6].yyv.lval, yypt[-5].yyv.lval, &yypt[-4].yyv.gen, NREG, &g);
	} break;
case 24:
#line	148	"a.y"
{
		Gen g;

		g = nullgen;
		g.type = D_CONST;
		g.offset = yypt[-3].yyv.lval;
		outcode(yypt[-6].yyv.lval, yypt[-5].yyv.lval, &g, NREG, &yypt[-0].yyv.gen);
	} break;
case 25:
#line	160	"a.y"
{
		outcode(yypt[-6].yyv.lval, yypt[-5].yyv.lval, &yypt[-2].yyv.gen, yypt[-4].yyv.gen.reg, &yypt[-0].yyv.gen);
	} break;
case 26:
#line	164	"a.y"
{
		outcode(yypt[-5].yyv.lval, yypt[-4].yyv.lval, &yypt[-1].yyv.gen, yypt[-3].yyv.gen.reg, &yypt[-3].yyv.gen);
	} break;
case 27:
#line	168	"a.y"
{
		outcode(yypt[-5].yyv.lval, yypt[-4].yyv.lval, &yypt[-2].yyv.gen, yypt[-0].yyv.gen.reg, &yypt[-0].yyv.gen);
	} break;
case 28:
#line	175	"a.y"
{
		outcode(yypt[-2].yyv.lval, yypt[-1].yyv.lval, &nullgen, NREG, &nullgen);
	} break;
case 29:
#line	182	"a.y"
{
		outcode(yypt[-3].yyv.lval, Always, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 30:
#line	186	"a.y"
{
		outcode(yypt[-5].yyv.lval, Always, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 31:
#line	193	"a.y"
{
		outcode(yypt[-5].yyv.lval, Always, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 32:
#line	200	"a.y"
{
		outcode(yypt[-3].yyv.lval, yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 33:
#line	207	"a.y"
{
		outcode(yypt[-2].yyv.lval, Always, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 34:
#line	214	"a.y"
{
		outcode(yypt[-4].yyv.lval, yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 35:
#line	218	"a.y"
{
		outcode(yypt[-4].yyv.lval, yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 36:
#line	222	"a.y"
{
		outcode(yypt[-6].yyv.lval, yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 37:
#line	226	"a.y"
{
		outcode(yypt[-5].yyv.lval, yypt[-4].yyv.lval, &yypt[-3].yyv.gen, yypt[-1].yyv.gen.reg, &nullgen);
	} break;
case 38:
#line	233	"a.y"
{
		Gen g;

		g = nullgen;
		g.type = D_CONST;
		g.offset =
			(0xe << 24) |		/* opcode */
			(yypt[-11].yyv.lval << 20) |		/* MCR/MRC */
			(yypt[-10].yyv.lval << 28) |		/* scond */
			((yypt[-9].yyv.lval & 15) << 8) |	/* coprocessor number */
			((yypt[-7].yyv.lval & 7) << 21) |	/* coprocessor operation */
			((yypt[-5].yyv.lval & 15) << 12) |	/* arm register */
			((yypt[-3].yyv.lval & 15) << 16) |	/* Crn */
			((yypt[-1].yyv.lval & 15) << 0) |	/* Crm */
			((yypt[-0].yyv.lval & 7) << 5) |	/* coprocessor information */
			(1<<4);			/* must be set */
		outcode(AWORD, Always, &nullgen, NREG, &g);
	} break;
case 39:
#line	255	"a.y"
{
		outcode(yypt[-6].yyv.lval, yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.gen.reg, &yypt[-0].yyv.gen);
	} break;
case 40:
#line	262	"a.y"
{
		yypt[-2].yyv.gen.type = D_REGREG;
		yypt[-2].yyv.gen.offset = yypt[-0].yyv.lval;
		outcode(yypt[-8].yyv.lval, yypt[-7].yyv.lval, &yypt[-6].yyv.gen, yypt[-4].yyv.gen.reg, &yypt[-2].yyv.gen);
	} break;
case 41:
#line	271	"a.y"
{
		outcode(yypt[-1].yyv.lval, Always, &nullgen, NREG, &nullgen);
	} break;
case 42:
#line	276	"a.y"
{
		yyval.lval = Always;
	} break;
case 43:
#line	280	"a.y"
{
		yyval.lval = (yypt[-1].yyv.lval & ~C_SCOND) | yypt[-0].yyv.lval;
	} break;
case 44:
#line	284	"a.y"
{
		yyval.lval = yypt[-1].yyv.lval | yypt[-0].yyv.lval;
	} break;
case 47:
#line	293	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.offset = yypt[-3].yyv.lval + pc;
	} break;
case 48:
#line	299	"a.y"
{
		yyval.gen = nullgen;
		if(pass == 2)
			yyerror("undefined label: %s", yypt[-1].yyv.sym->name);
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yypt[-1].yyv.sym;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 49:
#line	308	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yypt[-1].yyv.sym;
		yyval.gen.offset = yypt[-1].yyv.sym->value + yypt[-0].yyv.lval;
	} break;
case 50:
#line	316	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_CONST;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 51:
#line	322	"a.y"
{
		yyval.gen = yypt[-0].yyv.gen;
		yyval.gen.type = D_CONST;
	} break;
case 52:
#line	327	"a.y"
{
		yyval.gen = yypt[-0].yyv.gen;
		yyval.gen.type = D_OCONST;
	} break;
case 53:
#line	332	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SCONST;
		memcpy(yyval.gen.sval, yypt[-0].yyv.sval, sizeof(yyval.gen.sval));
	} break;
case 55:
#line	341	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = yypt[-0].yyv.dval;
	} break;
case 56:
#line	347	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = -yypt[-0].yyv.dval;
	} break;
case 57:
#line	355	"a.y"
{
		yyval.lval = 1 << yypt[-0].yyv.lval;
	} break;
case 58:
#line	359	"a.y"
{
		int i;
		yyval.lval=0;
		for(i=yypt[-2].yyv.lval; i<=yypt[-0].yyv.lval; i++)
			yyval.lval |= 1<<i;
		for(i=yypt[-0].yyv.lval; i<=yypt[-2].yyv.lval; i++)
			yyval.lval |= 1<<i;
	} break;
case 59:
#line	368	"a.y"
{
		yyval.lval = (1<<yypt[-2].yyv.lval) | yypt[-0].yyv.lval;
	} break;
case 63:
#line	377	"a.y"
{
		yyval.gen = yypt[-3].yyv.gen;
		yyval.gen.reg = yypt[-1].yyv.lval;
	} break;
case 64:
#line	382	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_PSR;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 65:
#line	388	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FPCR;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 66:
#line	394	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 70:
#line	405	"a.y"
{
		yyval.gen = yypt[-0].yyv.gen;
		if(yypt[-0].yyv.gen.name != D_EXTERN && yypt[-0].yyv.gen.name != D_STATIC) {
		}
	} break;
case 71:
#line	413	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
		yyval.gen.offset = 0;
	} break;
case 73:
#line	423	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 75:
#line	433	"a.y"
{
		yyval.gen = yypt[-3].yyv.gen;
		yyval.gen.type = D_OREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
	} break;
case 80:
#line	446	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_CONST;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 81:
#line	454	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_REG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 82:
#line	462	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_REGREG;
		yyval.gen.reg = yypt[-3].yyv.lval;
		yyval.gen.offset = yypt[-1].yyv.lval;
	} break;
case 83:
#line	471	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SHIFT;
		yyval.gen.offset = yypt[-3].yyv.lval | yypt[-0].yyv.lval | (0 << 5);
	} break;
case 84:
#line	477	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SHIFT;
		yyval.gen.offset = yypt[-3].yyv.lval | yypt[-0].yyv.lval | (1 << 5);
	} break;
case 85:
#line	483	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SHIFT;
		yyval.gen.offset = yypt[-3].yyv.lval | yypt[-0].yyv.lval | (2 << 5);
	} break;
case 86:
#line	489	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SHIFT;
		yyval.gen.offset = yypt[-3].yyv.lval | yypt[-0].yyv.lval | (3 << 5);
	} break;
case 87:
#line	497	"a.y"
{
		if(yyval.lval < 0 || yyval.lval >= 16)
			print("register value out of range\n");
		yyval.lval = ((yypt[-0].yyv.lval&15) << 8) | (1 << 4);
	} break;
case 88:
#line	503	"a.y"
{
		if(yyval.lval < 0 || yyval.lval >= 32)
			print("shift value out of range\n");
		yyval.lval = (yypt[-0].yyv.lval&31) << 7;
	} break;
case 90:
#line	512	"a.y"
{
		yyval.lval = REGPC;
	} break;
case 91:
#line	516	"a.y"
{
		if(yypt[-1].yyv.lval < 0 || yypt[-1].yyv.lval >= NREG)
			print("register value out of range\n");
		yyval.lval = yypt[-1].yyv.lval;
	} break;
case 93:
#line	525	"a.y"
{
		yyval.lval = REGSP;
	} break;
case 95:
#line	532	"a.y"
{
		if(yypt[-1].yyv.lval < 0 || yypt[-1].yyv.lval >= NREG)
			print("register value out of range\n");
		yyval.lval = yypt[-1].yyv.lval;
	} break;
case 98:
#line	544	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FREG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 99:
#line	550	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
	} break;
case 100:
#line	558	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.name = yypt[-1].yyv.lval;
		yyval.gen.sym = S;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 101:
#line	566	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.name = yypt[-1].yyv.lval;
		yyval.gen.sym = yypt[-4].yyv.sym;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 102:
#line	574	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.name = D_STATIC;
		yyval.gen.sym = yypt[-6].yyv.sym;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 103:
#line	583	"a.y"
{
		yyval.lval = 0;
	} break;
case 104:
#line	587	"a.y"
{
		yyval.lval = yypt[-0].yyv.lval;
	} break;
case 105:
#line	591	"a.y"
{
		yyval.lval = -yypt[-0].yyv.lval;
	} break;
case 110:
#line	603	"a.y"
{
		yyval.lval = yypt[-0].yyv.sym->value;
	} break;
case 111:
#line	607	"a.y"
{
		yyval.lval = -yypt[-0].yyv.lval;
	} break;
case 112:
#line	611	"a.y"
{
		yyval.lval = yypt[-0].yyv.lval;
	} break;
case 113:
#line	615	"a.y"
{
		yyval.lval = ~yypt[-0].yyv.lval;
	} break;
case 114:
#line	619	"a.y"
{
		yyval.lval = yypt[-1].yyv.lval;
	} break;
case 115:
#line	624	"a.y"
{
		yyval.lval = 0;
	} break;
case 116:
#line	628	"a.y"
{
		yyval.lval = yypt[-0].yyv.lval;
	} break;
case 118:
#line	635	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval + yypt[-0].yyv.lval;
	} break;
case 119:
#line	639	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval - yypt[-0].yyv.lval;
	} break;
case 120:
#line	643	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval * yypt[-0].yyv.lval;
	} break;
case 121:
#line	647	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval / yypt[-0].yyv.lval;
	} break;
case 122:
#line	651	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval % yypt[-0].yyv.lval;
	} break;
case 123:
#line	655	"a.y"
{
		yyval.lval = yypt[-3].yyv.lval << yypt[-0].yyv.lval;
	} break;
case 124:
#line	659	"a.y"
{
		yyval.lval = yypt[-3].yyv.lval >> yypt[-0].yyv.lval;
	} break;
case 125:
#line	663	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval & yypt[-0].yyv.lval;
	} break;
case 126:
#line	667	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval ^ yypt[-0].yyv.lval;
	} break;
case 127:
#line	671	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval | yypt[-0].yyv.lval;
	} break;
	}
	goto yystack;  /* stack new state and value */
}
