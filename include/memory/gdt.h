/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#pragma once


#include <stdint.h>


struct idt_ptr {
	unsigned short limit;
	uintptr_t base;
} __attribute__((packed));


// Defines a GDT entry.
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));


struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


struct gdt_entry gdt[6];
struct gdt_ptr gp;


void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void gdt_init();