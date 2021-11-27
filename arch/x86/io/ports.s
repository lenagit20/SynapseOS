.code32

.type port_outb, @function

.global port_outb

port_outb:
    push    ebp
    mov     ebp, esp
    sub     esp, 8
    mov     edx, [ebp+arg_0]
    mov     eax, [ebp+arg_4]
    mov     [ebp+port], dx
    mov     [ebp+val], al
    movzx   eax, [ebp+val]
    movzx   edx, [ebp+port]
    out     dx, al
    nop
    ret

