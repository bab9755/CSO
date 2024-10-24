
	.section	__TEXT,__text,regular,pure_instructions
	.globl	_exponent
	.p2align	4, 0x90

	# This function takes three parameters:
	#   -- a 32-bit integer x in the %edi register
	#   -- a 32-bit integer y in the %esi register	
	#   -- a 32-bit integer n in the %edx register
	# It returns x^n + y^n, that is, x to the nth power plus y to the nth power.
	# The return value, being 32 bits, must be placed in the %eax register.
	
_exponent:	

	# Note: You can overwrite the 64-bit registers %rax, %rcx, %rdx, %rsi, %rdi, %r8,
	# %r9, %r10, %r11 (as well as their 32-bit halves, %eax, %ecx,
	# %edx, %esi, %edi, %r8d, %r9d, %r10d, %r11d) as you like. These are
	# "caller-saved" registers.
	
	pushq	%rbp	     # LEAVE THIS ALONE
	movq	%rsp, %rbp   # LEAVE THIS ALONE

	/* FILL THIS IN */   # use the 32-bit register %eax to hold x^n, initially 1
	                     # 
	mov $1, %eax

	
        /* FILL THIS IN */   # use a 32-bit register to hold y^n, initially 1
	mov $1, %ebx
	/* FILL THIS IN	*/   # use a 32-bit register to hold i, initially 0
	mov $0, %ecx
LOOP_TOP:
	
        /* FILL THIS IN	*/   # compare i to n (remember, the comparison appears reversed)
	
        /* FILL THIS IN	*/   # and if i is greater or equal to n, jump to DONE
	cmp %edx, %ecx
	jge DONE
        /* FILL THIS IN	*/   # multiply register holding x^n by x
        /* FILL THIS IN	*/   # multiply register holding y^n by y
	imul %eax, %edi
	imul %ebx, %esi 
        /* FILL THIS IN	*/   # i++
	inc %ecx
        /* FILL THIS IN	*/   # jump to LOOP_TOP
	jmp LOOP_TOP
DONE:
        /* FILL THIS IN	*/   # add y^n to x^n
		add %ebx, %eax
        		     # Since the result is already in %eax, just leave it there

	popq	%rbp	     # LEAVE THIS ALONE
	retq                 # LEAVE THIS ALONE

	
