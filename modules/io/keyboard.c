/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#include <kernel.h>


/*
  0 - none
  1 - shell
  2 - getchar
  3 - gets

*/
int input_type = 1, SHIFT, string_mem_counter;
char keycode, last_char; 
char string_mem[1024];


unsigned  char keyboard_map[] = {
    0, 
    27, //`
    '1', '2',  '3', '4',  '5', '6',  '7', '8',	'9',  '0', 
    '-', '=',  
    '\b',	/*  Backspace  */
    '\t',			/*  Tab  */
    'q', 'w',  'e', 'r',	/*  19 */
    't', 'y',  'u', 'i',  'o', 'p',  '[', ']',  '\n',	/*  Enter  key  */
    0,			/*  29 - Control */
    'a', 's',  'd', 'f',  'g', 'h',  'j', 'k',  'l', ';',	/*  39 */
    '\'',  '`', 
    -2,		/*  Left shift 42 */
    '\\',  'z', 'x',  'c', 'v',  'b', 'n',			/*  49 */
    'm', ',',  '.', '/',  
    -2,				/*  Right  shift  54*/
    '*',
    0,	/*  Alt  */
    ' ',	/*  Space  bar  */
    -1,	/*  Caps lock  */
    0,	/*  59 - F1  key  ...  >  */
    0, 0,  0, 0,  0, 0,  0, 0,
    0,	/*  <  ...  F10  */
    0,	/*  69 - Num lock*/
    0,	/*  Scroll Lock  */
    0,	/*  Home key */
    0,	/*  Up Arrow */
    0,	/*  Page Up  */
    '-',
    0,	/*  Left Arrow */
    0,
    0,	/*  Right  Arrow  */
    '+',
    0,	/*  79 - End key*/
    0,	/*  Down Arrow */
    0,	/*  Page Down  */
    0,	/*  Insert Key */
    0,	/*  Delete Key */
    0, 0,  0,
    0,	/*  F11  Key  */
    0,	/*  F12  Key  */
    0,	/*  All  other  keys are undefined */
};

unsigned  char keyboard_map_shifted[] = {
    0, 
    27, //`
    '!', '@',  '#', '$',  '%', '^',  '&', '*',	'(',  ')', 
    '_', '+',  
    '\b',	/*  Backspace  */
    '\t',			/*  Tab  */
    'Q', 'W',  'E', 'R',	/*  19 */
    'T', 'Y',  'U', 'I',  'O', 'P',  '{', '}',  '\n',	/*  Enter  key  */
    0,			/*  29 - Control */
    'A', 'S',  'D', 'F',  'G', 'H',  'J', 'K',  'L', ':',	/*  39 */
    '"',  '`', 
    1,		/*  Left shift */
    '|',  'Z', 'X',  'C', 'V',  'B', 'N',			/*  49 */
    'M', '<',  '>', '?',  
    1,				/*  Right  shift  */
    '*',
    0,	/*  Alt  */
    ' ',	/*  Space  bar  */
    -1,	/*  Caps lock  */
    0,	/*  59 - F1  key  ...  >  */
    0, 0,  0, 0,  0, 0,  0, 0,
    0,	/*  <  ...  F10  */
    0,	/*  69 - Num lock*/
    0,	/*  Scroll Lock  */
    0,	/*  Home key */
    0,	/*  Up Arrow */
    0,	/*  Page Up  */
    '-',
    0,	/*  Left Arrow */
    0,
    0,	/*  Right  Arrow  */
    '+',
    0,	/*  79 - End key*/
    0,	/*  Down Arrow */
    0,	/*  Page Down  */
    0,	/*  Insert Key */
    0,	/*  Delete Key */
    0, 0,  0,
    0,	/*  F11  Key  */
    0,	/*  F12  Key  */
    0,	/*  All  other  keys are undefined */
};

void kb_init(void) {
    input_type = 1;
    /* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
    port_outb(0x21, 0xFD);
}

void keyboard_handler_main(void) {

    unsigned char status;
    char res[32];

    /* write EOI */
    port_outb(0x20, 0x20);

    status = port_inb(KEYBOARD_STATUS_PORT);

    /* Lowest bit of status will be set if buffer is not empty */
    if (status & 0x01) {
        keycode = port_inb(KEYBOARD_DATA_PORT);

        if (input_type == 0) {
            return;
        }

        if (keycode == -86 || keycode == 42) {
            SHIFT = 1;
            return;
        }
        if (keycode < 0){
            return;
        }
        if (SHIFT) {
            last_char =  keyboard_map_shifted[(unsigned char) keycode];
        }
        last_char = keyboard_map[(unsigned char) keycode];
        if (input_type == 2) {
            log_puts("getch: ");
            itoa(keycode, res);
            log_putsln(res);
            input_type = 0;
            
            return;
        }
        // Keycode 14 is backspase
        if (keycode == 14) {

            if (string_mem_counter != 0) {
                string_mem_counter--;
                string_mem[string_mem_counter] = 0;
                log_putsln("string_mem =");
                log_putsln(string_mem);
                log_putsln("string_mem_counter =");
                itoa(string_mem_counter, res);
                log_putsln(res);
                backspace();
            }
            return;
        }
        if (input_type == 3) {
            log_puts("getch: ");
            itoa(keycode, res);
            log_putsln(res);
            input_type = -2;
            return;
        }

        if (keycode == ENTER_KEY_CODE) {
            row++;
            col = -1;
            if (input_type == 1) {
                string_mem_counter = 0;
                shell(string_mem);
                memset(string_mem, 0, 1024);
            }
            return;
        }

        if (keycode ==  input_type == 1) {
            putsln("EXIT");
            alive = 0;
            return;
        }

        if (string_mem_counter > 1023) {
            log_putsln("Buffer string_mem is full!!");
            putsln("Buffer string_mem is full!!");
            return;
        }

        string_mem[string_mem_counter] = last_char;
        string_mem_counter++;
        log_puts("Scancode: ");
        itoa(keycode, res);
        log_putsln(res);
        if (keycode < 0) {
            return;
        }
        putchar(last_char);
        //qemu_printf("key = %c (index %d)\n", keyboard_map[(unsigned char) keycode], (unsigned char) keycode);
    }
}

char getchar() {
    input_type = 2;

    while (input_type != -2) {
        keyboard_handler_main();
    }
    input_type = 1;
    return last_char;
}

char gets() {
    input_type = 3;

    while (input_type != -3) {
        keyboard_handler_main();
    }
    input_type = 1;
    return last_char;
}