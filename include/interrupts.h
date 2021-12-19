/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#pragma once



#include <stdint.h>
#include <stddef.h>
#include <libc/string.h>


typedef struct {
    uint16_t address_0_15;
    uint16_t selector;
    uint8_t reserved;
    uint8_t type;
    uint16_t address_16_31;
} __attribute__((packed)) IntDesc;


typedef struct {
    uint16_t limit;
    void *base;
} __attribute__((packed)) IDTR;


uint8_t irq_base;
uint8_t irq_count;


void init_interrupts();
void set_int_handler(uint8_t index, void *handler, uint8_t type);