section .text
global main_asm
main_asm:
	push RBX
	xor rbx, rbx

.loop:
	cmp RBX, RDI
	jge .done

	;load x coordinates and subtract them
	movss xmm0, dword [RDX + RBX * 4]
	subss xmm0, dword [RSI + RBX * 4]

	;load y coordinates and subtract them
	movss xmm1, dword [R8 + RBX * 4]
	subss xmm1, dword [RCX + RBX * 4]

	;square
	mulss xmm0, xmm0 ;(dx)^2
	mulss xmm1, xmm1 ;(dy)^2

	;add 
	addss xmm0, xmm1

	;sqrt
	sqrtss xmm0, xmm1

	;store in z
	movss dword [R9 + RBX * 4], xmm0

	inc RBX
	jmp .loop

.done:
	pop RBX
	ret