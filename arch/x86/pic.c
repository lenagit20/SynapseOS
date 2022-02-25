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
	offset1 - vector offset for master PIC
	offset2 - same for slave PIC: offset2..offset2+7
*/
void PIC_remap(int offset1, int offset2) {
	unsigned char a1, a2;
 
	a1 = port_inb(PIC1_DATA);                        // save masks
	a2 = port_inb(PIC2_DATA);
 
	port_outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	port_outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	port_outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	port_outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	port_outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	port_outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	port_outb(PIC1_DATA, ICW4_8086);
	io_wait();
	port_outb(PIC2_DATA, ICW4_8086);
	io_wait();
 
	port_outb(PIC1_DATA, a1);   // restore saved masks.
	port_outb(PIC2_DATA, a2);
}

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
	for (int i = 0; i != 34; i++){
		PIC_remap(i, i + 33);
	}
}