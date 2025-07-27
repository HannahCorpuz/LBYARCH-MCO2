; assembly part using x86-64
section .data


section .text
bits 64
default rel ; to handle address relocation

global asmhello
extern printf

asmhello:
	SUBSS XMM0, XMM2
	SUBSS XMM1, XMM3

	MOVSS XMM2, XMM0
	MOVSS XMM3, XMM1

	MULSS XMM0, XMM2
	MULSS XMM1, XMM3

	ADDSS XMM0, XMM1

	SQRTSS XMM0, XMM0
	ret
