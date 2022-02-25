/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Apache-2.0 License.
*/

#include <lang0x42.h>



int lang0x42_eval(const char *input){
    log_putsln(input);
    char memory[30000];
    int cursor = 0;

    char current_char;
    size_t i, loop;

    for (i = 0; input[i] != 0; i++){
        current_char = input[i];

        switch(current_char){
            case '+':
                memory[cursor]++;
                break;
            case '-':
                memory[cursor]--;
                break;
            case '>':
                cursor++;
                break;
            case '<':
                cursor--;
                break;
            case '.':
                putchar(memory[cursor]);
                break;
            case ',':
                memory[cursor] = getchar();
                break;
            case '[':
                break;
            case ']':
                if (memory[cursor]) {
                    loop = 1;

                    while ( loop > 0){
                        current_char = input[--i];
                        if (current_char == '['){
                            loop--;
                        } else if (current_char == ']'){
                            loop++;
                        }
                    }
                }
                
                break;
            
            // Non-brainfuck functions
            case '0':
                memory[cursor] = 0;
                break;
            case 'E':
                putsln("Exit with code 2");
                return 2;
                break;


            default:
                break;
            
        }
    }

    putsln("Exit with code 0");

    return 0;
}