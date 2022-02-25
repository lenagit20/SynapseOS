/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Apache-2.0 License.
*/


#include <idt.h>
#include <io/tty.h>
#include <io/ports.h>
#include <io/keyboard.h>
#include <exceptions.h>


int mode;


struct IDT_entry IDT[IDT_SIZE]; // array of IDT entries


/*
    idt_set_entry adds an interrupt handler to the given address

	adress this is a position in IDT
	interrupt_adress this is the interrupt address

*/
void idt_set_entry(uint8_t adress, uint32_t interrupt_adress, uint16_t selector, uint8_t type_attr) {
    IDT[adress].offset_lowerbits = interrupt_adress  & 0xffff;
    IDT[adress].selector = selector;
    IDT[adress].zero = 0;
    IDT[adress].type_attr = type_attr;
    IDT[adress].offset_higherbits = (interrupt_adress & 0xffff0000) >> 16;
}


/*
    load_idt - is used to load idt
*/
void load_idt(uint32_t idt_ptr[2]);

void floppy_handler(){
	putsln("FLOPPY");
}
/*
    idt_init - is used to provide idt to kernel
*/
void idt_init() {
	uint32_t idt_address;
	uint32_t idt_ptr[2];
	
	
	idt_set_entry(0x0, (uint32_t)divide_by_zero, 0x08, 0x8e);

	init_pic();

	idt_set_entry(0x6, (uint32_t)floppy_handler, 0x08, 0x8e);
	idt_set_entry(0x8, (uint32_t)keyboard_handler, 0x08, 0x8e);

	
	/* populate IDT entry of keyboard's */


	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	port_outb(PIC1 , 0x11);
	port_outb(PIC2 , 0x11);


	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	port_outb(0x21, PIC1);
	port_outb(0xA1, 0x28);

	/* ICW3 - setup cascading */
	port_outb(0x21, 0x00);
	port_outb(0xA1, 0x00);

	/* ICW4 - environment info */
	port_outb(0x21, 0x01);
	port_outb(0xA1, 0x01);
	/* Initialization finished */

	/* mask interrupts */
	port_outb(0x21, 0xff);
	port_outb(0xA1, 0xff);

  
	/* fill the IDT descriptor */
	idt_address = (uint32_t)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;
	
	log_putsln("load_idt");
	load_idt(idt_ptr); // load IDT to special cpu register
}