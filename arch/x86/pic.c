/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Apache-2.0 License.
*/


#include <idt.h>
#include <io/tty.h>
#include <io/ports.h>
#include <io/keyboard.h>
#include <exceptions.h>


/*
    disable_pic - is used to disable the PIC
*/
void disable_pic() {
	asm volatile("mov %ax, 0xff");

	port_outb(0xA1, 0xFF); // out 0xa1, al
	port_outb(0x21, 0xFF); // out 0x21, al
}


/*

*/
void init_pic() {

}