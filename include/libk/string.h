/*
    Copyright (C) Aren Elchinyan 2021-2022. All rights reserved.
    Distributed under terms of the Apache-2.0 License.
*/


#pragma once


#include <stddef.h>


size_t strlen(const char *str);
void *memcpy(void *destination, const void *source, size_t n);
void *memset(void *destination, int c, size_t n);