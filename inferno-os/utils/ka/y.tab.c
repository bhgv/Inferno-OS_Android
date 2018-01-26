
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
#define YYEOFCODE 1
#define YYERRCODE 2
short	yyexca[] =
{-1, 1,
	1, -1,
	-2, 0,
};
#define	YYNPROD	139
#define	YYPRIVATE 57344
#define	yydebug	1
#define	YYLAST	741
short	yyact[] =
{
  50,  46,  45,  44,  79,  91,  39, 137,  43,  88,
 225, 222,  77, 326,  72,  70,  77, 329,  67,  74,
 312,  93,  83,  85, 311,  41,  90, 310,  96, 103,
 111, 111, 303, 104, 106, 118, 118,  71,  76, 294,
 293,  84,  86, 292,   2,  64,  63,  97, 100, 118,
 129, 291, 133, 290, 313, 232,  42,  58, 263,  59,
 130, 221, 307, 220, 141, 142, 143,  58,  68,  59,
  80,  61,  64,  63,  88,  38, 190,  77, 154,  52,
 101, 102,  53, 174, 107, 117, 119,  77, 166,  60,
  93,  62, 136, 165,  47, 168,  48, 135,  61,  65,
 134, 306, 175, 176, 305,  58, 304,  59, 300, 299,
 298, 297,  57, 118, 265, 187,  60, 189,  62,  88,
 184, 183, 208,  48, 214, 211,  65, 206, 209, 213,
 210, 182, 181, 218, 219, 229, 230, 231, 179, 177,
 234, 235, 171, 128, 164,  58,  52,  59, 238,  53,
 163, 236, 162, 161, 160, 157, 243, 244, 245, 247,
 192, 193, 108, 156, 155, 188, 153, 254, 256, 258,
 260, 262, 152, 151, 150, 264, 149, 148, 266, 147,
 146, 145, 144, 127, 170, 126, 125, 272, 124, 123,
 276, 273, 277, 122, 121, 120, 118, 118, 118, 118,
 118, 237,  37, 118, 118, 118,  36,  33,  34,  35,
 274,  32, 249, 250, 251, 275,  58, 253,  59, 159,
 267, 131, 288,  57,  55, 224,  58,  52,  59,  56,
  53, 284,  40,  66,  75,  78,  82,  52, 270, 271,
  53, 296,  92, 295,  64,  63, 278, 279, 280, 281,
 282, 327, 191, 285, 286, 287, 255, 257, 259, 261,
 158,  58,  52,  59, 233,  53,  93, 283,  55, 224,
  61, 301, 268,  56, 269,  55,   8,  58,  52,  59,
  56,  53, 116,  73, 118, 118, 115,  55,  60,  58,
  62,  59,  56,   1,  54,  48,  87,  51,  65, 139,
 140, 317, 319,  69, 314, 315, 316, 318,  49, 321,
 324, 169, 325,   0,  58,  89,  59, 289,  98,  99,
 227, 226, 228,   0, 105, 109,   0, 133, 114, 141,
  64,  63, 322, 323, 308, 309,  64,  63, 110, 113,
   0,   0, 207,   0, 212, 215, 216, 217,   0, 227,
 226, 228, 267,   0,   0,  58,  61,  59, 227, 226,
 228, 320,  61,  58,  58,  59,  59, 239, 240, 241,
 242,   0,   0, 246,  60, 248,  62,   0, 253, 252,
   0,  48,  62,  77,  65,   0,   0, 112, 172, 173,
  65,   0,   0, 178,   9,   0,   0, 180, 195, 196,
 197, 198, 199, 185, 186,   0,  10,  11,  12,  14,
  15,  26,  17,  13,  23,  24,  25,  21,  18,  16,
  27,  28,  19,  22,  29,  30,  31,  64,  63,   0,
 197, 198, 199,  20, 202, 200, 201, 195, 196, 197,
 198, 199,   6,   0,   0,   4,   3,   5,   0,   0,
   7,  64,  63,  61, 138,   0, 139, 140,  55,   0,
  58,  52,  59,  56,  53,  54,   0,  57,   0,   0,
   0,  60,   0,  62,  64,  63,   0,  61,  48,   0,
  51,  65,   0,   0,  58,   0,  59, 302,  64, 328,
   0,   0,   0,   0,   0,  94,  95,  62,   0,   0,
  61,   0,  48,  64,  63,  65,   0,   0,  52,   0,
   0,  53,   0,   0,  61,   0,   0,   0,  60,   0,
  62,   0,   0,   0,   0,  48,   0,  81,  65,  61,
 158, 132,  60,   0,  62,   0,  58,   0,  59,  48,
   0,   0,  65,  64,  63,   0,   0,  60,   0,  62,
   0,   0,   0,   0,  48,  64,  63,  65, 204, 203,
 202, 200, 201, 195, 196, 197, 198, 199,   0,  61,
  64,  63,  64,  63,   0,   0,  64,  63,   0,   0,
   0,  61,   0,   0,   0,   0,   0,  94,  95,  62,
   0,  64,  63,   0,  48,   0,  61,  65,  61, 167,
  95,  62,  61,   0,   0,  58, 112,  59,   0,  65,
  64,  63,   0, 132,  60, 223,  62,  61,  62,   0,
   0,  48,  62, 112,  65,   0,  65, 112,   0,  77,
  65,  64,  63,   0,   0,  60,  61,  62,   0,   0,
   0,   0,  48,   0,   0,  65, 200, 201, 195, 196,
 197, 198, 199,   0,  60,   0,  62,  61,   0,   0,
   0, 112,   0,   0,  65, 204, 203, 202, 200, 201,
 195, 196, 197, 198, 199,   0,   0,  62,   0,   0,
   0,   0, 112,   0,   0,  65, 204, 203, 202, 200,
 201, 195, 196, 197, 198, 199, 203, 202, 200, 201,
 195, 196, 197, 198, 199,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0, 205,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
 194
};
short	yypact[] =
{
-1000, 392,-1000, 155, 151, 152, 148,-1000, 144,  17,
 418, 235, 321, 465, 582,  25,  25,  60,  60, 272,
 534,  15, -50, 194, 194, 228, 272, 103,  60, 601,
 601,  60,-1000,-1000, 622, 622,-1000,-1000,-1000, 136,
 135, 134, 130, 129, 127, 126, 124,-1000, 563,-1000,
   0, 561,-1000,  40,-1000,-1000,  37,-1000,-1000,  32,
 447,-1000,-1000, 622, 622, 622, 123, 122, 121, 120,
 118, 117, 115,-1000, 114, 113, 107, 622, 105, 104,
  96, 209,  95,  94,  93,  91,  85, 546,-1000, 442,
  83,  60,  60,  23, 447, 290,  80,  79,-1000,-1000,
  60,  73,  72,  62,  61,-1000,  60,  60, 219,-1000,
  58,  16, 622, 240,-1000, 392, 392, 682,-1000, 661,
  63, 247,  63, 582, 582, 582, 272, 272,   2, 554,
 322,-1000,-1000,   0, 622, 622, 622,  -5, 256, 622,
 622,-1000,-1000,-1000, 184, 582, 582, 582, 582, 272,
 272, 494, 272, 582,-1000, 194, 194,  36,-1000, 166,
 272, 272, 272, 272, 272,-1000,  -2, 290,-1000,-1000,
  55, 272,-1000,-1000, 313,  -5,-1000, 272,-1000, 272,
-1000, 194, 194, 228,  25,-1000,-1000,-1000,-1000, 567,
 284, 622,-1000,-1000,-1000, 622, 622, 622, 622, 622,
 260, 223, 622, 622, 622,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000, 622, 272,-1000,  -8, -10,-1000,-1000,-1000, -18,
 -21, -22, 284, 290,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,  52,-1000,  51,-1000,  50,
-1000,  49,-1000, 181,-1000, 534,-1000, -29,-1000,-1000,
-1000,  47,  45,-1000,-1000,-1000,  42,   3, 419, 419,
-1000,-1000,-1000, 622, 622, 639, 428, 691, -34, -37,
-1000,-1000,-1000,-1000,-1000, -41,  -6, 272, 272, 174,
 174,-1000,-1000,-1000, 194, 228, -46, -49, 389, 389,
-1000,-1000,-1000, 214,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000, 479, -44, 327,-1000
};
short	yypgo[] =
{
   0,   0,  50,  10,   7,  94, 221,   6, 308,   1,
   3,  56,  25,   2,   4,   5,   8, 303, 293,  44,
 286, 282, 276, 296
};
short	yyr1[] =
{
   0,  18,  18,  20,  19,  21,  19,  19,  19,  19,
  19,  19,  19,  22,  22,  22,  22,  22,  22,  22,
  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,
  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,
  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,
  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,
  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,
  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,
  22,  22,  22,  22,  22,  22,  22,  22,  15,  15,
  15,   7,  16,  17,   9,  10,  10,  11,  11,  13,
  13,  14,  14,  12,   5,   5,   6,   6,   6,   6,
   6,   8,   8,   8,  23,  23,   4,   4,   4,   3,
   3,   3,   1,   1,   1,   1,   1,   1,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,   2
};
short	yyr2[] =
{
   0,   0,   2,   0,   4,   0,   4,   4,   4,   2,
   1,   2,   2,   4,   4,   4,   4,   4,   4,   4,
   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
   4,   4,   4,   4,   4,   4,   4,   4,   6,   6,
   4,   4,   6,   6,   4,   4,   4,   4,   4,   4,
   3,   3,   3,   5,   5,   4,   3,   3,   4,   4,
   3,   2,   4,   4,   4,   6,   6,   2,   3,   4,
   4,   6,   4,   6,   4,   4,   2,   3,   3,   3,
   3,   2,   4,   6,   6,   6,   6,   2,   4,   2,
   2,   1,   1,   1,   1,   1,   4,   1,   4,   2,
   2,   2,   3,   2,   1,   4,   3,   5,   5,   1,
   4,   4,   5,   7,   0,   1,   0,   2,   2,   1,
   1,   1,   1,   1,   2,   2,   2,   3,   1,   3,
   3,   3,   3,   3,   4,   4,   3,   3,   3
};
short	yychk[] =
{
-1000, -18, -19,  54,  53,  55,  50,  58, -22,   2,
  14,  15,  16,  21,  17,  18,  27,  20,  26,  30,
  41,  25,  31,  22,  23,  24,  19,  28,  29,  32,
  33,  34,  56,  56,  57,  57,  58,  58,  58,  -7,
  -6, -12, -11, -16, -10, -13,  -9,  -5,  60,  -8,
  -1,  62,  43,  46,  47,  40,  45,  49,  42,  44,
  53,  35,  55,  10,   9,  63,  -6,  -7, -11, -17,
 -10, -12, -13,  48,  -7,  -6, -12,  62,  -6, -14,
 -11,  62,  -6,  -7, -12,  -7, -12, -23,  59, -23,
  -7, -15,  -6,  -1,  53,  54,  -7, -12, -23, -23,
 -12, -11, -11, -10,  -7, -23,  -7, -11,  59, -23,
  -8,  -1,  60,  -8, -23, -20, -21,  -2,  -1,  -2,
  59,  59,  59,  59,  59,  59,  59,  59,  -5,  -2,
  60,  -6,  52,  -1,  60,  60,  60,  -4,   7,   9,
  10,  -1,  -1,  -1,  59,  59,  59,  59,  59,  59,
  59,  59,  59,  59,  -1,  59,  59,  59,  51,  10,
  59,  59,  59,  59,  59, -15,  -1,  53, -15,  -6,
  -5,  59, -23, -23,  60,  -4,  -4,  59, -23,  59,
 -23,  59,  59,  59,  59, -23, -23,  -7, -11,  59,
  60,  12, -19, -19,  58,   9,  10,  11,  12,  13,
   7,   8,   6,   5,   4,  58,  -7,  -6,  -9,  -7,
 -16, -10,  -6,  -7,  -9,  -6,  -6,  -6,  -7,  -7,
  61,  59,   9,  61,  -5,  -3,  37,  36,  38,  -1,
  -1,  -1,  60,   8,  -1,  -1,  -7, -11, -10,  -6,
  -6,  -6,  -6,  -7,  -7,  -7,  -6,  -7,  -6, -11,
 -11, -11,  -6,  51,  -7,  -5,  -7,  -5,  -7,  -5,
  -7,  -5,  -7,  60,  -4,  59,  -7,  39,  -5,  -5,
 -11, -11, -10,  -7, -12, -12,  -1,  -1,  -2,  -2,
  -2,  -2,  -2,   7,   8,  -2,  -2,  -2,  -1,  -5,
  61,  61,  61,  61,  61,  -3,  -4,  59,  59,  59,
  59, -15,  -6,  61,  59,  59,  59,  59,  -2,  -2,
  61,  61,  61,  60,  -7,  -7,  -7,  -9,  -7,  -9,
 -11, -10, -12, -12, -13, -14,  62,  37,  10,  61
};
short	yydef[] =
{
   1,  -2,   2,   0,   0,   0,   0,  10,   0,   0,
   0,   0,   0,   0,   0,   0,   0, 114, 114,   0,
   0, 114, 114,   0,   0,   0,   0, 114, 114,   0,
   0, 114,   3,   5,   0,   0,   9,  11,  12,   0,
   0,   0,   0,   0,   0,   0,   0,  91,   0, 109,
   0,   0,  97,   0,  92,  95,   0,  94, 104,   0,
 116, 122, 123,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,  93,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0, 115,   0,
   0, 114, 114,   0, 116, 116, 114,   0,  61,  67,
 114,   0,   0,   0,   0,  76, 114, 114, 115,  81,
   0,   0,   0,   0,  87,   0,   0,   0, 128,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,  99, 100, 103,   0,   0,   0,   0,   0,   0,
   0, 124, 125, 126,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0, 103,   0,   0,   0, 101,   0,
   0,   0,   0,   0,   0,  50,   0, 116,  51,  52,
   0,   0,  56,  57,   0,  89,  90, 115,  60,   0,
  68,   0,   0,   0,   0,  77,  78,  79,  80,   0,
   0,   0,   4,   6,   7,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   8,  13,  26,  63,  14,
  23,  24,  27,  46,  64,  31,  33,  35,  48,  62,
 106,   0,   0, 127,   0,   0, 119, 120, 121,   0,
   0,   0,   0, 116, 117, 118,  15,  18,  25,  28,
  32,  34,  36,  47,  49,  16,  29,  17,  30,  19,
  20,  21,  22, 102,  37,  91,  40,  91,  41,  91,
  44,  91,  45,   0,  89,   0,  55,   0,  58,  59,
  69,  70,  72,  74,  75,  82,   0,   0, 129, 130,
 131, 132, 133,   0,   0, 136, 137, 138,   0,   0,
 110, 111,  98,  96, 105,   0,   0,   0,   0,   0,
   0,  53,  54,  88,   0,   0,   0,   0, 134, 135,
 107, 108, 112,   0,  38,  39,  42,  65,  43,  66,
  71,  73,  83,  84,  85,  86,   0,   0,   0, 113
};
short	yytok1[] =
{
   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,  62,  13,   6,   0,
  60,  61,  11,   9,  59,  10,   0,  12,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  56,  58,
   7,  57,   8,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   5,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   4,   0,  63
};
short	yytok2[] =
{
   2,   3,  14,  15,  16,  17,  18,  19,  20,  21,
  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,
  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,
  52,  53,  54,  55
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
#line	36	"a.y"
{
		if(yypt[-1].yyv.sym->value != pc)
			yyerror("redeclaration of %s", yypt[-1].yyv.sym->name);
		yypt[-1].yyv.sym->value = pc;
	} break;
case 5:
#line	43	"a.y"
{
		yypt[-1].yyv.sym->type = LLAB;
		yypt[-1].yyv.sym->value = pc;
	} break;
case 7:
#line	49	"a.y"
{
		yypt[-3].yyv.sym->type = LVAR;
		yypt[-3].yyv.sym->value = yypt[-1].yyv.lval;
	} break;
case 8:
#line	54	"a.y"
{
		if(yypt[-3].yyv.sym->value != yypt[-1].yyv.lval)
			yyerror("redeclaration of %s", yypt[-3].yyv.sym->name);
		yypt[-3].yyv.sym->value = yypt[-1].yyv.lval;
	} break;
case 9:
#line	60	"a.y"
{
		nosched = yypt[-1].yyv.lval;
	} break;
case 13:
#line	72	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 14:
#line	76	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 15:
#line	80	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 16:
#line	84	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 17:
#line	88	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 18:
#line	96	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 19:
#line	100	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 20:
#line	104	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 21:
#line	108	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 22:
#line	112	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 23:
#line	116	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 24:
#line	124	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 25:
#line	128	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 26:
#line	135	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 27:
#line	139	"a.y"
{
		if(yypt[-2].yyv.gen.offset != 0)
			yyerror("constant must be zero");
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 28:
#line	145	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 29:
#line	149	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 30:
#line	153	"a.y"
{
		if(yypt[-2].yyv.gen.offset != 0)
			yyerror("constant must be zero");
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 31:
#line	163	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 32:
#line	167	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 33:
#line	171	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 34:
#line	175	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 35:
#line	183	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 36:
#line	187	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 37:
#line	195	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 38:
#line	209	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 39:
#line	213	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 40:
#line	217	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 41:
#line	221	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 42:
#line	225	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 43:
#line	229	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 44:
#line	233	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 45:
#line	237	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 46:
#line	245	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 47:
#line	249	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 48:
#line	253	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 49:
#line	257	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 50:
#line	266	"a.y"
{
		outcode(yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 51:
#line	274	"a.y"
{
		outcode(yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 52:
#line	278	"a.y"
{
		outcode(yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 53:
#line	282	"a.y"
{
		outcode(yypt[-4].yyv.lval, &nullgen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 54:
#line	286	"a.y"
{
		outcode(yypt[-4].yyv.lval, &nullgen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 55:
#line	293	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 56:
#line	300	"a.y"
{
		outcode(yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 57:
#line	304	"a.y"
{
		outcode(yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 58:
#line	311	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, yypt[-0].yyv.lval, &nullgen);
	} break;
case 59:
#line	315	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, yypt[-0].yyv.lval, &nullgen);
	} break;
case 60:
#line	319	"a.y"
{
		outcode(yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 61:
#line	323	"a.y"
{
		outcode(yypt[-1].yyv.lval, &nullgen, NREG, &nullgen);
	} break;
case 62:
#line	330	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 63:
#line	337	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 64:
#line	341	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 65:
#line	345	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 66:
#line	349	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 67:
#line	356	"a.y"
{
		outcode(yypt[-1].yyv.lval, &nullgen, NREG, &nullgen);
	} break;
case 68:
#line	360	"a.y"
{
		outcode(yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 69:
#line	367	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 70:
#line	371	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 71:
#line	375	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.gen.reg, &yypt[-0].yyv.gen);
	} break;
case 72:
#line	382	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 73:
#line	386	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.gen.reg, &yypt[-0].yyv.gen);
	} break;
case 74:
#line	393	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 75:
#line	397	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 76:
#line	404	"a.y"
{
		outcode(yypt[-1].yyv.lval, &nullgen, NREG, &nullgen);
	} break;
case 77:
#line	408	"a.y"
{
		outcode(yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 78:
#line	412	"a.y"
{
		outcode(yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 79:
#line	416	"a.y"
{
		outcode(yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 80:
#line	420	"a.y"
{
		outcode(yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 81:
#line	427	"a.y"
{
		outcode(yypt[-1].yyv.lval, &nullgen, NREG, &nullgen);
	} break;
case 82:
#line	434	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 83:
#line	438	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 84:
#line	445	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 85:
#line	449	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 86:
#line	453	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 87:
#line	460	"a.y"
{
		outcode(yypt[-1].yyv.lval, &nullgen, NREG, &nullgen);
	} break;
case 88:
#line	466	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.offset = yypt[-3].yyv.lval + pc;
	} break;
case 89:
#line	472	"a.y"
{
		yyval.gen = nullgen;
		if(pass == 2)
			yyerror("undefined label: %s", yypt[-1].yyv.sym->name);
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yypt[-1].yyv.sym;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 90:
#line	481	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yypt[-1].yyv.sym;
		yyval.gen.offset = yypt[-1].yyv.sym->value + yypt[-0].yyv.lval;
	} break;
case 91:
#line	490	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_REG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 92:
#line	498	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_PREG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 93:
#line	506	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_PREG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 94:
#line	514	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_PREG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 95:
#line	522	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_CREG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 96:
#line	528	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_CREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
	} break;
case 97:
#line	536	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FREG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 98:
#line	542	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
	} break;
case 99:
#line	550	"a.y"
{
		yyval.gen = yypt[-0].yyv.gen;
		yyval.gen.type = D_CONST;
	} break;
case 100:
#line	555	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SCONST;
		memcpy(yyval.gen.sval, yypt[-0].yyv.sval, sizeof(yyval.gen.sval));
	} break;
case 101:
#line	563	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = yypt[-0].yyv.dval;
	} break;
case 102:
#line	569	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = -yypt[-0].yyv.dval;
	} break;
case 103:
#line	576	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_CONST;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 105:
#line	585	"a.y"
{
		if(yyval.lval < 0 || yyval.lval >= NREG)
			print("register value out of range\n");
		yyval.lval = yypt[-1].yyv.lval;
	} break;
case 106:
#line	593	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
		yyval.gen.offset = 0;
	} break;
case 107:
#line	600	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_ASI;
		yyval.gen.reg = yypt[-3].yyv.lval;
		yyval.gen.offset = yypt[-1].yyv.lval;
	} break;
case 108:
#line	607	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.reg = yypt[-3].yyv.lval;
		yyval.gen.xreg = yypt[-1].yyv.lval;
		yyval.gen.offset = 0;
	} break;
case 110:
#line	616	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 111:
#line	625	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.name = yypt[-1].yyv.lval;
		yyval.gen.sym = S;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 112:
#line	633	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.name = yypt[-1].yyv.lval;
		yyval.gen.sym = yypt[-4].yyv.sym;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 113:
#line	641	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.name = D_STATIC;
		yyval.gen.sym = yypt[-6].yyv.sym;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 116:
#line	653	"a.y"
{
		yyval.lval = 0;
	} break;
case 117:
#line	657	"a.y"
{
		yyval.lval = yypt[-0].yyv.lval;
	} break;
case 118:
#line	661	"a.y"
{
		yyval.lval = -yypt[-0].yyv.lval;
	} break;
case 123:
#line	673	"a.y"
{
		yyval.lval = yypt[-0].yyv.sym->value;
	} break;
case 124:
#line	677	"a.y"
{
		yyval.lval = -yypt[-0].yyv.lval;
	} break;
case 125:
#line	681	"a.y"
{
		yyval.lval = yypt[-0].yyv.lval;
	} break;
case 126:
#line	685	"a.y"
{
		yyval.lval = ~yypt[-0].yyv.lval;
	} break;
case 127:
#line	689	"a.y"
{
		yyval.lval = yypt[-1].yyv.lval;
	} break;
case 129:
#line	696	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval + yypt[-0].yyv.lval;
	} break;
case 130:
#line	700	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval - yypt[-0].yyv.lval;
	} break;
case 131:
#line	704	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval * yypt[-0].yyv.lval;
	} break;
case 132:
#line	708	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval / yypt[-0].yyv.lval;
	} break;
case 133:
#line	712	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval % yypt[-0].yyv.lval;
	} break;
case 134:
#line	716	"a.y"
{
		yyval.lval = yypt[-3].yyv.lval << yypt[-0].yyv.lval;
	} break;
case 135:
#line	720	"a.y"
{
		yyval.lval = yypt[-3].yyv.lval >> yypt[-0].yyv.lval;
	} break;
case 136:
#line	724	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval & yypt[-0].yyv.lval;
	} break;
case 137:
#line	728	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval ^ yypt[-0].yyv.lval;
	} break;
case 138:
#line	732	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval | yypt[-0].yyv.lval;
	} break;
	}
	goto yystack;  /* stack new state and value */
}
