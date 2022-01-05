/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/


#include <libc/string.h>


/*
    strlen is needed to calculate the length of the string.

    str - the string the length of which you need to find out
*/
int strlen(const char *str) {
	int len = 0;
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