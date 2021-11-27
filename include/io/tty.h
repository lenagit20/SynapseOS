/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#pragma once


#include <kernel.h>


#define COLS 80;                  // Screen width
#define ROWS 25;                  // Screen height
#define SCREEN_SIZE COLS * ROWS;         // Screen height


extern uint16_t* terminal_buffer; // VGA buffer for terminal

// Cursor positions
extern int col;                   // Column (80 max)
extern int row;                   // Row (25 max)


void clean_screen();              // Clean screen function
void putc(const char c);          // Write a char function
void puts(const char c[]);        // Write a string function