/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#include <drivers/floppy.h>


void floppy_detect_drives() {

   port_outb(0x70, 0x10);
   unsigned drives = port_inb(0x71);

   putsln(" - Floppy drive 0: %s\n", drive_types[drives >> 4]);
   putsln(" - Floppy drive 1: %s\n", drive_types[drives & 0xf]);

}



void test_floppy(){
    floppy_detect_drives();
}