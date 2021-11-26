/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#pragma once


#include <kernel.h>
#include <stddef.h>


#define cols 80; // Screen width
#define rows 25; // Screen height


// VGA buffer for terminal
extern uint16_t* terminal_buffer;

// Cursor positions
extern int col;
extern int row;


void clean_screen();
void putc(const char c);