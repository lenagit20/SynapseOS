/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#include <lang0x42.h>
#include <shell.h>


void shell(char *input){
    log_putsln("SHELL:");
    log_putsln(input);

    if (strcmp(input, "help") == 0) {
        putsln("Commands:");
        putsln("help, 0x42, ls, cd, echo");
    } else if (strcmp(input, "0x42") == 0) {
        input_type = 4;
        putsln("Lang0x42 active!");
    } else if (strcmp(input, "ls") == 0) {

    } else if (strcmp(input, "") == 0) {

    } else if (strcmp(input, "") == 0) {

    }
}