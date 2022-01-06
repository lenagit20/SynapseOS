/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#include <kernel.h>



/*
    kernel_main is the main function of the kernel. 
    It initializes the core modules and the main cycle has been declared.
*/
void kernel_main() {
    clean_screen();


    puts("SynapseOS 0.0.1");
    puts("10 * 10 = ");
    putint(100);

    puts("CMOS_get Seconds = ");
    putint(CMOS_get(0x00));
    puts("CMOS_get Minuts = ");
    putint(CMOS_get(0x02));
    puts("CMOS_get Hour = ");
    putint(CMOS_get(0x04));
    puts("CMOS_get Day = ");
    putint(CMOS_get(0x07));
    puts("CMOS_get Month = ");
    putint(CMOS_get(0x08));
    puts("CMOS_get Year = ");
    putint(CMOS_get(0x09));
    

    while(1);
}