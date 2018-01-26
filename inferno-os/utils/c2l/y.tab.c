
#line	2	"cc.y"
#include "cc.h"

#line	4	"cc.y"
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
} YYSTYPE;
extern	int	yyerrflag;
#ifndef	YYMAXDEPTH
#define	YYMAXDEPTH	150
#endif
YYSTYPE	yylval;
YYSTYPE	yyval;
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
#define YYEOFCODE 1
#define YYERRCODE 2

#line	1239	"cc.y"

short	yyexca[] =
{-1, 1,
	1, -1,
	-2, 181,
-1, 36,
	4, 8,
	5, 8,
	6, 9,
	-2, 5,
-1, 48,
	95, 194,
	-2, 193,
-1, 50,
	95, 199,
	-2, 198,
-1, 52,
	95, 204,
	-2, 203,
-1, 71,
	6, 9,
	-2, 8,
-1, 305,
	4, 96,
	95, 82,
	-2, 0,
-1, 324,
	6, 22,
	-2, 21,
-1, 329,
	95, 82,
	-2, 96,
-1, 335,
	4, 96,
	95, 82,
	-2, 0,
-1, 388,
	4, 96,
	95, 82,
	-2, 0,
-1, 390,
	4, 96,
	95, 82,
	-2, 0,
-1, 392,
	4, 96,
	95, 82,
	-2, 0,
-1, 402,
	4, 96,
	95, 82,
	-2, 0,
-1, 408,
	4, 96,
	95, 82,
	-2, 0,
};
#define	YYNPROD	246
#define	YYPRIVATE 57344
#define	YYLAST	1250
short	yyact[] =
{
 172, 326, 253, 330, 206, 323, 200,  82, 204, 328,
  39, 343, 297, 344, 296,  15, 254, 202,  80,  84,
   5,   4,  14, 130,  74, 195, 207, 121, 194, 111,
  77,  41,  85, 374, 198,   6, 198, 132,  81, 274,
  48,  50,  52,  46, 133,  75, 299,  98, 262, 201,
  36, 137, 135,  42,  43,  44, 120,  65, 310, 308,
  83, 285, 139, 408,  60, 394,  42,  43,  44, 110,
 393, 316, 249, 315, 126, 309, 115, 290, 125, 137,
 250, 287, 284, 128, 116, 380, 402,  61, 113, 112,
 251,   5, 368, 122, 124, 251, 251, 249, 251, 251,
 171, 251,  71, 214, 137, 250,  76, 114, 179, 180,
 181, 182, 183, 184, 185, 186, 391, 170,  53,  42,
  43,  44, 213, 212, 131, 303, 133, 197, 126, 187,
 189, 214, 373, 137, 135,  42,  43,  44,  83, 192,
  35, 218, 219, 220, 221, 222, 223, 224, 225, 226,
 227, 228, 229, 230, 231, 232, 233, 234, 235, 211,
 237, 238, 239, 240, 241, 242, 243, 244, 245, 246,
 247, 203, 236, 215, 255, 210, 216,  76, 191, 292,
  27,  28,  61, 404, 392, 249, 390, 388, 256, 252,
  64,   7, 137, 250, 248, 370,  70, 369,  45, 365,
 270, 362, 171, 361, 171, 360, 126, 257, 258,  83,
 275, 115,  59,  58,  83,  13, 279, 217, 267, 259,
 138, 260, 261,  47, 268,  38, 269, 115,  11,  12,
 251, 265, 276,  40,  42,  43,  44, 282,  62,  27,
  28, 280,  67, 286,  17, 140, 141, 142,  24, 281,
 372,  23, 283, 320, 117,  19,  20, 119, 114,  18,
  76,  47, 376,   8, 278, 289,   9,  22, 199,  25,
  10,  21,  27,  28, 300, 288,  26,  73,  47,  27,
  28, 352, 353, 293, 294, 251,  38, 311, 215, 302,
   5, 306, 255, 304,  40,  42,  43,  44, 272, 273,
  54,  55,  83, 319, 115, 407, 300, 312, 314, 321,
 317, 307, 291, 277, 126, 129, 403, 322, 301, 401,
 203,  83, 348,  69, 400, 389, 281, 383, 351, 381,
 300, 367, 350, 366,  38, 358, 355, 363, 359, 357,
 364, 356,  40,  42,  43,  44, 371,  38,  34, 349,
 318, 324, 196, 133,  68,  40,  42,  43,  44, 375,
 137, 135,  42,  43,  44, 378,  51,  66,  49,  63,
 255, 255, 384, 385, 377, 118, 379, 126,  38, 382,
 331, 387, 295, 263, 193, 354,  40,  42,  43,  44,
 395,  57, 397, 396, 399, 143, 144, 140, 141, 142,
 324, 123,  89,  72, 405, 398,  56, 406,   3,   2,
 409,  90,  91,  88,   1, 136,  95,  94, 134, 205,
 298,  86,  79,  11,  12, 105, 104,  99, 100, 101,
 102, 103, 106, 107, 112, 113,  29, 329,  37,  17,
 109, 108, 305,  24, 271,  31,  23,  87, 327, 264,
  19,  20,  33, 266,  18,  96,  16,  30,   8,   0,
  32,   9,  22,   0,  25,  10,  21,  27,  28,  89,
  97,  26,   0,   0,   0,   0,  92,  93,  90,  91,
  88,   0,   0,  95,  94,   0,   0,   0,  86, 347,
   0,   0, 105, 104,  99, 100, 101, 102, 103, 106,
 107, 112, 113,   0, 338, 345,   0, 339, 346, 335,
   0,   0,   0,   0, 333, 340, 332, 327,   0,   0,
 336,   0,  96, 341,   0,   0, 337,   0,   0,   0,
 334,   0,   0,   0,   0,   0, 342,  97,  89,   0,
   0,   0, 325,  92,  93,   0,   0,  90,  91,  88,
   0,   0,  95,  94,   0,   0,   0,  86, 347,   0,
   0, 105, 104,  99, 100, 101, 102, 103, 106, 107,
 112, 113,   0, 338, 345,   0, 339, 346, 335,   0,
   0,   0,   0, 333, 340, 332,   0,   0,   0, 336,
   0,  96, 341,   0,   0, 337,   0,   0,   0, 334,
  89,   0,   0,   0,   0, 342,  97,   0,   0,  90,
  91,  88,  92,  93,  95,  94,   0,   0,   0,  86,
 347,   0,   0, 105, 104,  99, 100, 101, 102, 103,
 106, 107, 112, 113,   0, 338, 345,   0, 339, 346,
 335,   0,   0,   0,   0, 333, 340, 332,   0,   0,
   0, 336,   0,  96, 341,   0,   0, 337,   0,   0,
   0, 334,  89,   0,   0,   0,   0, 342,  97,   0,
   0,  90,  91,  88,  92,  93,  95,  94,   0, 209,
 208,  86,  79,   0,   0, 105, 104,  99, 100, 101,
 102, 103, 106, 107, 112, 113,  17,   0,   0,   0,
  24,   0,   0,  23,   0,   0,   0,  19,  20,   0,
   0,  18,   0,   0,   0,  96,   0,   0,   0,  22,
   0,  25,   0,  21,   0,   0,   0,   0,  26,  89,
  97,   0,   0,   0, 127,   0,  92,  93,  90,  91,
  88,   0,   0,  95,  94,   0,   0,   0,  86,  79,
   0,   0, 105, 104,  99, 100, 101, 102, 103, 106,
 107, 112, 113, 156, 155, 154, 153, 151, 152, 147,
 148, 149, 150, 146, 145, 143, 144, 140, 141, 142,
   0,   0,  96, 151, 152, 147, 148, 149, 150, 146,
 145, 143, 144, 140, 141, 142,  89,  97,   0,   0,
   0, 127,   0,  92,  93,  90,  91,  88,   0,   0,
  95,  94,   0,   0,   0,  86,  79,   0,   0, 105,
 104,  99, 100, 101, 102, 103, 106, 107, 112, 113,
 155, 154, 153, 151, 152, 147, 148, 149, 150, 146,
 145, 143, 144, 140, 141, 142,   0,   0,   0,  96,
 178, 177, 175, 176, 174, 173, 146, 145, 143, 144,
 140, 141, 142,  89,  97,   0,   0,   0, 313,   0,
  92,  93,  90,  91,  88,   0,   0,  95,  94,   0,
   0,   0,  86,  79,   0,   0, 105, 104,  99, 100,
 101, 102, 103, 106, 107, 112, 113, 154, 153, 151,
 152, 147, 148, 149, 150, 146, 145, 143, 144, 140,
 141, 142,   0,   0,   0,   0,  96,   0,   0,   0,
   0,   0,   0,   0,   0,  89,   0,   0,   0,   0,
   0,  97,   0,   0,  90,  91,  88,  92,  93,  95,
  94,   0,   0,   0, 190,  79,   0,   0, 105, 104,
  99, 100, 101, 102, 103, 106, 107, 112, 113, 153,
 151, 152, 147, 148, 149, 150, 146, 145, 143, 144,
 140, 141, 142,   0,   0,   0,   0,   0,  96,   0,
   0,   0,   0,   0,   0,   0,   0,  89,   0,   0,
   0,   0,   0,  97,   0,   0,  90,  91,  88,  92,
  93,  95,  94,   0,   0,   0, 188,  79,   0,   0,
 105, 104,  99, 100, 101, 102, 103, 106, 107, 112,
 113,   0,   0,   0,   0,  78,   0,   0,  79,  11,
  12,   0,   0,   0,   0,   0,   0,   0,   0,   0,
  96,   0,  29,   0,   0,  17,   0,   0,   0,  24,
   0,  31,  23,   0,   0,  97,  19,  20,  33,   0,
  18,  92,  93,  30,   8,   0,  32,   9,  22,   0,
  25,  10,  21,  27,  28,  11,  12,  26,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  29,   0,
   0,  17,   0,   0,   0,  24,   0,  31,  23,   0,
   0,   0,  19,  20,  33,   0,  18,   0,   0,  30,
   8,   0,  32,   9,  22,   0,  25,  10,  21,  27,
  28,  29,   0,  26,  17,   0,   0,   0,  24,   0,
  31,  23,   0,   0,   0,  19,  20,  33,   0,  18,
   0,   0,  30,   0,   0,  32,   0,  22,   0,  25,
   0,  21,  27,  28,   0,   0,  26, 159, 160, 161,
 162, 163, 164, 166, 165, 167, 168, 169, 158, 386,
 157, 156, 155, 154, 153, 151, 152, 147, 148, 149,
 150, 146, 145, 143, 144, 140, 141, 142, 159, 160,
 161, 162, 163, 164, 166, 165, 167, 168, 169, 158,
   0, 157, 156, 155, 154, 153, 151, 152, 147, 148,
 149, 150, 146, 145, 143, 144, 140, 141, 142, 158,
   0, 157, 156, 155, 154, 153, 151, 152, 147, 148,
 149, 150, 146, 145, 143, 144, 140, 141, 142, 147,
 148, 149, 150, 146, 145, 143, 144, 140, 141, 142
};
short	yypact[] =
{
-1000,1031,-1000, 344,-1000,-1000,1064,1031,  76,  76,
  23,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000, 296,-1000, 171,-1000,-1000,
 252,-1000,-1000,-1000,-1000,1064,1064,-1000,-1000, -38,
-1000, -38,-1000,-1000,-1000, 252,-1000, 271, 985, 840,
 191,  -9,1064, -38,-1000,-1000, -38,-1000, -39,  50,
-1000,-1000,1031, 706, -10, 310,-1000, 319, 180,-1000,
-1000, -32,-1000,1182,-1000,-1000, 379, 813, 840, 840,
 840, 840, 840, 840, 840, 840, 964, 902,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,  34,  32,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,  31, 262, -46, 252,-1000,1182, 639,-1000, 985,
-1000,-1000,-1000,-1000,  81,  10,-1000, 840, 177,-1000,
 840, 840, 840, 840, 840, 840, 840, 840, 840, 840,
 840, 840, 840, 840, 840, 840, 840, 840, 840, 840,
 840, 840, 840, 840, 840, 840, 840, 840, 840, 840,
  63,  96,1182, 840, 840,  76,  76,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000, 379,-1000,
 379,-1000,-1000, -48,-1000, 184,  50,-1000,  50, 840,
-1000,-1000, 294,-1000, -57, 639, 308, 258, 840,  76,
-1000,  92, 985, 840,-1000, -11, -33,-1000,-1000,-1000,
-1000, 211, 211, 363, 363, 826, 826, 826, 826,1213,
1213, 759, 936, 875, 809, 743, 225,1182,1182,1182,
1182,1182,1182,1182,1182,1182,1182,1182, -12,-1000,
  38, 840,-1000, -16, 307,1182,  85,-1000,-1000,  63,
  63,-1000,-1000, 300,-1000,-1000, 636,-1000,  29,-1000,
1182,1031,-1000, 252,-1000, 306, 258,-1000,-1000, -35,
-1000,-1000, -18, -36,-1000,-1000, 840, 773, 151,-1000,
-1000, 840,-1000, -20, -22, 300, 346, 298,-1000,-1000,
 235, 840,-1000,-1000, 313, 446,-1000,-1000,-1000,-1000,
-1000,1202,-1000, 639,-1000,-1000,-1000, 345,-1000, 300,
 840,-1000,-1000, 277,-1000,-1000,-1000, 332,-1000, 577,
 331, -46, 163, 161, 159, 515, 840, 157, 329, 327,
  49, 155, 153,-1000, 280, 840, 232, 114, -63,-1000,
-1000,-1000,-1000, 252, 256,-1000,-1000,-1000,-1000,-1000,
 840, 840, 840,   1, 325, 840,-1000,-1000, 323, 840,
 840,1151,-1000,-1000,-1000,-1000, 706,  94, 321,  93,
  74,-1000,  91,-1000, -23, -28,-1000,-1000, 515, 840,
 515, 840, 515, 320, 315,  21, 312,-1000,  90,-1000,
-1000,-1000, 515, 840, 301,-1000, -30,-1000, 515,-1000
};
short	yypgo[] =
{
   0,  31, 215, 456,  15,  22, 191,  25, 453,  30,
  28, 190,  35,  18, 449,  24,  45,   3,  47,   6,
   1,  13,   0,  19, 447,   2,  16, 444, 442,  32,
 441, 440,  69,  29,  46, 438, 437,  11,   9,   5,
 420,  10,  26, 419,  23,  37, 418, 415,  38,   7,
   4,   8, 414, 409, 408, 140, 406, 403, 401, 391,
  21, 385,  17, 384, 383,  14, 382,  12, 380, 375,
 369, 368, 367, 366, 354, 352,  27, 323
};
short	yyr1[] =
{
   0,  52,  52,  53,  53,  56,  58,  53,  55,  59,
  55,  55,  34,  34,  35,  35,  35,  35,  27,  27,
  27,  39,  61,  39,  39,  57,  57,  62,  62,  64,
  63,  66,  63,  65,  65,  67,  67,  40,  40,  40,
  44,  44,  45,  45,  45,  46,  46,  46,  47,  47,
  47,  50,  50,  42,  42,  42,  43,  43,  43,  43,
  51,  51,  51,  15,  15,  16,  16,  16,  16,  16,
  19,  28,  28,  36,  36,  37,  37,  37,  20,  20,
  20,  38,  68,  38,  38,  38,  38,  38,  38,  38,
  38,  38,  38,  38,  38,  38,  17,  17,  48,  48,
  49,  21,  21,  22,  22,  22,  22,  22,  22,  22,
  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,
  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,
  22,  22,  22,  22,  23,  23,  23,  29,  29,  29,
  29,  29,  29,  29,  29,  29,  29,  29,  24,  24,
  24,  24,  24,  24,  24,  24,  24,  24,  24,  24,
  24,  24,  24,  24,  24,  24,  24,  24,  24,  32,
  30,  30,  33,  31,  31,  25,  25,  26,  26,  69,
  11,  54,  54,  14,  14,  13,  13,  13,  13,  13,
  10,   9,  60,  12,  70,  12,  71,  12,  12,  72,
  12,  73,  12,  12,  74,  75,  12,  77,  12,  12,
  12,   8,   8,   6,   6,   7,   7,   2,   2,   2,
  76,  76,  76,  76,   5,   5,   5,   5,   5,   5,
   5,   5,   5,   5,   3,   3,   3,   3,   3,   4,
   4,  18,  41,   1,   1,   1
};
short	yyr2[] =
{
   0,   0,   2,   2,   3,   0,   0,   6,   1,   0,
   4,   3,   1,   3,   1,   3,   4,   4,   0,   3,
   4,   1,   0,   4,   3,   0,   4,   1,   3,   0,
   4,   0,   5,   0,   1,   1,   3,   1,   3,   2,
   0,   1,   2,   3,   1,   1,   4,   4,   2,   3,
   3,   1,   3,   3,   2,   2,   2,   3,   1,   2,
   1,   1,   2,   0,   1,   1,   2,   2,   3,   3,
   4,   0,   2,   1,   2,   3,   2,   2,   2,   1,
   2,   2,   0,   2,   5,   7,   9,   5,   7,   3,
   5,   2,   2,   3,   5,   5,   0,   1,   0,   1,
   1,   1,   3,   1,   3,   3,   3,   3,   3,   3,
   3,   3,   3,   3,   3,   3,   3,   3,   3,   3,
   3,   3,   5,   3,   3,   3,   3,   3,   3,   3,
   3,   3,   3,   3,   1,   5,   7,   1,   2,   2,
   2,   2,   2,   2,   2,   2,   2,   2,   3,   5,
   5,   4,   4,   3,   3,   2,   2,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
   1,   2,   1,   1,   2,   0,   1,   1,   3,   0,
   4,   0,   1,   1,   1,   1,   2,   1,   2,   3,
   2,   1,   1,   2,   0,   4,   0,   3,   2,   0,
   4,   0,   3,   2,   0,   0,   7,   0,   5,   1,
   1,   1,   2,   1,   2,   0,   2,   1,   1,   1,
   1,   3,   2,   3,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,
   1,   1,   1,   1,   1,   1
};
short	yychk[] =
{
-1000, -52, -53, -54, -60, -13, -12,  -6,  79,  82,
  86,  44,  45,  -2,  -5,  -4,  -3,  60,  75,  71,
  72,  87,  83,  67,  64,  85,  92,  88,  89,  57,
  78,  66,  81,  73,   4, -55, -34, -35,  34, -41,
  42,  -1,  43,  44,  45,  -6, -12,  -2,  -1, -71,
  -1, -73,  -1,  95,   4,   5, -56, -59,  42,  41,
  -7, -34,  -6, -70, -11,  95, -72, -11, -74, -77,
 -55, -34, -57,   6, -15, -16, -18,  -9,  40,  43,
 -13, -48, -49, -22, -23, -29,  42, -24,  34,  23,
  32,  33,  97,  98,  38,  37,  76,  91, -18,  48,
  49,  50,  51,  52,  47,  46,  53,  54, -30, -31,
 -32, -33,  55,  56, -34,  -4,  93, -11, -69, -11,
  95, -76,  43, -58, -60, -50, -22,  95,  93,   5,
 -44, -34, -45,  34, -46,  42, -47,  41,  40,  94,
  34,  35,  36,  32,  33,  31,  30,  26,  27,  28,
  29,  24,  25,  23,  22,  21,  20,  19,  17,   6,
   7,   8,   9,  10,  11,  13,  12,  14,  15,  16,
  -9, -21, -22,  42,  41,  39,  40,  38,  37, -23,
 -23, -23, -23, -23, -23, -23, -23, -29,  42, -29,
  42, -32, -33, -63, -10,  -7, -75,  96,   5,   6,
 -19,  95, -62, -34, -51, -43, -50, -42,  41,  40,
 -16,  -7,  42,  41,  93, -45, -48,  40, -22, -22,
 -22, -22, -22, -22, -22, -22, -22, -22, -22, -22,
 -22, -22, -22, -22, -22, -22, -21, -22, -22, -22,
 -22, -22, -22, -22, -22, -22, -22, -22, -44,  34,
  42,   5,  93, -25, -26, -22, -21,  -1,  -1,  -9,
  -9, -10,  96, -64, -14, -12,  -8,  -5, -76, -76,
 -22, -27,   4,   5,  96, -50, -42,   5,   6, -49,
  -1, -45, -15, -48,  93,  94,  18,  93,  -7, -21,
  93,   5,  94, -44, -44, -66, -65, -67, -40, -34,
 -41,  18,  -5,  96, -60, -28, -62,   5,  94,  93,
  94, -22, -23,  95, -26,  93,  93, -65,   4,   5,
  18, -49,   4, -39, -34,  96, -20,   2, -38, -36,
 -17, -68,  70,  68,  84,  63,  74,  80,  58,  61,
  69,  77,  90, -37, -21,  59,  62,  43, -51,   4,
 -67, -49,   4,   5, -61,   4, -37, -38,   4, -19,
  42,  42,  42, -20, -17,  42,   4,   4,  43,  42,
  42, -22,  18,  18,  96, -39,   6, -21, -17, -21,
  84,   4, -21,   4, -25, -25,  18, -50,  93,   4,
  93,  42,  93,  93,  93, -20, -17, -20, -21, -20,
   4,   4,  65,   4,  93, -20, -17,   4,  93, -20
};
short	yydef[] =
{
   1,  -2,   2,   0, 182, 192, 185, 187, 196, 201,
   0, 209, 210, 213, 217, 218, 219, 224, 225, 226,
 227, 228, 229, 230, 231, 232, 233, 239, 240, 234,
 235, 236, 237, 238,   3,   0,  -2,  12, 215,  14,
   0, 242, 243, 244, 245, 186, 188, 214,  -2,   0,
  -2,   0,  -2, 207,   4,   0,  25,   0,  63,  98,
   0,   0, 189,   0, 197, 179,   0, 202,   0,   0,
  11,  -2,   6,   0,   0,  64,  65,  40,   0, 241,
 191,   0,  99, 100, 103, 134,   0, 137,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0, 157, 158,
 159, 160, 161, 162, 163, 164, 165, 166, 167, 168,
 170, 173, 169, 172,  13, 216,  15, 195, 215, 200,
 205,   0, 220,   0,   0,  10,  51,   0,  16,   0,
  66,  67,  41, 215,  44,   0,  45,  98,   0,  17,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
  40,   0, 101, 175,   0,   0,   0, 155, 156, 138,
 139, 140, 141, 142, 143, 144, 145, 146,   0, 147,
   0, 171, 174, 215,  29,   0,   0, 208, 222,   0,
   7,  18,   0,  27,   0,  60,  61,  58,   0,   0,
  69,  42,  63,  98,  48,   0,   0,  68, 104, 105,
 106, 107, 108, 109, 110, 111, 112, 113, 114, 115,
 116, 117, 118, 119, 120, 121,   0, 123, 124, 125,
 126, 127, 128, 129, 130, 131, 132, 133,   0, 215,
   0,   0, 148,   0, 176, 177,   0, 153, 154,  40,
  40,  31, 180,  33, 190, 183, 184, 211,   0, 223,
 221,  71,  26,   0,  52,  62,  59,  56,  55,   0,
  54,  43,   0,   0,  50,  49,   0,   0,  42, 102,
 151,   0, 152,   0,   0,  33,   0,  34,  35,  37,
  14,   0, 212, 206,   0,  -2,  28,  57,  53,  46,
  47, 122, 135,   0, 178, 149, 150,   0,  30,   0,
   0,  39,  19,   0,  -2,  70,  72,   0,  79,  -2,
   0,   0,   0,   0,   0,  -2,  96,   0,   0,   0,
   0,   0,   0,  73,  97,   0,   0, 241,   0,  32,
  36,  38,  20,   0,   0,  78,  74,  80,  81,  83,
   0,  96,   0,   0,   0,   0,  91,  92,   0, 175,
 175,   0,  76,  77, 136,  24,   0,   0,   0,   0,
   0,  89,   0,  93,   0,   0,  75,  23,  -2,  96,
  -2,   0,  -2,   0,   0,  84,   0,  87,   0,  90,
  94,  95,  -2,  96,   0,  85,   0,  88,  -2,  86
};
short	yytok1[] =
{
   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,  97,   0,   0,   0,  36,  23,   0,
  42,  93,  34,  32,   5,  33,  40,  35,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  18,   4,
  26,   6,  27,  17,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,  41,   0,  94,  22,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,  95,  21,  96,  98
};
short	yytok2[] =
{
   2,   3,   7,   8,   9,  10,  11,  12,  13,  14,
  15,  16,  19,  20,  24,  25,  28,  29,  30,  31,
  37,  38,  39,  43,  44,  45,  46,  47,  48,  49,
  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,
  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,
  90,  91,  92
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
#line	74	"cc.y"
{
		dodecl(xdecl, lastclass, lasttype, Z, 1);
	} break;
case 5:
#line	79	"cc.y"
{
		lastdcl = T;
		dodecl(xdecl, lastclass, lasttype, yypt[-0].yyv.node, 0);
		if(lastdcl == T || lastdcl->etype != TFUNC) {
			diag(yypt[-0].yyv.node, "not a function");
			lastdcl = types[TFUNC];
		}
		thisfn = lastdcl;
		markdcl();
		firstdcl = dclstack;
		argmark(yypt[-0].yyv.node, 0);
	} break;
case 6:
#line	92	"cc.y"
{
		argmark(yypt[-2].yyv.node, 1);
	} break;
case 7:
#line	96	"cc.y"
{
		yypt[-0].yyv.node->blk = 0;
		codgen(yypt[-0].yyv.node, yypt[-4].yyv.node, lineno);
		revertdcl();
	} break;
case 8:
#line	104	"cc.y"
{
		dodecl(xdecl, lastclass, lasttype, yypt[-0].yyv.node, 1);
	} break;
case 9:
#line	108	"cc.y"
{
		yypt[-0].yyv.node = dodecl(xdecl, lastclass, lasttype, yypt[-0].yyv.node, 0);
	} break;
case 10:
#line	112	"cc.y"
{
		yypt[-0].yyv.node = doinit(yypt[-3].yyv.node->sym, yypt[-3].yyv.node->type, 0L, yypt[-0].yyv.node);
		yypt[-0].yyv.node = new(ODAS, yypt[-3].yyv.node, yypt[-0].yyv.node);
		yypt[-0].yyv.node->type = yypt[-3].yyv.node->type;
		yypt[-0].yyv.node->lineno = yypt[-3].yyv.node->lineno;
		vtgen(yypt[-0].yyv.node);
	} break;
case 13:
#line	124	"cc.y"
{
		yyval.node = new(OIND, yypt[-0].yyv.node, Z);
		yyval.node->garb = simpleg(yypt[-1].yyv.lval);
	} break;
case 15:
#line	132	"cc.y"
{
		yyval.node = yypt[-1].yyv.node;
	} break;
case 16:
#line	136	"cc.y"
{
		yyval.node = new(OFUNC, yypt[-3].yyv.node, yypt[-1].yyv.node);
		/* outfun($$); */
	} break;
case 17:
#line	141	"cc.y"
{
		yyval.node = new(OARRAY, yypt[-3].yyv.node, yypt[-1].yyv.node);
	} break;
case 18:
#line	149	"cc.y"
{
		yyval.node = Z;
	} break;
case 19:
#line	153	"cc.y"
{
		yyval.node = dodecl(adecl, lastclass, lasttype, Z, 1);
		if(yypt[-2].yyv.node != Z)
			if(yyval.node != Z)
				yyval.node = new(OLIST, yypt[-2].yyv.node, yyval.node);
			else
				yyval.node = yypt[-2].yyv.node;
	} break;
case 20:
#line	162	"cc.y"
{
		yyval.node = yypt[-3].yyv.node;
		if(yypt[-1].yyv.node != Z) {
			yyval.node = yypt[-1].yyv.node;
			if(yypt[-3].yyv.node != Z)
				yyval.node = new(OLIST, yypt[-3].yyv.node, yypt[-1].yyv.node);
		}
	} break;
case 21:
#line	173	"cc.y"
{
		yyval.node = dodecl(adecl, lastclass, lasttype, yypt[-0].yyv.node, 1);
		if(yyval.node->sym->class == CSTATIC)
			yyval.node = Z;
	} break;
case 22:
#line	179	"cc.y"
{
		yypt[-0].yyv.node = dodecl(adecl, lastclass, lasttype, yypt[-0].yyv.node, 0);
	} break;
case 23:
#line	183	"cc.y"
{
		/* long w; */

		/* w = $1->sym->type->width; */
		yyval.node = doinit(yypt[-3].yyv.node->sym, yypt[-3].yyv.node->type, 0L, yypt[-0].yyv.node);
		/* $$ = contig($1->sym, $$, w); */
		yyval.node = new(ODAS, yypt[-3].yyv.node, yyval.node);
		yyval.node->type = yypt[-3].yyv.node->type;
		yyval.node->lineno = yypt[-3].yyv.node->lineno;
		vtgen(yyval.node);
		if(yypt[-3].yyv.node->sym->class == CSTATIC)
			yyval.node = Z;
	} break;
case 24:
#line	197	"cc.y"
{
		yyval.node = yypt[-2].yyv.node;
		if(yypt[-0].yyv.node != Z) {
			yyval.node = yypt[-0].yyv.node;
			if(yypt[-2].yyv.node != Z)
				yyval.node = new(OLIST, yypt[-2].yyv.node, yypt[-0].yyv.node);
		}
	} break;
case 27:
#line	214	"cc.y"
{
		dodecl(pdecl, lastclass, lasttype, yypt[-0].yyv.node, 1);
	} break;
case 29:
#line	224	"cc.y"
{
		lasttype = yypt[-0].yyv.type;
	} break;
case 31:
#line	229	"cc.y"
{
		lasttype = yypt[-0].yyv.type;
	} break;
case 33:
#line	235	"cc.y"
{
		lastfield = 0;
		edecl(CXXX, lasttype, S);
	} break;
case 35:
#line	243	"cc.y"
{
		dodecl(edecl, CXXX, lasttype, yypt[-0].yyv.node, 1);
	} break;
case 37:
#line	250	"cc.y"
{
		lastbit = 0;
		firstbit = 1;
	} break;
case 38:
#line	255	"cc.y"
{
		yyval.node = new(OBIT, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 39:
#line	259	"cc.y"
{
		yyval.node = new(OBIT, Z, yypt[-0].yyv.node);
	} break;
case 40:
#line	267	"cc.y"
{
		yyval.node = (Z);
	} break;
case 42:
#line	274	"cc.y"
{
		yyval.node = new(OIND, (Z), Z);
		yyval.node->garb = simpleg(yypt[-0].yyv.lval);
	} break;
case 43:
#line	279	"cc.y"
{
		yyval.node = new(OIND, yypt[-0].yyv.node, Z);
		yyval.node->garb = simpleg(yypt[-1].yyv.lval);
	} break;
case 46:
#line	288	"cc.y"
{
		yyval.node = new(OFUNC, yypt[-3].yyv.node, yypt[-1].yyv.node);
	} break;
case 47:
#line	292	"cc.y"
{
		yyval.node = new(OARRAY, yypt[-3].yyv.node, yypt[-1].yyv.node);
	} break;
case 48:
#line	298	"cc.y"
{
		yyval.node = new(OFUNC, (Z), Z);
	} break;
case 49:
#line	302	"cc.y"
{
		yyval.node = new(OARRAY, (Z), yypt[-1].yyv.node);
	} break;
case 50:
#line	306	"cc.y"
{
		yyval.node = yypt[-1].yyv.node;
	} break;
case 52:
#line	313	"cc.y"
{
		yyval.node = new(OINIT, invert(yypt[-1].yyv.node), Z);
	} break;
case 53:
#line	319	"cc.y"
{
		yyval.node = new(OARRAY, yypt[-1].yyv.node, Z);
	} break;
case 54:
#line	323	"cc.y"
{
		yyval.node = new(OELEM, Z, Z);
		yyval.node->sym = yypt[-0].yyv.sym;
	} break;
case 57:
#line	332	"cc.y"
{
		yyval.node = new(OLIST, yypt[-2].yyv.node, yypt[-1].yyv.node);
	} break;
case 59:
#line	337	"cc.y"
{
		yyval.node = new(OLIST, yypt[-1].yyv.node, yypt[-0].yyv.node);
	} break;
case 62:
#line	345	"cc.y"
{
		yyval.node = new(OLIST, yypt[-1].yyv.node, yypt[-0].yyv.node);
	} break;
case 63:
#line	350	"cc.y"
{
		yyval.node = Z;
	} break;
case 64:
#line	354	"cc.y"
{
		yyval.node = invert(yypt[-0].yyv.node);
	} break;
case 66:
#line	362	"cc.y"
{
		yyval.node = new(OPROTO, yypt[-0].yyv.node, Z);
		yyval.node->type = yypt[-1].yyv.type;
	} break;
case 67:
#line	367	"cc.y"
{
		yyval.node = new(OPROTO, yypt[-0].yyv.node, Z);
		yyval.node->type = yypt[-1].yyv.type;
	} break;
case 68:
#line	372	"cc.y"
{
		yyval.node = new(ODOTDOT, Z, Z);
	} break;
case 69:
#line	376	"cc.y"
{
		yyval.node = new(OLIST, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 70:
#line	382	"cc.y"
{
		yyval.node = invert(yypt[-1].yyv.node);
		if(yypt[-2].yyv.node != Z)
			yyval.node = new(OLIST, yypt[-2].yyv.node, yyval.node);
		if(yyval.node == Z)
			yyval.node = new(ONUL, Z, Z);
		yyval.node->blk = 1;
	} break;
case 71:
#line	392	"cc.y"
{
		yyval.node = Z;
	} break;
case 72:
#line	396	"cc.y"
{
		if(yypt[-1].yyv.node == Z)
			yyval.node = yypt[-0].yyv.node;
		else
			yyval.node = new(OLIST, yypt[-1].yyv.node, yypt[-0].yyv.node);
	} break;
case 74:
#line	406	"cc.y"
{
		yyval.node = new(OLIST, yypt[-1].yyv.node, yypt[-0].yyv.node);
	} break;
case 75:
#line	412	"cc.y"
{
		yyval.node = new(OCASE, yypt[-1].yyv.node, Z);
		yyval.node->lineno = yypt[-1].yyv.node->lineno;
	} break;
case 76:
#line	417	"cc.y"
{
		yyval.node = new(OCASE, Z, Z);
	} break;
case 77:
#line	421	"cc.y"
{
		yyval.node = new(OLABEL, dcllabel(yypt[-1].yyv.sym, 1), Z);
		yypt[-1].yyv.sym->lineno = lineno;
	} break;
case 78:
#line	428	"cc.y"
{
		yyval.node = Z;
	} break;
case 80:
#line	433	"cc.y"
{
		yyval.node = new(OLIST, yypt[-1].yyv.node, yypt[-0].yyv.node);
	} break;
case 81:
#line	439	"cc.y"
{
		if(yyval.node == Z)
			yyval.node = new(ONUL, Z, Z);
		yyval.node->kind = KEXP;
	} break;
case 82:
#line	444	"cc.y"
{
		markdcl();
	} break;
case 83:
#line	448	"cc.y"
{
		revertdcl();
		yyval.node = yypt[-0].yyv.node;
	} break;
case 84:
#line	453	"cc.y"
{
		yyval.node = new(OIF, yypt[-2].yyv.node, new(OLIST, yypt[-0].yyv.node, Z));
		yyval.node->lineno = yypt[-2].yyv.node->lineno;
		yypt[-0].yyv.node->blk = 0;
	} break;
case 85:
#line	459	"cc.y"
{
		yyval.node = new(OIF, yypt[-4].yyv.node, new(OLIST, yypt[-2].yyv.node, yypt[-0].yyv.node));
		yyval.node->lineno = yypt[-4].yyv.node->lineno;
		yypt[-2].yyv.node->blk = yypt[-0].yyv.node->blk = 0;
	} break;
case 86:
#line	465	"cc.y"
{
		yyval.node = new(OFOR, new(OLIST, yypt[-4].yyv.node, new(OLIST, yypt[-6].yyv.node, yypt[-2].yyv.node)), yypt[-0].yyv.node);
		if(yypt[-6].yyv.node != Z)
			yyval.node->lineno = yypt[-6].yyv.node->lineno;
		else if(yypt[-4].yyv.node != Z)
			yyval.node->lineno = yypt[-4].yyv.node->lineno;
		else if(yypt[-2].yyv.node != Z)
			yyval.node->lineno = yypt[-2].yyv.node->lineno;
		else
			yyval.node->lineno = line(yypt[-0].yyv.node);
		yypt[-0].yyv.node->blk = 0;
	} break;
case 87:
#line	478	"cc.y"
{
		yyval.node = new(OWHILE, yypt[-2].yyv.node, yypt[-0].yyv.node);
		yyval.node->lineno = yypt[-2].yyv.node->lineno;
		yypt[-0].yyv.node->blk = 0;
	} break;
case 88:
#line	484	"cc.y"
{
		yyval.node = new(ODWHILE, yypt[-2].yyv.node, yypt[-5].yyv.node);
		yyval.node->lineno = line(yypt[-5].yyv.node);
		yypt[-5].yyv.node->blk = 0;
	} break;
case 89:
#line	490	"cc.y"
{
		yyval.node = new(ORETURN, yypt[-1].yyv.node, Z);
		yyval.node->type = thisfn->link;
		if(yypt[-1].yyv.node != Z)
			yyval.node->lineno = yypt[-1].yyv.node->lineno;
	} break;
case 90:
#line	497	"cc.y"
{
		yyval.node = new(OSWITCH, yypt[-2].yyv.node, yypt[-0].yyv.node);
		yyval.node->lineno = yypt[-2].yyv.node->lineno;
		yypt[-0].yyv.node->blk = 0;
	} break;
case 91:
#line	503	"cc.y"
{
		yyval.node = new(OBREAK, Z, Z);
	} break;
case 92:
#line	507	"cc.y"
{
		yyval.node = new(OCONTINUE, Z, Z);
	} break;
case 93:
#line	511	"cc.y"
{
		yyval.node = new(OGOTO, dcllabel(yypt[-1].yyv.sym, 0), Z);
		yypt[-1].yyv.sym->lineno = lineno;
	} break;
case 94:
#line	516	"cc.y"
{
		yyval.node = new(OUSED, yypt[-2].yyv.node, Z);
		yyval.node->lineno = line(yypt[-2].yyv.node);
	} break;
case 95:
#line	521	"cc.y"
{
		yyval.node = new(OSET, yypt[-2].yyv.node, Z);
		yyval.node->lineno = line(yypt[-2].yyv.node);
	} break;
case 96:
#line	527	"cc.y"
{
		yyval.node = Z;
	} break;
case 98:
#line	533	"cc.y"
{
		yyval.node = Z;
	} break;
case 100:
#line	540	"cc.y"
{
		yyval.node = new(OCAST, yypt[-0].yyv.node, Z);
		yyval.node->type = types[TLONG];
	} break;
case 102:
#line	548	"cc.y"
{
		yyval.node = new(OCOMMA, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 104:
#line	555	"cc.y"
{
		yyval.node = new(OMUL, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 105:
#line	559	"cc.y"
{
		yyval.node = new(ODIV, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 106:
#line	563	"cc.y"
{
		yyval.node = new(OMOD, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 107:
#line	567	"cc.y"
{
		yyval.node = new(OADD, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 108:
#line	571	"cc.y"
{
		yyval.node = new(OSUB, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 109:
#line	575	"cc.y"
{
		yyval.node = new(OASHR, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 110:
#line	579	"cc.y"
{
		yyval.node = new(OASHL, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 111:
#line	583	"cc.y"
{
		yyval.node = new(OLT, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 112:
#line	587	"cc.y"
{
		yyval.node = new(OGT, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 113:
#line	591	"cc.y"
{
		yyval.node = new(OLE, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 114:
#line	595	"cc.y"
{
		yyval.node = new(OGE, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 115:
#line	599	"cc.y"
{
		yyval.node = new(OEQ, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 116:
#line	603	"cc.y"
{
		yyval.node = new(ONE, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 117:
#line	607	"cc.y"
{
		yyval.node = new(OAND, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 118:
#line	611	"cc.y"
{
		yyval.node = new(OXOR, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 119:
#line	615	"cc.y"
{
		yyval.node = new(OOR, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 120:
#line	619	"cc.y"
{
		yyval.node = new(OANDAND, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 121:
#line	623	"cc.y"
{
		yyval.node = new(OOROR, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 122:
#line	627	"cc.y"
{
		yyval.node = new(OCOND, yypt[-4].yyv.node, new(OLIST, yypt[-2].yyv.node, yypt[-0].yyv.node));
	} break;
case 123:
#line	631	"cc.y"
{
		yyval.node = new(OAS, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 124:
#line	635	"cc.y"
{
		yyval.node = new(OASADD, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 125:
#line	639	"cc.y"
{
		yyval.node = new(OASSUB, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 126:
#line	643	"cc.y"
{
		yyval.node = new(OASMUL, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 127:
#line	647	"cc.y"
{
		yyval.node = new(OASDIV, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 128:
#line	651	"cc.y"
{
		yyval.node = new(OASMOD, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 129:
#line	655	"cc.y"
{
		yyval.node = new(OASASHL, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 130:
#line	659	"cc.y"
{
		yyval.node = new(OASASHR, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 131:
#line	663	"cc.y"
{
		yyval.node = new(OASAND, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 132:
#line	667	"cc.y"
{
		yyval.node = new(OASXOR, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 133:
#line	671	"cc.y"
{
		yyval.node = new(OASOR, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 135:
#line	678	"cc.y"
{
		yyval.node = new(OCAST, yypt[-0].yyv.node, Z);
		dodecl(NODECL, CXXX, yypt[-3].yyv.type, yypt[-2].yyv.node, 1);
		yyval.node->type = lastdcl;
	} break;
case 136:
#line	684	"cc.y"
{
		yyval.node = new(OSTRUCT, yypt[-1].yyv.node, Z);
		dodecl(NODECL, CXXX, yypt[-5].yyv.type, yypt[-4].yyv.node, 1);
		yyval.node->type = lastdcl;
	} break;
case 138:
#line	693	"cc.y"
{
		yyval.node = new(OIND, yypt[-0].yyv.node, Z);
	} break;
case 139:
#line	697	"cc.y"
{
		yyval.node = new(OADDR, yypt[-0].yyv.node, Z);
	} break;
case 140:
#line	701	"cc.y"
{
		yyval.node = new(OPOS, yypt[-0].yyv.node, Z);
	} break;
case 141:
#line	705	"cc.y"
{
		yyval.node = new(ONEG, yypt[-0].yyv.node, Z);
	} break;
case 142:
#line	709	"cc.y"
{
		yyval.node = new(ONOT, yypt[-0].yyv.node, Z);
	} break;
case 143:
#line	713	"cc.y"
{
		yyval.node = new(OCOM, yypt[-0].yyv.node, Z);
	} break;
case 144:
#line	717	"cc.y"
{
		yyval.node = new(OPREINC, yypt[-0].yyv.node, Z);
	} break;
case 145:
#line	721	"cc.y"
{
		yyval.node = new(OPREDEC, yypt[-0].yyv.node, Z);
	} break;
case 146:
#line	725	"cc.y"
{
		yyval.node = new(OSIZE, yypt[-0].yyv.node, Z);
	} break;
case 147:
#line	729	"cc.y"
{
		yyval.node = new(OSIGN, yypt[-0].yyv.node, Z);
	} break;
case 148:
#line	735	"cc.y"
{
		yyval.node = yypt[-1].yyv.node;
	} break;
case 149:
#line	739	"cc.y"
{
		yyval.node = new(OSIZE, Z, Z);
		dodecl(NODECL, CXXX, yypt[-2].yyv.type, yypt[-1].yyv.node, 1);
		yyval.node->type = lastdcl;
	} break;
case 150:
#line	745	"cc.y"
{
		yyval.node = new(OSIGN, Z, Z);
		dodecl(NODECL, CXXX, yypt[-2].yyv.type, yypt[-1].yyv.node, 1);
		yyval.node->type = lastdcl;
	} break;
case 151:
#line	751	"cc.y"
{
		yyval.node = new(OFUNC, yypt[-3].yyv.node, Z);
		if(yypt[-3].yyv.node->op == ONAME)
		if(yypt[-3].yyv.node->type == T)
			dodecl(xdecl, CXXX, types[TINT], yyval.node, 1);
		yyval.node->right = invert(yypt[-1].yyv.node);
		yyval.node->kind = KEXP;
	} break;
case 152:
#line	760	"cc.y"
{
		yyval.node = new(OARRIND, yypt[-3].yyv.node, yypt[-1].yyv.node);
	} break;
case 153:
#line	764	"cc.y"
{
		yyval.node = new(ODOTIND, yypt[-2].yyv.node, Z);
		yyval.node->sym = yypt[-0].yyv.sym;
	} break;
case 154:
#line	769	"cc.y"
{
		yyval.node = new(ODOT, yypt[-2].yyv.node, Z);
		yyval.node->sym = yypt[-0].yyv.sym;
	} break;
case 155:
#line	774	"cc.y"
{
		yyval.node = new(OPOSTINC, yypt[-1].yyv.node, Z);
	} break;
case 156:
#line	778	"cc.y"
{
		yyval.node = new(OPOSTDEC, yypt[-1].yyv.node, Z);
	} break;
case 158:
#line	783	"cc.y"
{
		yyval.node = new(OCONST, Z, Z);
		yyval.node->type = types[TINT];
		yyval.node->vconst = yypt[-0].yyv.vval;
		yyval.node->kind = KCHR;
	} break;
case 159:
#line	790	"cc.y"
{
		yyval.node = new(OCONST, Z, Z);
		yyval.node->type = types[TINT];
		yyval.node->vconst = yypt[-0].yyv.vval;
		yyval.node->kind = lastnumbase;
	} break;
case 160:
#line	797	"cc.y"
{
		yyval.node = new(OCONST, Z, Z);
		yyval.node->type = types[TLONG];
		yyval.node->vconst = yypt[-0].yyv.vval;
		yyval.node->kind = lastnumbase;
	} break;
case 161:
#line	804	"cc.y"
{
		yyval.node = new(OCONST, Z, Z);
		yyval.node->type = types[TUINT];
		yyval.node->vconst = yypt[-0].yyv.vval;
		yyval.node->kind = lastnumbase;
	} break;
case 162:
#line	811	"cc.y"
{
		yyval.node = new(OCONST, Z, Z);
		yyval.node->type = types[TULONG];
		yyval.node->vconst = yypt[-0].yyv.vval;
		yyval.node->kind = lastnumbase;
	} break;
case 163:
#line	818	"cc.y"
{
		yyval.node = new(OCONST, Z, Z);
		yyval.node->type = types[TDOUBLE];
		yyval.node->fconst = yypt[-0].yyv.dval;
		yyval.node->cstring = strdup(symb);
		yyval.node->kind = lastnumbase;
	} break;
case 164:
#line	826	"cc.y"
{
		yyval.node = new(OCONST, Z, Z);
		yyval.node->type = types[TFLOAT];
		yyval.node->fconst = yypt[-0].yyv.dval;
		yyval.node->cstring = strdup(symb);
		yyval.node->kind = lastnumbase;
	} break;
case 165:
#line	834	"cc.y"
{
		yyval.node = new(OCONST, Z, Z);
		yyval.node->type = types[TVLONG];
		yyval.node->vconst = yypt[-0].yyv.vval;
		yyval.node->kind = lastnumbase;
	} break;
case 166:
#line	841	"cc.y"
{
		yyval.node = new(OCONST, Z, Z);
		yyval.node->type = types[TUVLONG];
		yyval.node->vconst = yypt[-0].yyv.vval;
		yyval.node->kind = lastnumbase;
	} break;
case 169:
#line	852	"cc.y"
{
		yyval.node = new(OSTRING, Z, Z);
		yyval.node->type = typ(TARRAY, types[TCHAR]);
		yyval.node->type->width = yypt[-0].yyv.sval.l + 1;
		yyval.node->cstring = yypt[-0].yyv.sval.s;
		yyval.node->sym = symstring;
	} break;
case 170:
#line	862	"cc.y"
{
		yyval.node = yypt[-0].yyv.node;
	} break;
case 171:
#line	866	"cc.y"
{
		char *s;
		int n1, n2;

		n1 = yypt[-1].yyv.node->type->width - 1;
		n2 = yypt[-0].yyv.node->type->width - 1;
		s = alloc(n1+n2+MAXALIGN);

		memcpy(s, yypt[-1].yyv.node->cstring, n1);
		memcpy(s+n1, yypt[-0].yyv.node->cstring, n2);
		s[n1+n2] = 0;

		yypt[-1].yyv.node->left = new(OCAT, ncopy(yypt[-1].yyv.node), yypt[-0].yyv.node);

		yyval.node = yypt[-1].yyv.node;
		yyval.node->type->width += n2;
		yyval.node->cstring = s;
	} break;
case 172:
#line	887	"cc.y"
{
		yyval.node = new(OLSTRING, Z, Z);
		yyval.node->type = typ(TARRAY, types[TUSHORT]);
		yyval.node->type->width = yypt[-0].yyv.sval.l + sizeof(TRune);
		yyval.node->rstring = (TRune*)yypt[-0].yyv.sval.s;
		yyval.node->sym = symstring;
	} break;
case 173:
#line	897	"cc.y"
{
		yyval.node = yypt[-0].yyv.node;
	} break;
case 174:
#line	901	"cc.y"
{
		char *s;
		int n1, n2;

		n1 = yypt[-1].yyv.node->type->width - sizeof(TRune);
		n2 = yypt[-0].yyv.node->type->width - sizeof(TRune);
		s = alloc(n1+n2+MAXALIGN);

		memcpy(s, yypt[-1].yyv.node->rstring, n1);
		memcpy(s+n1, yypt[-0].yyv.node->rstring, n2);
		*(TRune*)(s+n1+n2) = 0;

		yypt[-1].yyv.node->left = new(OCAT, ncopy(yypt[-1].yyv.node), yypt[-0].yyv.node);

		yyval.node = yypt[-1].yyv.node;
		yyval.node->type->width += n2;
		yyval.node->rstring = (TRune*)s;
	} break;
case 175:
#line	921	"cc.y"
{
		yyval.node = Z;
	} break;
case 178:
#line	929	"cc.y"
{
		yyval.node = new(OLIST, yypt[-2].yyv.node, yypt[-0].yyv.node);
	} break;
case 179:
#line	935	"cc.y"
{
		yyval.tyty.t1 = strf;
		yyval.tyty.t2 = strl;
		strf = T;
		strl = T;
		lastbit = 0;
		firstbit = 1;
	} break;
case 180:
#line	944	"cc.y"
{
		yyval.type = strf;
		strf = yypt[-2].yyv.tyty.t1;
		strl = yypt[-2].yyv.tyty.t2;
	} break;
case 181:
#line	951	"cc.y"
{
		lastclass = CXXX;
		lasttype = types[TINT];
	} break;
case 183:
#line	959	"cc.y"
{
		yyval.tycl.t = yypt[-0].yyv.type;
		yyval.tycl.c = CXXX;
	} break;
case 184:
#line	964	"cc.y"
{
		yyval.tycl.t = simplet(yypt[-0].yyv.lval);
		yyval.tycl.c = simplec(yypt[-0].yyv.lval);
	} break;
case 185:
#line	971	"cc.y"
{
		yyval.tycl.t = yypt[-0].yyv.type;
		yyval.tycl.c = CXXX;
	} break;
case 186:
#line	976	"cc.y"
{
		yyval.tycl.t = yypt[-1].yyv.type;
		yyval.tycl.c = simplec(yypt[-0].yyv.lval);
		if(yypt[-0].yyv.lval & ~BCLASS & ~BGARB)
			diag(Z, "illegal combination of types 1: %Q/%T", yypt[-0].yyv.lval, yypt[-1].yyv.type);
	} break;
case 187:
#line	983	"cc.y"
{
		yyval.tycl.t = simplet(yypt[-0].yyv.lval);
		yyval.tycl.c = simplec(yypt[-0].yyv.lval);
		yyval.tycl.t = garbt(yyval.tycl.t, yypt[-0].yyv.lval);
	} break;
case 188:
#line	989	"cc.y"
{
		yyval.tycl.t = yypt[-0].yyv.type;
		yyval.tycl.c = simplec(yypt[-1].yyv.lval);
		yyval.tycl.t = garbt(yyval.tycl.t, yypt[-1].yyv.lval);
		if(yypt[-1].yyv.lval & ~BCLASS & ~BGARB)
			diag(Z, "illegal combination of types 2: %Q/%T", yypt[-1].yyv.lval, yypt[-0].yyv.type);
	} break;
case 189:
#line	997	"cc.y"
{
		yyval.tycl.t = yypt[-1].yyv.type;
		yyval.tycl.c = simplec(yypt[-2].yyv.lval|yypt[-0].yyv.lval);
		yyval.tycl.t = garbt(yyval.tycl.t, yypt[-2].yyv.lval|yypt[-0].yyv.lval);
		if((yypt[-2].yyv.lval|yypt[-0].yyv.lval) & ~BCLASS & ~BGARB || yypt[-0].yyv.lval & BCLASS)
			diag(Z, "illegal combination of types 3: %Q/%T/%Q", yypt[-2].yyv.lval, yypt[-1].yyv.type, yypt[-0].yyv.lval);
	} break;
case 190:
#line	1007	"cc.y"
{
		yyval.type = yypt[-0].yyv.tycl.t;
		if(yypt[-0].yyv.tycl.c != CXXX)
			diag(Z, "illegal combination of class 4: %s", cnames[yypt[-0].yyv.tycl.c]);
		yyval.type = garbt(yyval.type, yypt[-1].yyv.lval);
	} break;
case 191:
#line	1016	"cc.y"
{
		yyval.type = yypt[-0].yyv.tycl.t;
		if(yypt[-0].yyv.tycl.c != CXXX)
			diag(Z, "illegal combination of class 4: %s", cnames[yypt[-0].yyv.tycl.c]);
	} break;
case 192:
#line	1024	"cc.y"
{
		lasttype = yypt[-0].yyv.tycl.t;
		lastclass = yypt[-0].yyv.tycl.c;
	} break;
case 193:
#line	1031	"cc.y"
{
		dotag(yypt[-0].yyv.sym, TSTRUCT, 0);
		yyval.type = yypt[-0].yyv.sym->suetag;
		yypt[-0].yyv.sym->lineno = lineno;
	} break;
case 194:
#line	1037	"cc.y"
{
		dotag(yypt[-0].yyv.sym, TSTRUCT, autobn);
		saveline = yypt[-0].yyv.sym->lineno = lineno;
	} break;
case 195:
#line	1042	"cc.y"
{
		yyval.type = yypt[-2].yyv.sym->suetag;
		if(yyval.type->link != T)
			diag(Z, "redeclare tag: %s", yypt[-2].yyv.sym->name);
		yyval.type->link = yypt[-0].yyv.type;
		yyval.type->lineno = saveline;
		suallign(yyval.type);
	} break;
case 196:
#line	1051	"cc.y"
{
		saveline = lineno;
	} break;
case 197:
#line	1055	"cc.y"
{
		char buf[128];

		taggen++;
		sprint(symb, "%s_adt_%d", outmod(buf, -1), taggen);
		yyval.type = dotag(lookup(), TSTRUCT, autobn);
		yyval.type->link = yypt[-0].yyv.type;
		yyval.type->lineno = saveline;
		lookup()->lineno = saveline;
		suallign(yyval.type);
	} break;
case 198:
#line	1067	"cc.y"
{
		dotag(yypt[-0].yyv.sym, TUNION, 0);
		yyval.type = yypt[-0].yyv.sym->suetag;
		yypt[-0].yyv.sym->lineno = lineno;
	} break;
case 199:
#line	1073	"cc.y"
{
		dotag(yypt[-0].yyv.sym, TUNION, autobn);
		saveline = yypt[-0].yyv.sym->lineno = lineno;
	} break;
case 200:
#line	1078	"cc.y"
{
		yyval.type = yypt[-2].yyv.sym->suetag;
		if(yyval.type->link != T)
			diag(Z, "redeclare tag: %s", yypt[-2].yyv.sym->name);
		yyval.type->link = yypt[-0].yyv.type;
		yyval.type->lineno = saveline;
		suallign(yyval.type);
	} break;
case 201:
#line	1087	"cc.y"
{
		saveline = lineno;
	} break;
case 202:
#line	1091	"cc.y"
{
		char buf[128];

		taggen++;
		sprint(symb, "%s_adt_%d", outmod(buf, -1), taggen);
		yyval.type = dotag(lookup(), TUNION, autobn);
		yyval.type->link = yypt[-0].yyv.type;
		yyval.type->lineno = saveline;
		lookup()->lineno = saveline;
		suallign(yyval.type);
	} break;
case 203:
#line	1103	"cc.y"
{
		dotag(yypt[-0].yyv.sym, TENUM, 0);
		yyval.type = yypt[-0].yyv.sym->suetag;
		if(yyval.type->link == T)
			yyval.type->link = types[TINT];
		yyval.type = yyval.type->link;
		yypt[-0].yyv.sym->lineno = lineno;
	} break;
case 204:
#line	1112	"cc.y"
{
		dotag(yypt[-0].yyv.sym, TENUM, autobn);
		yypt[-0].yyv.sym->lineno = lineno;
	} break;
case 205:
#line	1117	"cc.y"
{
		en.tenum = T;
		en.cenum = T;
	} break;
case 206:
#line	1122	"cc.y"
{
		yyval.type = yypt[-5].yyv.sym->suetag;
		if(yyval.type->link != T)
			diag(Z, "redeclare tag: %s", yypt[-5].yyv.sym->name);
		if(en.tenum == T) {
			diag(Z, "enum type ambiguous: %s", yypt[-5].yyv.sym->name);
			en.tenum = types[TINT];
		}
		yyval.type->link = en.tenum;
		yyval.type = en.tenum;
		etgen(nil);
	} break;
case 207:
#line	1135	"cc.y"
{
		en.tenum = T;
		en.cenum = T;
	} break;
case 208:
#line	1140	"cc.y"
{
		yyval.type = en.tenum;
		etgen(nil);
	} break;
case 209:
#line	1145	"cc.y"
{
		yyval.type = tcopy(yypt[-0].yyv.sym->type);
	} break;
case 210:
#line	1149	"cc.y"
{
		yyval.type = tcopy(yypt[-0].yyv.sym->type);
	} break;
case 212:
#line	1156	"cc.y"
{
		yyval.lval = typebitor(yypt[-1].yyv.lval, yypt[-0].yyv.lval);
	} break;
case 214:
#line	1163	"cc.y"
{
		yyval.lval = typebitor(yypt[-1].yyv.lval, yypt[-0].yyv.lval);
	} break;
case 215:
#line	1168	"cc.y"
{
		yyval.lval = 0;
	} break;
case 216:
#line	1172	"cc.y"
{
		yyval.lval = typebitor(yypt[-1].yyv.lval, yypt[-0].yyv.lval);
	} break;
case 220:
#line	1183	"cc.y"
{
		doenum(yypt[-0].yyv.sym, Z);
		yypt[-0].yyv.sym->lineno = lineno;
	} break;
case 221:
#line	1188	"cc.y"
{
		doenum(yypt[-2].yyv.sym, yypt[-0].yyv.node);
		yypt[-2].yyv.sym->lineno = lineno;
	} break;
case 224:
#line	1196	"cc.y"
{ yyval.lval = BCHAR; } break;
case 225:
#line	1197	"cc.y"
{ yyval.lval = BSHORT; } break;
case 226:
#line	1198	"cc.y"
{ yyval.lval = BINT; } break;
case 227:
#line	1199	"cc.y"
{ yyval.lval = BLONG; } break;
case 228:
#line	1200	"cc.y"
{ yyval.lval = BSIGNED; } break;
case 229:
#line	1201	"cc.y"
{ yyval.lval = BUNSIGNED; } break;
case 230:
#line	1202	"cc.y"
{ yyval.lval = BFLOAT; } break;
case 231:
#line	1203	"cc.y"
{ yyval.lval = BDOUBLE; } break;
case 232:
#line	1204	"cc.y"
{ yyval.lval = BVOID; } break;
case 233:
#line	1205	"cc.y"
{ yyval.lval = BVLONG|BLONG; } break;
case 234:
#line	1208	"cc.y"
{ yyval.lval = BAUTO; } break;
case 235:
#line	1209	"cc.y"
{ yyval.lval = BSTATIC; } break;
case 236:
#line	1210	"cc.y"
{ yyval.lval = BEXTERN; } break;
case 237:
#line	1211	"cc.y"
{ yyval.lval = BTYPEDEF; } break;
case 238:
#line	1212	"cc.y"
{ yyval.lval = BREGISTER; } break;
case 239:
#line	1215	"cc.y"
{ yyval.lval = BCONSTNT; } break;
case 240:
#line	1216	"cc.y"
{ yyval.lval = BVOLATILE; } break;
case 241:
#line	1220	"cc.y"
{
		yyval.node = new(ONAME, Z, Z);
		if(yypt[-0].yyv.sym->class == CLOCAL)
			yypt[-0].yyv.sym = mkstatic(yypt[-0].yyv.sym);
		yyval.node->sym = yypt[-0].yyv.sym;
		yyval.node->type = yypt[-0].yyv.sym->type;
	} break;
case 242:
#line	1229	"cc.y"
{
		yyval.node = new(ONAME, Z, Z);
		yyval.node->sym = yypt[-0].yyv.sym;
		yyval.node->type = yypt[-0].yyv.sym->type;
	} break;
	}
	goto yystack;  /* stack new state and value */
}
