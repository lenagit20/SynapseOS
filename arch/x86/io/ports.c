/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#include <io/ports.h>


/*
    port_outb is a feature shell for the Assembly instruction with the same name used,
    to communicate with devices associated with ports.

    uint16_t port - port
    val - value
*/
void port_outb(uint16_t port, uint8_t  val){
    asm volatile( "outb %0, %1" : : "a"(val), "Nd"(port) );
}


/*
    port_inb is a feature shell for the Assembly instruction with the same name used,
    to communicate with devices associated with ports.

    uint16_t port - port
*/
uint8_t port_inb(uint16_t port){
    uint8_t ret;

    asm volatile( "inb %1, %0" : "=a"(ret) : "Nd"(port) );

    return ret;
}