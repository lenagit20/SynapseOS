/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#pragma once


#include <gdt.h>
#include <idt.h>
#include <io/tty.h>
#include <io/ports.h>
#include <io/CMOS.h>
#include <io/keyboard.h>
#include <libk/stdlib.h>
#include <lang0x42.h>


void kernel_main();