/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#include <io/tty.h>
#include <libc/string.h>


uint16_t* terminal_buffer = (uint16_t*) 0xC03FF000; // VGA memory adress

int col;
int row;


void clean_screen(){
    for (int i = 0; i < 2000; i++){
        terminal_buffer[i] = 0;
    }

    col = 0;
    row = 0;
}


void putc(const char c){
    if (++col == 81){
        col = 0;
        if (++row == 26){
            row = 25;
        }
    }
    const size_t index = row * 80 + col;
    terminal_buffer[index] = (uint16_t) c | (uint16_t) 15 << 8;
}

void puts(const char c[]){
    for (int i = 0; i < strlen(c); i++){
        putc(c[i]);
    } 
}