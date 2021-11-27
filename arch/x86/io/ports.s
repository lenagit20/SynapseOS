.code32

.type port_outb_asm, @function

.global port_outb_asm

.intel_syntax noprefix
port_outb_asm:
    push    ebp
    mov     ebp, esp
    sub     esp, 8
    mov     edx, [ebp+arg_0]
    mov     eax, [ebp+arg_4]
    mov     [ebp+port], dx
    mov     [ebp+val], al
    mov     eax, [ebp+val]
    mov     edx, [ebp+port]
    out     dx, al
    nop
    ret

