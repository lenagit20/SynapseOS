/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Apache-2.0 License.
*/


#pragma once



#include <stdint.h>
#include <stddef.h>
#include <libk/string.h>
#include <io/ports.h>


void timer_int_handler();
void init_interrupts();
void set_int_handler(uint8_t index, void *handler, uint8_t type);