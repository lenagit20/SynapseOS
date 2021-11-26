/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#ifndef TTY_H
#define TTY_H


#include <kernel.h>

#define cols 80; // Screen width
#define rows 25; // Screen height

// VGA buffer for terminal
uint16_t* terminal_buffer = (uint16_t*) 0xC03FF000;


// Cursor positions
int col;
int row;



#endif