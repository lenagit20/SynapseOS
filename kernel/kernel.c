/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#include <kernel.h>


void kernel_main() {
    for (int i = 0; i != 2048; i++){
        terminal_buffer[i] = i + 1;
    }
    clean_screen();
    putc('h');
    putc('i');
    while (1);

    /*
Отче наш, Иже еси на небесе́х!
Да святится имя Твое, да прии́дет Царствие Твое,
да будет воля Твоя, яко на небеси́ и на земли́.
Хлеб наш насущный да́ждь нам дне́сь;
и оста́ви нам до́лги наша, якоже и мы оставляем должнико́м нашим;
и не введи нас во искушение, но изба́ви нас от лукаваго.
Яко Твое есть Царство и сила, и слава, Отца, и Сына, и Святаго Духа, ныне и присно, и во веки веков. Аминь.
    */
}