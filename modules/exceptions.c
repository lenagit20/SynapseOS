/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#include <kernel.h>
#include <exceptions.h>
#include <io/tty.h>


void divide_by_zero(){
    set_color(COLOR_RED);

    putsln("ERROR: Divide-by-zero");
	while(1);

}