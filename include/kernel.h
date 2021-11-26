/*
    Copyright (C) Aren Elchinyan 2021. All rights reserved.
    Distributed under terms of the Creative Commons Zero v1.0 Universal License.
*/

#pragma once

#include <stdint.h>
#include <io/tty.h>


typedef unsigned long uint32;
typedef signed long int32;

typedef unsigned long long uint64;
typedef signed long long int64;


#ifdef __x86_64__
    typedef uint64 size_t;
#else
    typedef uint32 size_t;
#endif