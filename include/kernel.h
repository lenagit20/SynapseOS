/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Apache-2.0 License.
*/


#pragma once


#include <gdt.h>
#include <idt.h>
#include <io/tty.h>
#include <io/ports.h>
#include <io/CMOS.h>
#include <io/keyboard.h>
#include <drivers/floppy.h>
#include <libk/stdlib.h>
#include <shell.h>
#include <lang0x42.h>


void kernel_main();
extern int alive;