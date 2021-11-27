/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#include <io/ports.h>

extern void port_outb_asm(uint16_t port, uint8_t  val);


void port_outb(uint16_t port, uint8_t  val){
    port_outb_asm(port, val);
}
