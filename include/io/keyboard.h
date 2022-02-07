/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#pragma once



#include <stdint.h>
#include <stddef.h>
#include <libk/string.h>
#include <io/tty.h>
#include <io/ports.h>


#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define ENTER_KEY_CODE 0x1C

extern unsigned char keyboard_map[128];

void keyboard_handler();
void keyboard_init();    // Init keyboard function
void keyboard_handler_main();    // Main keyboard function
char getc();                     // Get an a Char from keyboard
char *gets();                    // Get an a String from keyboard




char keyboard_scancodes[] = {
    '0'
};