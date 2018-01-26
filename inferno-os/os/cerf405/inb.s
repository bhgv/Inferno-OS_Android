#include "mem.h"

/*
 * the tlb entry is configured for little-endian access,
 * so byte-reversing loads aren't needed
 */

#define	ISAIO	PHYSPCIIO0

#define	BDNZ	BC	16,0,

TEXT	inb(SB), $0
	OR	$ISAIO, R3
	EIEIO
	MOVBZ	(R3), R3
	RETURN

TEXT	insb(SB), $0
	MOVW	v+4(FP), R4
	MOVW	n+8(FP), R5
	MOVW	R5, CTR
	OR	$ISAIO, R3
	SUB	$1, R4
insb1:
	EIEIO
	MOVBZ	(R3), R7
	MOVBU	R7, 1(R4)
	BDNZ	insb1
	RETURN

TEXT	outb(SB), $0
	MOVW	v+4(FP), R4
	OR	$ISAIO, R3
	EIEIO
	MOVB	R4, (R3)
	RETURN

TEXT	outsb(SB), $0
	MOVW	v+4(FP), R4
	MOVW	n+8(FP), R5
	MOVW	R5, CTR
	OR	$ISAIO, R3
	SUB	$1, R4
outsb1:
	EIEIO
	MOVBZU	1(R4), R7
	MOVB	R7, (R3)
	BDNZ	outsb1
	RETURN

TEXT	ins(SB), $0
	OR	$ISAIO, R3
	EIEIO
	MOVHZ	(R3), R3
	RETURN

TEXT	inss(SB), $0
	MOVW	v+4(FP), R4
	MOVW	n+8(FP), R5
	MOVW	R5, CTR
	OR	$ISAIO, R3
	SUB	$2, R4
inss1:
	EIEIO
	MOVHZ	(R3), R7
	MOVHU	R7, 2(R4)
	BDNZ	inss1
	RETURN

TEXT	outs(SB), $0
	MOVW	v+4(FP), R4
	OR	$ISAIO, R3
	EIEIO
	MOVH	R4, (R3)
	RETURN

TEXT	outss(SB), $0
	MOVW	v+4(FP), R4
	MOVW	n+8(FP), R5
	MOVW	R5, CTR
	OR	$ISAIO, R3
	SUB	$2, R4
outss1:
	EIEIO
	MOVHZU	2(R4), R7
	MOVH	R7, (R3)
	BDNZ	outss1
	RETURN

TEXT	inl(SB), $0
	OR	$ISAIO, R3
	EIEIO
	MOVW	(R3), R3
	RETURN

TEXT	insl(SB), $0
	MOVW	v+4(FP), R4
	MOVW	n+8(FP), R5
	MOVW	R5, CTR
	OR	$ISAIO, R3
	SUB	$4, R4
insl1:
	EIEIO
	MOVW	(R3), R7
	MOVWU	R7, 4(R4)
	BDNZ	insl1
	RETURN

TEXT	outl(SB), $0
	MOVW	v+4(FP), R4
	OR	$ISAIO, R3
	EIEIO
	MOVW	R4, (R3)
	RETURN

TEXT	outsl(SB), $0
	MOVW	v+4(FP), R4
	MOVW	n+8(FP), R5
	MOVW	R5, CTR
	OR	$ISAIO, R3
	SUB	$4, R4
outsl1:
	EIEIO
	MOVWU	4(R4), R7
	MOVW	R7, (R3)
	BDNZ	outsl1
	RETURN
