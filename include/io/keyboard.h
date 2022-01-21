/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#pragma once



#include <stdint.h>
#include <stddef.h>
#include <libc/string.h>
#include <io/ports.h>


void keyboard_handler();
void keyboard_init();    // Init keyboard function
void keyboard_handler_main();    // Main keyboard function
char getc();                     // Get an a Char from keyboard
char *gets();                    // Get an a String from keyboard

void keyboard_handler(/* struct regs *r */) {
    asm("hlt");
}


char keyboard_scancodes[] = {
    '0'
}