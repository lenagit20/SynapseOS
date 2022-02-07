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
    log_putsln("Setup");
    clean_screen();
    set_color(COLOR_LIGHT_CYAN);
    putsln("SynapseOS 0.0.1");
    putsln(__TIMESTAMP__);
    set_color(COLOR_WHITE);

    
    gdt_init();
    putsln("gdt inited");
    log_putsln("gdt inited!");

    idt_init();
    putsln("idt inited");
    log_putsln("idt inited!");

    kb_init();
    putsln("keyboard inited");
    log_putsln("kb inited!");

    while(1){
        keyboard_handler_main();
    }
}