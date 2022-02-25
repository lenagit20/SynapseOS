/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Apache-2.0 License.
*/


#include <kernel.h>
#include <multyboot.h>


int alive = 1;


/*
    kernel_main is the main function of the kernel. 
    It initializes the core modules and the main cycle has been declared.
*/
void kernel_main() {
    clean_screen();
    log_putsln("Setup");
    
    
    set_color(COLOR_LIGHT_CYAN);
    putsln("SynapseOS 0.0.1, Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.");
    putsln("Offical website: https://synapse-os.github.io ");
    putsln("");
    puts("Builded: ");
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
    
    test_floppy();
    set_color(COLOR_LIGHT_CYAN);
    puts("kernel");
    set_color(COLOR_YELLOW);
    puts("> ");
    set_color(COLOR_GREEN);

    //lang0x42_eval(",.[,.]");

    while(alive) {
        keyboard_handler_main();
    }
    
    log_putsln("EXIT");
}