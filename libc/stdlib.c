/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#include <libc/stdlib.h>


/*
    reverse is needed to reverse string.

    s - the string which you need to reverse
*/
void reverse(char s[]) {
	int j;
    char c;

    j = strlen(s) - 1;
 
    for (int i = 0; i < j; i++) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;

        j--;
    }
}
