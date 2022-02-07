/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#include <kernel.h>
#include <multyboot.h>


/*
    kernel_main is the main function of the kernel. 
    It initializes the core modules and the main cycle has been declared.
*/
void kernel_main(const void* multiboot_struct) {
    clean_screen();
    log_putsln("Setup");

    char res[64];



    const multiboot_info_t* mb_info = multiboot_struct;            /* Make pointer to multiboot_info_t struct */
    log_puts("mb_info->flags: ");
    itoa(mb_info->flags, res);
    log_putsln(res);
    
    multiboot_uint32_t mb_flags = mb_info->flags;                  /* Get flags from mb_info */
    log_puts("mb_flags: ");
    itoa(mb_flags, res);
    log_putsln(res);
        
 
    if (mb_flags & MULTIBOOT_INFO_MODS) {                          /* Check if modules are available */
        multiboot_uint32_t mods_count = mb_info->mods_count;   /* Get the amount of modules available */
		log_puts("mods_count: ");
        itoa(mods_count, res);
        log_putsln(res);
        
        multiboot_uint32_t mods_addr = mb_info->mods_addr;     /* And the starting address of the modules */
        
        for (uint32_t mod = 0; mod < mods_count; mod++) {
            log_puts("mod: ");
            itoa(mod, res);
            log_putsln(res);

            multiboot_module_t* module = (multiboot_module_t*)(mods_addr + (mod * sizeof(multiboot_module_t)));     /* Loop through all modules */
        }
    }
    log_putsln("Setup");
    clean_screen();
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

    set_color(COLOR_LIGHT_CYAN);
    puts("kernel");
    set_color(COLOR_YELLOW);
    puts("> ");
    set_color(COLOR_GREEN);

    while(1){
        keyboard_handler_main();
    }
}