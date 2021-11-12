.intel_syntax noprefix

.extern interrupt_handler


.macro no_error_code_handler idt_index
.global interrupt_handler_\idt_index
interrupt_handler_\idt_index:
    cli
    push 0
    push \idt_index
    jmp  common_interrupt_handler
.endm

.macro error_code_handler idt_index
.global interrupt_handler_\idt_index
interrupt_handler_\idt_index:
    cli
    push \idt_index
    jmp  common_interrupt_handler
.endm



.section '.text' executable


# the common parts of the generic interrupt handler             
common_interrupt_handler:
	# save the registers
	push    eax
	push    ebx
	push	ecx
	push	edx
	push	ebp
	push	esi
	push	edi

	# call the C function
	call    interrupt_handler

	# restore the registers
	pop	edi
	pop	esi
	pop	ebp
	pop	edx
	pop	ecx
	pop	ebx
	pop     eax

	# restore the esp
	add     esp, 8

	# return to the code that got interrupted
	iret

# create handler for interrupt 1 (keyboard)
no_error_code_handler 33
# create handler for interrupt 2 (paging)
error_code_handler 14
