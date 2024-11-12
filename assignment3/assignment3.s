	.text
	.globl	_NAME
	
_NAME:

	# For Unix (including MacOS and Linux), the calling convention
	# is that the first six integer/pointer parameters (in order): %rdi,
	# %rsi, %rdx, %rcx, %r8, %r9 (or their 32-bit halves %edi, %rsi, etc.
	# for 32-bit parameters). The rest of the parameters will have been
	# pushed onto the stack in reverse (right to left) order. The return
	# value is put into %rax (or  %eax for a 32-bit return value).

	# You can overwrite the 64-bit "caller-saved" registers %rax, %rcx,
	# %rdx, %rsi, %rdi, %r8, %r9, %r10, and %r11, as well as their 32-bit
	# halves, %eax, %ecx, %edx, %esi, %edi, %r8d, %r9d, %r10d, %r11d.

	# The "callee-saved registers", which, if used, must be saved before
	# the first use and restored after the last use, are %rbx, %r12, %r13,
	# %r14, and %r15, as well as their 32-bit halves, %ebx, %r12d, %r13d,
	# %r14d, and %r15d.

	pushq	%rbp         
	movq	%rsp, %rbp   

	#INSERT CODE HERE

	popq	%rbp   
	retq           

