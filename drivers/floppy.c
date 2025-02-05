/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Apache-2.0 License.
*/

#include <drivers/floppy.h>


void floppy_detect_drives() {

   port_outb(0x70, 0x10);
   unsigned drives = port_inb(0x71);

   putsln("Floppy drives:");
   puts(" - Floppy drive 0: ");
   putsln(drive_types[drives >> 4]);
   puts(" - Floppy drive 1: ");
   putsln(drive_types[drives & 0xf]);

}



void test_floppy(){
    floppy_detect_drives();
}