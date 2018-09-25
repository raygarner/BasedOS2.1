//defines global symbols _init and _fini. these symbols cause 
//the linker to emit DT_INIT and DT_FINI

.section .init
.global _init
.type _init, @function
_init:
	push %ebp
	movl %esp, %ebp
	/* gcc will put the contents of crtbegin.o's .init section here. */

.section .fini
.global _fini
.type _fini, @function
_fini:
	push %ebp
	movl %esp, %ebp
	/* gcc will put the contents of crtbegin.o's .fini section here. */
