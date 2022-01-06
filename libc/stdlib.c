/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/ 


#include <libc/stdlib.h>
#include <libc/string.h>


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


/*
    itoa is needed to convert integer to string.

    i- the integer wich you need to convert
*/
char* itoa(int n) {
    int i = 0, sign;
    char * str = "";

    if ((sign = n) < 0) {
        n = -n;
    }

    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverse(str);

    return str;
}