/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#include <io/keyboard.h>



void keyboard_handler(/* struct regs *r */) {
    asm("hlt");
}

void keyboard_init(void) {
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	port_outb(0x21 , 0xFD);
}

void keyboard_handler_main(void) {
	unsigned char status;
	char keycode;

	/* write EOI */
	port_outb(0x20, 0x20);

	status = port_inb(KEYBOARD_STATUS_PORT);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = port_inb(KEYBOARD_DATA_PORT);
		if(keycode < 0)
			return;

		if(keycode == -20) {
			putchar('\n');
			return;
		}

    putchar(keyboard_map[(unsigned char) keycode]);
    //qemu_printf("key = %c (index %d)\n", keyboard_map[(unsigned char) keycode], (unsigned char) keycode);
	}
}