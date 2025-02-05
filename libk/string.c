/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Apache-2.0 License.
*/


#include <libk/string.h>


/*
    strlen is needed to calculate the length of the string.

    str - the string the length of which you need to find out
*/
size_t strlen(const char *str) {
	size_t len = 0;
	while (str[len] != 0) {
		len++;
	}
	return len;
}


/*
    memcpy is needed to copy disjoint arrays.

    destination - a pointer to the array into which the data will be copied.
    source - a pointer to an array of the source of the copied data.
    n - the number of bytes to copy.
*/
void *memcpy(void *destination, const void *source, size_t n){
    char *tmp_dest = (char*)destination;
    const char *tmp_src = (const char*)source;

    while (n){
        *tmp_dest++ = *tmp_src++;
        n--;
    }

    return destination;
}


/*
    memset is needed to fill the array with the specified characters.

    destination - a pointer to the array to fill
    c - character code to fill
    n - the size of the filled part of the array in bytes
*/
void *memset(void *destination, int c, size_t n){
    if (destination){
       char *tmp_mem = (char*)destination;
       while (n--) *tmp_mem++ = c;
    }
    
    return destination;
}


/*
    strcmp is needed for string comparison

    str1, str2 - strings to be compared
*/
int strcmp(const char *str1, const char *str2) {
    int s1;
    int s2;

    do {
        s1 = *str1++;
        s2 = *str2++;
        if (s1 == 0)
            break;
    } while (s1 == s2);

    return (s1 < s2) ? -1 : (s1 > s2);
}