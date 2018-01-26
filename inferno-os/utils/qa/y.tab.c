
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
#define YYEOFCODE 1
#define YYERRCODE 2
short	yyexca[] =
{-1, 1,
	1, -1,
	-2, 0,
};
#define	YYNPROD	192
#define	YYPRIVATE 57344
#define	yydebug	1
#define	YYLAST	920
short	yyact[] =
{
  47,  53,  92, 107, 442, 283, 177,  56, 110,  51,
  99, 453,  87,  55,  57, 288, 100, 102, 103, 105,
 106,  54,  58, 119,  76,  97,  77,  99, 127, 129,
 131,   2, 133, 135,  66, 138, 151, 142,  76,  63,
  77, 466,  64, 114,  76, 465,  77,  61,  61,  61,
  63, 454, 121,  64, 432, 431, 421, 108, 115,  97,
  99,  52, 420, 401, 397,  76,  61,  77, 400, 212,
 422, 140, 386, 375, 145, 145,  98, 101,  97, 104,
 385,  50, 384,  97, 120, 287, 383, 137, 382, 143,
 128, 381, 147, 380,  93,  96, 167, 141, 122, 379,
  49,  99, 377, 171, 376, 123, 124, 125, 126, 332,
 211, 212,  89,  91,  95, 298, 139, 212, 181, 182,
 183, 165, 206, 213, 214, 238, 172, 176, 175, 174,
 173, 132, 168, 134, 136, 205, 196, 462, 461, 150,
 152, 233, 460, 459, 458, 457, 413, 412, 410, 409,
 209, 408, 407, 406, 254, 263, 264, 405, 404, 272,
 274, 259, 278, 279, 280, 281, 267, 262, 260, 403,
 402, 396, 216, 395, 276, 258, 261, 394, 393, 270,
 240, 241, 275, 277, 392, 302, 305, 306, 391, 390,
  61, 231, 232,  61, 235, 236, 389, 374, 319, 321,
 323, 325, 327, 328, 373, 290, 237, 122, 330, 291,
 292, 293, 295, 297, 230, 257, 300, 301, 268, 334,
 337,  61, 234, 348, 350, 351, 352,  61, 354, 229,
 358, 333, 316, 228, 227, 226, 225, 224, 223, 269,
 222, 331, 221, 220, 219, 218, 217, 209, 340, 215,
 210, 204,  82, 464, 256, 203, 202, 266, 201, 318,
 200, 199, 198,  61, 197, 195, 169, 194, 193, 307,
 308, 309, 310, 190, 361, 314, 362,  48,  88,  90,
  79,  82,  81, 189, 349, 304, 188, 187, 111, 355,
 357, 312,  82,  81, 186, 315, 130, 185, 184, 360,
 344, 345, 346, 347, 387,  59, 388, 164, 163,  79,
 162, 161, 191, 170,  78, 160,  80, 159, 158, 157,
  79, 109,  85,  86,  83,  67, 156, 155, 154, 356,
 118, 359, 153,  46,  45,  82,  81,  44,  41,  42,
 363, 364, 365, 366, 367,  80,  43, 370, 371, 372,
 109, 463, 411,  83, 116, 117,  80, 313,  40, 398,
 113, 112, 399,  79,  83, 192,  65,  76, 166,  77,
  67,  63, 273,  63,  64, 118,  64,  82,  81,  63,
 207, 416,  64, 417, 418,  76,  63,  77, 455,  64,
 423, 424, 425, 426, 427, 428, 429,  78, 239,  80,
 430, 369, 299, 166,  62,  79,  94,  83, 368, 433,
 446,   8, 419, 445,  67, 451, 452,  65, 149, 118,
 255, 179, 180, 265, 191, 148, 438, 439, 440,  60,
 285, 284, 286, 108,   1,  72,  76, 209,  77,  78,
  76,  80,  77, 271, 443, 443,  62,  75,  99,  83,
  74, 303, 285, 284, 286,  82,  81, 311, 456, 468,
 469,   0, 471, 472,   0, 414, 415, 144, 146, 441,
 444, 282,   0, 448, 449, 450,   0, 335, 338,   0,
 294, 296,   0,  79, 436, 437, 245, 246, 247,   0,
 171,  63,   0, 353,  64,   0, 178, 470, 179, 180,
   0, 181,   0, 317, 320, 322, 324, 326,  67, 329,
  76, 447,  77, 118,   0,   0,   0,  78, 282,  80,
   0, 342,   0, 343,  62, 473,   0,  83,   0,   0,
   0,   9, 285, 284, 286, 341,   0,   0,  76, 467,
  77,   0,   0,  10,  11,  18,  16,  17,  15,  27,
  20,  21,  12,  23,  26,  24,  25,  22,   0,  34,
  36,   0,  35,  37,  38,  39, 243, 244, 245, 246,
 247,  82,  81, 252, 251, 250, 248, 249, 243, 244,
 245, 246, 247,   0,   0,   0,   6,  30,  31,  33,
  32,  28,  29,   0, 378,  14,  19,  13,   0,  79,
   4,   3,   5,   0,  67,   7,  76,  63,  77,  68,
  64,  65,  85,  86,  70,  69,  73,  84,  71,  82,
  81, 251, 250, 248, 249, 243, 244, 245, 246, 247,
  82,  81,   0,  78,   0,  80,   0,   0,   0,   0,
  62,   0,  66,  83,   0,  82,  81,  79, 289,  82,
  81,   0,  67,   0,  76,   0,  77,  68,  79,   0,
  85,  86,  70,  69,  73,  84,  71, 434,  82,  81,
   0,   0,   0,  79,   0,  82,  81,  79,   0,   0,
  76,  78,  77,  80,  76,   0,  77,   0,  62,   0,
  99,  83, 116, 117,  80,   0,  79,  82,  81, 435,
   0,   0,  83,  79,   0,   0,   0,  78,   0,  80,
  76,  78,  77,  80,  62,  82,  81,  83, 109,   0,
   0,  83,   0,   0,   0,  79,   0,  82,  81,   0,
 116, 117,  80,   0,  82,  81,   0, 339,   0,  80,
  83,   0,   0,  79, 109,  82,  81,  83, 248, 249,
 243, 244, 245, 246, 247,  79,   0,  82,  81, 116,
 117,  80,  79,   0,  82,  81, 336,   0,   0,  83,
   0,   0,   0,  79,   0,   0,   0, 116, 117,  80,
   0,   0,   0,   0, 208,  79,   0,  83, 170,  78,
   0,  80,  79,   0, 313,   0, 109,   0,  80,  83,
   0,   0,   0, 109,   0,   0,  83,   0,   0,  80,
   0,   0,   0,   0, 109,   0,  99,  83,   0,  78,
   0,  80,   0,   0,   0,   0, 109,   0,  80,  83,
   0,   0,   0, 109,   0,   0,  83, 252, 251, 250,
 248, 249, 243, 244, 245, 246, 247, 252, 251, 250,
 248, 249, 243, 244, 245, 246, 247,  67,   0,   0,
   0,   0, 118,   0,   0,   0,   0,  70,  69,   0,
  84,  71, 250, 248, 249, 243, 244, 245, 246, 247,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0, 253,
   0,   0,   0,   0,   0,   0,   0,   0,   0, 242
};
short	yypact[] =
{
-1000, 529,-1000, 284, 264, 271, 261,-1000, 258, 257,
 562, 636, 326,   5, -70, -20, 396, -20, 396, 396,
 755, 283,  21, 334, 334, 334, 334, 396, -20, 640,
 -19, 396,   0, -19,  -6, -46, 130, 748, 748, 130,
-1000,-1000, 755, 755,-1000,-1000,-1000, 255, 251, 250,
 249, 242, 241, 240, 238, 234, 233, 231, 230,-1000,
-1000,  43, 666,-1000,  54,-1000, 718,-1000,  48,-1000,
  52,  51,-1000,  50,-1000,-1000,-1000,  49, 489,-1000,
-1000, 755, 755, 755,-1000,-1000,-1000, 221, 220, 217,
 210, 209, 206, 196, 355, 191, 190, 396, 188, 755,
 187, 185, 184, 183, 181, 179, 178, 174,-1000, 755,
-1000,-1000, 272, 706, 173,  33, 489, 412,  48, 172,
 169,-1000,-1000, 168, 167, 166, 165, 163, 161, 160,
 159, 158, 157, 156, 152, 137,-1000,-1000, 130, 130,
 341, 130, 130,-1000, 129,  47, 386,-1000, 529, 529,
 843,-1000, 833, 610, 396, 396, 368, 328, 323, 396,
 815, 466, 396, 396, 396, 392,   6, 569, 755,-1000,
-1000,  43, 755, 755, 666, 666, 755,  37, 394, 755,
 755,-1000,-1000,-1000, 636, 396, 396, 334, 334, 334,
 446,-1000, 288, 334, -19, 755,-1000, -20, 396, 396,
 396, 396, 396, 396, 755,  30,-1000,-1000, 272,  39,
 688, 659, 494,  37,-1000, 396,-1000, 396, 334, 334,
 334, 334, -20, 396, 396, 396, 748, -20, -53, 396,
 -19,-1000,-1000,-1000,-1000,-1000,-1000, 736, 414, 755,
-1000,-1000,-1000, 755, 755, 755, 755, 755, 401, 393,
 755, 755, 755,-1000,-1000,-1000,-1000, 127,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000, 120,-1000,
-1000,-1000,-1000,  -5,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,  25,  23,-1000,-1000,-1000,-1000, 396,-1000,
  20,  14,  12,   9,   7,   3,   1,  -7, 414, 412,
-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000, 119, 112,-1000,
 111,-1000, 107,-1000, 101,-1000, 100,-1000,-1000,  96,
-1000,  94,-1000, -15,-1000,-1000, 272,-1000,-1000, 272,
  -9, -16,-1000,-1000,-1000,  93,  92,  81,  80,  76,
  75,  74,-1000,-1000,-1000,  72,-1000,  71,-1000,-1000,
 278,  70,  69, 475, 475,-1000,-1000,-1000, 755, 755,
 741, 866, 616, 336, 317, 755,-1000,-1000, -17,-1000,
-1000,-1000,-1000,-1000,-1000,-1000,-1000, -23,  -8, 396,
 396, 396, 396, 396, 396, 396, 755,-1000, -24, -25,
 621,-1000, 334, 334, 372, 372, 372, 736, 736, 396,
 -19, -70, -70, -69, 557, 557,-1000,-1000,-1000, -28,
-1000,-1000, 349,-1000,-1000,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000,-1000, 272,-1000,  68,-1000,-1000,
-1000,  67,  66,  65,  61,  60,-1000,-1000,-1000, 277,
-1000,-1000,-1000, 243,-1000, -34, -38, 334, 396, 396,
 755, 396, 396, -70, 725,-1000,-1000,-1000,-1000,-1000,
-1000,-1000,-1000,-1000
};
short	yypgo[] =
{
   0,  36,  96,   5,   6, 305, 266,   0, 100, 429,
  21,  81,  22, 450, 447,  61,   1,   2,   8,  13,
   7,   3,   9, 443,  14, 435,   4, 434,  31, 425,
 418, 411,  52
};
short	yyr1[] =
{
   0,  27,  27,  29,  28,  30,  28,  28,  28,  28,
  28,  28,  28,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  31,  31,  31,  31,
  31,  31,  31,  31,  31,  31,  31,  31,  18,  18,
  18,   7,  12,  12,  13,  20,  14,  25,  19,  19,
  19,  19,  19,  24,  24,  22,  23,  11,  11,  10,
  10,  21,  26,  16,  16,  17,  17,  15,   5,   5,
   8,   8,   6,   6,   9,   9,   9,  32,  32,   4,
   4,   4,   3,   3,   3,   1,   1,   1,   1,   1,
   1,   2,   2,   2,   2,   2,   2,   2,   2,   2,
   2,   2
};
short	yyr2[] =
{
   0,   0,   2,   0,   4,   0,   4,   4,   4,   2,
   1,   2,   2,   4,   4,   4,   4,   4,   4,   4,
   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
   4,   4,   4,   4,   4,   6,   4,   4,   4,   6,
   4,   4,   6,   6,   6,   4,   4,   6,   4,   6,
   4,   6,   4,   4,   2,   6,   4,   4,   4,   6,
   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
   2,   2,   4,   3,   3,   5,   4,   4,   6,   4,
   4,   6,   6,   6,   8,   4,   4,   3,   2,   4,
   4,   6,   8,   4,   6,   4,   4,   6,   6,   8,
   8,   8,   8,   4,   4,   4,   6,   4,   6,   4,
   4,   2,   2,   3,   3,   3,   3,   3,   3,   2,
   4,   6,   6,   8,   6,   6,   6,   2,   4,   2,
   2,   1,   1,   1,   1,   1,   1,   1,   1,   4,
   4,   4,   1,   4,   4,   1,   4,   1,   4,   1,
   4,   1,   3,   2,   2,   2,   3,   2,   1,   4,
   3,   5,   1,   4,   4,   5,   7,   0,   1,   0,
   2,   2,   1,   1,   1,   1,   1,   2,   2,   2,
   3,   1,   3,   3,   3,   3,   3,   4,   4,   3,
   3,   3
};
short	yychk[] =
{
-1000, -27, -28,  72,  71,  73,  57,  76, -31,   2,
  14,  15,  23,  68,  66,  19,  17,  18,  16,  67,
  21,  22,  28,  24,  26,  27,  25,  20,  62,  63,
  58,  59,  61,  60,  30,  33,  31,  34,  35,  36,
  74,  74,  75,  75,  76,  76,  76,  -7,  -6,  -8,
 -11, -22, -15, -16, -10, -19, -20, -24, -12,  -5,
  -9,  -1,  78,  45,  48,  49,  80,  42,  47,  53,
  52,  56, -25,  54, -13, -14,  44,  46,  71,  37,
  73,  10,   9,  81,  55,  50,  51,  -7,  -6,  -8,
  -6,  -8, -17, -11,  80,  -8, -11,  78, -15,  80,
  -7, -15,  -7,  -7, -15,  -7,  -7, -21,  -1,  78,
 -18,  -6,  78,  77, -10,  -1,  71,  72,  47,  -7,
 -15, -32,  77, -11, -11, -11, -11,  -7, -15,  -7,
  -6,  -7,  -8,  -7,  -8,  -7,  -8, -32,  -7, -11,
  77, -15, -16, -32,  -9,  -1,  -9, -32, -29, -30,
  -2,  -1,  -2,  77,  77,  77,  77,  77,  77,  77,
  77,  77,  77,  77,  77,  78,  -5,  -2,  78,  -6,
  70,  -1,  78,  78,  78,  78,  78,  -4,   7,   9,
  10,  -1,  -1,  -1,  77,  77,  77,  77,  77,  77,
  77,  69,  10,  77,  77,  77,  -1,  77,  77,  77,
  77,  77,  77,  77,  77, -12, -18,  -6,  78,  -1,
  77,  77,  78,  -4,  -4,  77, -32,  77,  77,  77,
  77,  77,  77,  77,  77,  77,  77,  77,  77,  77,
  77, -32, -32,  -7, -11, -32, -32,  77,  78,  12,
 -28, -28,  76,   9,  10,  11,  12,  13,   7,   8,
   6,   5,   4,  76,  -7,  -6,  -8, -15, -10, -20,
 -24, -12, -19,  -7,  -7,  -6,  -8, -22, -15, -11,
 -10, -23,  -7,  49,  -7, -10, -19, -10,  -7,  -7,
  -7,  -7,  -5,  -3,  39,  38,  40,  79,   9,  79,
  -1,  -1,  -1,  -1,  -5,  -1,  -5,  -1,  78,   8,
  -1,  -1,  -7,  -6,  -8,  -7,  -7, -11, -11, -11,
 -11,  -6,  -8,  69, -11,  -8,  -1,  -5, -15,  -7,
  -5,  -7,  -5,  -7,  -5,  -7,  -5,  -7,  -7,  -5,
 -21,  -1,  79, -12, -18,  -6,  78, -18,  -6,  78,
  -1,  41,  -5,  -5, -11, -11, -11, -11,  -7, -15,
  -7,  -7,  -7,  -6,  -7, -15,  -8, -15,  -7,  -8,
 -15,  -1,  -1,  -2,  -2,  -2,  -2,  -2,   7,   8,
  -2,  -2,  -2,  77,  77,  78,  79,  79,  -5,  79,
  79,  79,  79,  79,  79,  79,  79,  -3,  -4,  77,
  77,  77,  77,  77,  77,  77,  77,  79, -12, -12,
  77,  79,  77,  77,  77,  77,  77,  77,  77,  77,
  77,  74,  77,  77,  -2,  -2, -20,  47, -22,  -1,
  79,  79,  78,  -7,  -7,  -7,  -7,  -7,  -7,  -7,
 -21,  79,  79, -18,  -6,  78, -11, -11, -10, -10,
 -10, -15, -26,  -1, -15, -26,  -7,  -8, -15, -15,
 -15, -16, -17,  80,  79,  39, -12,  77,  77,  77,
  77,  77,  77,  74,  10,  79,  79, -11,  -7,  -7,
  -1,  -7,  -7, -15
};
short	yydef[] =
{
   1,  -2,   2,   0,   0,   0,   0,  10,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0, 167,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0, 167,   0, 167,   0,   0, 167,
   3,   5,   0,   0,   9,  11,  12,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0, 131,
 162,   0,   0, 147,   0, 145,   0, 149, 135, 138,
   0,   0, 142,   0, 132, 133, 158,   0, 169, 175,
 176,   0,   0,   0, 137, 134, 136,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,  54,   0,   0, 151,   0,
  70,  71,   0,   0,   0,   0, 169, 169,   0, 167,
   0,  88, 168,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0, 111, 112, 167, 167,
 168, 167, 167, 119,   0,   0,   0, 127,   0,   0,
   0, 181,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0, 153,
 154, 157,   0,   0,   0,   0,   0,   0,   0,   0,
   0, 177, 178, 179,   0,   0,   0,   0,   0,   0,
   0, 155,   0,   0,   0,   0, 157,   0,   0,   0,
   0,   0,   0,   0,   0,   0,  73,  74,   0,   0,
   0,   0,   0, 129, 130, 168,  87,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0, 113, 114, 115, 116, 117, 118,   0,   0,   0,
   4,   6,   7,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   8,  13,  27,  28,   0,  40,  41,
  65,  67,  69,  14,  15,  31,  32,  34,   0,  33,
  36,  37,  56,   0,  57,  60,  68,  61,  63,  62,
  64,  66,   0,   0, 172, 173, 174, 160,   0, 180,
   0,   0,   0,   0,   0,   0,   0,   0,   0, 169,
 170, 171,  16,  29,  30,  17,  18,  19,  20,  21,
  22,  23,  24, 156,  25,  26,  38, 131,   0,  45,
 131,  46, 131,  48, 131,  50, 131,  52,  53,   0,
  58, 151,  72,   0,  76,  77,   0,  79,  80,   0,
   0,   0,  85,  86,  89,  90,   0,  93,  95,  96,
   0,   0, 103, 104, 105,   0, 107,   0, 109, 110,
 120,   0,   0, 182, 183, 184, 185, 186,   0,   0,
 189, 190, 191,   0,   0,   0, 163, 164,   0, 148,
 150, 139, 140, 141, 143, 144, 159,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,  75,   0,   0,
   0, 128,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0, 187, 188,  39, 135,  35,   0,
 161, 165,   0,  42,  44,  43,  47,  49,  51,  55,
  59,  78,  81,  82,  83,   0,  91,   0,  94,  97,
  98,   0,   0,   0,   0,   0, 106, 108, 122, 121,
 124, 125, 126,   0, 146,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0, 166,  84,  92,  99, 100,
 152, 101, 102, 123
};
short	yytok1[] =
{
   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,  80,  13,   6,   0,
  78,  79,  11,   9,  77,  10,   0,  12,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,  74,  76,
   7,  75,   8,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   5,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   4,   0,  81
};
short	yytok2[] =
{
   2,   3,  14,  15,  16,  17,  18,  19,  20,  21,
  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,
  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,
  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,
  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,
  72,  73
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
#line	38	"a.y"
{
		if(yypt[-1].yyv.sym->value != pc)
			yyerror("redeclaration of %s", yypt[-1].yyv.sym->name);
		yypt[-1].yyv.sym->value = pc;
	} break;
case 5:
#line	45	"a.y"
{
		yypt[-1].yyv.sym->type = LLAB;
		yypt[-1].yyv.sym->value = pc;
	} break;
case 7:
#line	51	"a.y"
{
		yypt[-3].yyv.sym->type = LVAR;
		yypt[-3].yyv.sym->value = yypt[-1].yyv.lval;
	} break;
case 8:
#line	56	"a.y"
{
		if(yypt[-3].yyv.sym->value != yypt[-1].yyv.lval)
			yyerror("redeclaration of %s", yypt[-3].yyv.sym->name);
		yypt[-3].yyv.sym->value = yypt[-1].yyv.lval;
	} break;
case 9:
#line	62	"a.y"
{
		nosched = yypt[-1].yyv.lval;
	} break;
case 13:
#line	74	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 14:
#line	78	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 15:
#line	82	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 16:
#line	86	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 17:
#line	90	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 18:
#line	94	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 19:
#line	101	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 20:
#line	105	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 21:
#line	109	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 22:
#line	113	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 23:
#line	117	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 24:
#line	121	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 25:
#line	128	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 26:
#line	132	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 27:
#line	139	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 28:
#line	143	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 29:
#line	147	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 30:
#line	151	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 31:
#line	158	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 32:
#line	162	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 33:
#line	169	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 34:
#line	173	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 35:
#line	177	"a.y"
{
		outgcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, NREG, &yypt[-2].yyv.gen, &yypt[-0].yyv.gen);
	} break;
case 36:
#line	181	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 37:
#line	185	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 38:
#line	189	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, yypt[-0].yyv.lval, &nullgen);
	} break;
case 39:
#line	196	"a.y"
{
		outgcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, NREG, &yypt[-2].yyv.gen, &yypt[-0].yyv.gen);
	} break;
case 40:
#line	200	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 41:
#line	204	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 42:
#line	214	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 43:
#line	218	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 44:
#line	222	"a.y"
{
		outgcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, NREG, &yypt[-2].yyv.gen, &yypt[-0].yyv.gen);
	} break;
case 45:
#line	226	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 46:
#line	230	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 47:
#line	234	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 48:
#line	238	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 49:
#line	242	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 50:
#line	246	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 51:
#line	250	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 52:
#line	254	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 53:
#line	258	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 54:
#line	262	"a.y"
{
		outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 55:
#line	269	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 56:
#line	276	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 57:
#line	280	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 58:
#line	287	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, yypt[-0].yyv.gen.reg, &yypt[-0].yyv.gen);
	} break;
case 59:
#line	291	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 60:
#line	299	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 61:
#line	303	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 62:
#line	307	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 63:
#line	311	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 64:
#line	315	"a.y"
{
		int r;
		r = yypt[-2].yyv.gen.offset;
		yypt[-2].yyv.gen.offset = 0;
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, r, &yypt[-0].yyv.gen);
	} break;
case 65:
#line	322	"a.y"
{
		int r;
		r = yypt[-0].yyv.gen.offset;
		yypt[-0].yyv.gen.offset = 0;
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, r, &yypt[-0].yyv.gen);
	} break;
case 66:
#line	329	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 67:
#line	333	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 68:
#line	337	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 69:
#line	341	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 70:
#line	350	"a.y"
{
		outcode(yypt[-1].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 71:
#line	354	"a.y"
{
		outcode(yypt[-1].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 72:
#line	358	"a.y"
{
		outcode(yypt[-3].yyv.lval, &nullgen, NREG, &yypt[-1].yyv.gen);
	} break;
case 73:
#line	362	"a.y"
{
		outcode(yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 74:
#line	366	"a.y"
{
		outcode(yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 75:
#line	370	"a.y"
{
		outcode(yypt[-4].yyv.lval, &nullgen, NREG, &yypt[-1].yyv.gen);
	} break;
case 76:
#line	374	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 77:
#line	378	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 78:
#line	382	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, NREG, &yypt[-1].yyv.gen);
	} break;
case 79:
#line	386	"a.y"
{
		outcode(yypt[-3].yyv.lval, &nullgen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 80:
#line	390	"a.y"
{
		outcode(yypt[-3].yyv.lval, &nullgen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 81:
#line	394	"a.y"
{
		outcode(yypt[-5].yyv.lval, &nullgen, yypt[-4].yyv.lval, &yypt[-1].yyv.gen);
	} break;
case 82:
#line	398	"a.y"
{
		Gen g;
		g = nullgen;
		g.type = D_CONST;
		g.offset = yypt[-4].yyv.lval;
		outcode(yypt[-5].yyv.lval, &g, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 83:
#line	406	"a.y"
{
		Gen g;
		g = nullgen;
		g.type = D_CONST;
		g.offset = yypt[-4].yyv.lval;
		outcode(yypt[-5].yyv.lval, &g, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 84:
#line	414	"a.y"
{
		Gen g;
		g = nullgen;
		g.type = D_CONST;
		g.offset = yypt[-6].yyv.lval;
		outcode(yypt[-7].yyv.lval, &g, yypt[-4].yyv.lval, &yypt[-1].yyv.gen);
	} break;
case 85:
#line	425	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, yypt[-0].yyv.lval, &nullgen);
	} break;
case 86:
#line	429	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, yypt[-0].yyv.lval, &nullgen);
	} break;
case 87:
#line	433	"a.y"
{
		outcode(yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 88:
#line	437	"a.y"
{
		outcode(yypt[-1].yyv.lval, &nullgen, NREG, &nullgen);
	} break;
case 89:
#line	444	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 90:
#line	448	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 91:
#line	452	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.gen.reg, &yypt[-0].yyv.gen);
	} break;
case 92:
#line	456	"a.y"
{
		outgcode(yypt[-7].yyv.lval, &yypt[-6].yyv.gen, yypt[-4].yyv.gen.reg, &yypt[-2].yyv.gen, &yypt[-0].yyv.gen);
	} break;
case 93:
#line	460	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 94:
#line	464	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-0].yyv.gen.reg, &yypt[-2].yyv.gen);
	} break;
case 95:
#line	471	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 96:
#line	475	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 97:
#line	479	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-0].yyv.gen.reg, &yypt[-2].yyv.gen);
	} break;
case 98:
#line	483	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-0].yyv.gen.reg, &yypt[-2].yyv.gen);
	} break;
case 99:
#line	490	"a.y"
{
		outgcode(yypt[-7].yyv.lval, &yypt[-6].yyv.gen, yypt[-4].yyv.gen.reg, &yypt[-2].yyv.gen, &yypt[-0].yyv.gen);
	} break;
case 100:
#line	494	"a.y"
{
		outgcode(yypt[-7].yyv.lval, &yypt[-6].yyv.gen, yypt[-4].yyv.gen.reg, &yypt[-2].yyv.gen, &yypt[-0].yyv.gen);
	} break;
case 101:
#line	498	"a.y"
{
		outgcode(yypt[-7].yyv.lval, &yypt[-6].yyv.gen, yypt[-4].yyv.gen.reg, &yypt[-2].yyv.gen, &yypt[-0].yyv.gen);
	} break;
case 102:
#line	502	"a.y"
{
		outgcode(yypt[-7].yyv.lval, &yypt[-6].yyv.gen, yypt[-4].yyv.gen.reg, &yypt[-2].yyv.gen, &yypt[-0].yyv.gen);
	} break;
case 103:
#line	509	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 104:
#line	513	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 105:
#line	521	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 106:
#line	525	"a.y"
{
		outgcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, NREG, &yypt[-2].yyv.gen, &yypt[-0].yyv.gen);
	} break;
case 107:
#line	529	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 108:
#line	533	"a.y"
{
		outgcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, NREG, &yypt[-2].yyv.gen, &yypt[-0].yyv.gen);
	} break;
case 109:
#line	537	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 110:
#line	541	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 111:
#line	545	"a.y"
{
		outcode(yypt[-1].yyv.lval, &yypt[-0].yyv.gen, NREG, &nullgen);
	} break;
case 112:
#line	552	"a.y"
{
		outcode(yypt[-1].yyv.lval, &nullgen, NREG, &nullgen);
	} break;
case 113:
#line	556	"a.y"
{
		outcode(yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 114:
#line	560	"a.y"
{
		outcode(yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 115:
#line	564	"a.y"
{
		outcode(yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 116:
#line	568	"a.y"
{
		outcode(yypt[-2].yyv.lval, &nullgen, NREG, &yypt[-0].yyv.gen);
	} break;
case 117:
#line	575	"a.y"
{
		outcode(yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 118:
#line	579	"a.y"
{
		outcode(yypt[-2].yyv.lval, &yypt[-1].yyv.gen, NREG, &nullgen);
	} break;
case 119:
#line	586	"a.y"
{
		outcode(yypt[-1].yyv.lval, &nullgen, NREG, &nullgen);
	} break;
case 120:
#line	593	"a.y"
{
		outcode(yypt[-3].yyv.lval, &yypt[-2].yyv.gen, NREG, &yypt[-0].yyv.gen);
	} break;
case 121:
#line	597	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 122:
#line	601	"a.y"
{
		outgcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, NREG, &yypt[-0].yyv.gen, &yypt[-2].yyv.gen);
	} break;
case 123:
#line	605	"a.y"
{
		outgcode(yypt[-7].yyv.lval, &yypt[-6].yyv.gen, yypt[-4].yyv.lval, &yypt[-0].yyv.gen, &yypt[-2].yyv.gen);
	} break;
case 124:
#line	612	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 125:
#line	616	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 126:
#line	620	"a.y"
{
		outcode(yypt[-5].yyv.lval, &yypt[-4].yyv.gen, yypt[-2].yyv.lval, &yypt[-0].yyv.gen);
	} break;
case 127:
#line	627	"a.y"
{
		outcode(yypt[-1].yyv.lval, &nullgen, NREG, &nullgen);
	} break;
case 128:
#line	633	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.offset = yypt[-3].yyv.lval + pc;
	} break;
case 129:
#line	639	"a.y"
{
		yyval.gen = nullgen;
		if(pass == 2)
			yyerror("undefined label: %s", yypt[-1].yyv.sym->name);
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yypt[-1].yyv.sym;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 130:
#line	648	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_BRANCH;
		yyval.gen.sym = yypt[-1].yyv.sym;
		yyval.gen.offset = yypt[-1].yyv.sym->value + yypt[-0].yyv.lval;
	} break;
case 131:
#line	657	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_REG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 134:
#line	669	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SPR;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 135:
#line	677	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_CREG;
		yyval.gen.reg = NREG;	/* whole register */
	} break;
case 136:
#line	685	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SPR;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 137:
#line	693	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_MSR;
	} break;
case 138:
#line	700	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SPR;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 139:
#line	706	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = yypt[-3].yyv.lval;
		yyval.gen.offset = yypt[-1].yyv.lval;
	} break;
case 140:
#line	712	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = yypt[-3].yyv.lval;
		yyval.gen.offset = yypt[-1].yyv.lval;
	} break;
case 141:
#line	718	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = yypt[-3].yyv.lval;
		yyval.gen.reg = yypt[-1].yyv.lval;
		yyval.gen.offset = 0;
	} break;
case 143:
#line	728	"a.y"
{
		if(yypt[-1].yyv.lval < 0 || yypt[-1].yyv.lval > 15)
			yyerror("segment register number out of range");
		yyval.gen = nullgen;
		yyval.gen.type = D_SREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
		yyval.gen.offset = NREG;
	} break;
case 144:
#line	737	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SREG;
		yyval.gen.reg = NREG;
		yyval.gen.offset = yypt[-1].yyv.lval;
	} break;
case 145:
#line	746	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FPSCR;
		yyval.gen.reg = NREG;
	} break;
case 146:
#line	754	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FPSCR;
		yyval.gen.reg = yypt[-1].yyv.lval;
	} break;
case 147:
#line	762	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FREG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 148:
#line	768	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
	} break;
case 149:
#line	776	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_CREG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 150:
#line	782	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_CREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
	} break;
case 151:
#line	790	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_REG;
		yyval.gen.reg = yypt[-0].yyv.lval;
	} break;
case 152:
#line	798	"a.y"
{
		int mb, me;
		ulong v;

		yyval.gen = nullgen;
		yyval.gen.type = D_CONST;
		mb = yypt[-2].yyv.lval;
		me = yypt[-0].yyv.lval;
		if(mb < 0 || mb > 31 || me < 0 || me > 31){
			yyerror("illegal mask start/end value(s)");
			mb = me = 0;
		}
		if(mb <= me)
			v = ((ulong)~0L>>mb) & (~0L<<(31-me));
		else
			v = ~(((ulong)~0L>>(me+1)) & (~0L<<(31-(mb-1))));
		yyval.gen.offset = v;
	} break;
case 153:
#line	819	"a.y"
{
		yyval.gen = yypt[-0].yyv.gen;
		yyval.gen.type = D_CONST;
	} break;
case 154:
#line	824	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_SCONST;
		memcpy(yyval.gen.sval, yypt[-0].yyv.sval, sizeof(yyval.gen.sval));
	} break;
case 155:
#line	832	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = yypt[-0].yyv.dval;
	} break;
case 156:
#line	838	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_FCONST;
		yyval.gen.dval = -yypt[-0].yyv.dval;
	} break;
case 157:
#line	845	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_CONST;
		yyval.gen.offset = yypt[-0].yyv.lval;
	} break;
case 159:
#line	854	"a.y"
{
		if(yyval.lval < 0 || yyval.lval >= NREG)
			print("register value out of range\n");
		yyval.lval = yypt[-1].yyv.lval;
	} break;
case 160:
#line	862	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
		yyval.gen.offset = 0;
	} break;
case 161:
#line	869	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.reg = yypt[-3].yyv.lval;
		yyval.gen.xreg = yypt[-1].yyv.lval;
		yyval.gen.offset = 0;
	} break;
case 163:
#line	880	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.reg = yypt[-1].yyv.lval;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 164:
#line	889	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.name = yypt[-1].yyv.lval;
		yyval.gen.sym = S;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 165:
#line	897	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.name = yypt[-1].yyv.lval;
		yyval.gen.sym = yypt[-4].yyv.sym;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 166:
#line	905	"a.y"
{
		yyval.gen = nullgen;
		yyval.gen.type = D_OREG;
		yyval.gen.name = D_STATIC;
		yyval.gen.sym = yypt[-6].yyv.sym;
		yyval.gen.offset = yypt[-3].yyv.lval;
	} break;
case 169:
#line	917	"a.y"
{
		yyval.lval = 0;
	} break;
case 170:
#line	921	"a.y"
{
		yyval.lval = yypt[-0].yyv.lval;
	} break;
case 171:
#line	925	"a.y"
{
		yyval.lval = -yypt[-0].yyv.lval;
	} break;
case 176:
#line	937	"a.y"
{
		yyval.lval = yypt[-0].yyv.sym->value;
	} break;
case 177:
#line	941	"a.y"
{
		yyval.lval = -yypt[-0].yyv.lval;
	} break;
case 178:
#line	945	"a.y"
{
		yyval.lval = yypt[-0].yyv.lval;
	} break;
case 179:
#line	949	"a.y"
{
		yyval.lval = ~yypt[-0].yyv.lval;
	} break;
case 180:
#line	953	"a.y"
{
		yyval.lval = yypt[-1].yyv.lval;
	} break;
case 182:
#line	960	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval + yypt[-0].yyv.lval;
	} break;
case 183:
#line	964	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval - yypt[-0].yyv.lval;
	} break;
case 184:
#line	968	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval * yypt[-0].yyv.lval;
	} break;
case 185:
#line	972	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval / yypt[-0].yyv.lval;
	} break;
case 186:
#line	976	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval % yypt[-0].yyv.lval;
	} break;
case 187:
#line	980	"a.y"
{
		yyval.lval = yypt[-3].yyv.lval << yypt[-0].yyv.lval;
	} break;
case 188:
#line	984	"a.y"
{
		yyval.lval = yypt[-3].yyv.lval >> yypt[-0].yyv.lval;
	} break;
case 189:
#line	988	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval & yypt[-0].yyv.lval;
	} break;
case 190:
#line	992	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval ^ yypt[-0].yyv.lval;
	} break;
case 191:
#line	996	"a.y"
{
		yyval.lval = yypt[-2].yyv.lval | yypt[-0].yyv.lval;
	} break;
	}
	goto yystack;  /* stack new state and value */
}
