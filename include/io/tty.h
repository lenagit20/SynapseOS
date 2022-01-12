/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#pragma once


#include <stdint.h>
#include <stddef.h>


#define COLS 80                                 // Screen width
#define ROWS 25                                 // Screen height
#define SCREEN_SIZE COLS * ROWS                 // Screen height


enum Colors {
    black = 0,
    blue = 1,
    green = 2,
    cyan = 3,
    red = 4,
    purple = 5,
    brown = 6,
    gray = 7,
    dark_gray = 8,
    light_blue = 9,
    light_green = 10,
    light_cyan = 11,
    light_red = 12,
    light_purple = 13,
    yellow = 14,
    white = 15,
};


void update_cursor(size_t row, size_t col);     // Move cursor function
void clean_screen();                            // Clean screen function
void set_color(uint8_t new_color);              // Change terminal color function
void putchar(const char c);                     // Write a char function
void puts(const char c[]);                      // Write a string function
void putint(const int i);                       // Write an integer function