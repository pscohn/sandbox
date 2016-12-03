	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	L_.str(%rip), %rax
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rax, %rdi
	callq	_puts
	movl	%eax, -20(%rbp)         ## 4-byte Spill
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	leaq	L_.str.1(%rip), %rdi
	callq	_puts
	movl	$1, %edi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	callq	_sleep
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	jmp	LBB0_1
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Begin"

L_.str.1:                               ## @.str.1
	.asciz	"hi"


.subsections_via_symbols
