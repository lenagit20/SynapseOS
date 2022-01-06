/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#include <io/CMOS.h>
#include <io/ports.h>


/*
    CMOS_get - is used for get value from CMOS

    register_number - the number of register 6-0

    Порт 0x70 (W) - индекс выбора регистра CMOS.
        бит 7 - на время чтения/записи данных отключается NMI.
        биты 6-0 - индекс регистра.
*/
int CMOS_get(int register_number) {   
    port_outb(0x70, register_number);

    return port_inb(0x71); 
}
