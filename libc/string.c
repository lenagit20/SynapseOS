/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#include <libc/string.h>


int strlen(const char *str) {
	int len = 0;
	while (str[len] != 0) {
		len++;
	}
	return len;
}