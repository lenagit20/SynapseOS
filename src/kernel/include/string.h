#ifndef STRING_H
#define STRING_H

#define S_NULL ((void*)0)

#include <stdint-gcc.h>

typedef unsigned char uint8;
typedef signed char int8;

typedef unsigned short uint16;
typedef signed short int16;

typedef unsigned long uint32;
typedef signed long int32;

typedef unsigned long long uint64;
typedef signed long long int64;

/*typedef unsigned long int __uint64_t;
typedef __uint64_t uint64_t;*/


#ifdef __x86_64__
    typedef uint64 size_t;
#else
    typedef uint32 size_t;
#endif

#define min(a, b) (((a) > (b)) ? (b) : (a))
#define max(a, b) (((a) > (b)) ? (a) : (b))


#define outportb(port, value) asm("outb %b0, %w1"::"a"(value),"d"(port));
#define outportw(port, value) asm("outw %w0, %w1"::"a"(value),"d"(port));
#define outportl(port, value) asm("outl %0, %w1"::"a"(value),"d"(port));
#define inportb(port, out_value) asm("inb %w1, %b0":"=a"(out_value):"d"(port));
#define inportw(port, out_value) asm("inw %w1, %w0":"=a"(out_value):"d"(port));
#define inportl(port, out_value) asm("inl %w1, %0":"=a"(out_value):"d"(port));


void memset(void *mem, char value, size_t count);
void memset_word(void *mem, uint16 value, size_t count);
void memcpy(void *dest, void *src, size_t count);
int memcmp(void *mem1, void *mem2, size_t count);
void *memchr(void *mem, char value, size_t count);

size_t strlen(char *str);
void strcpy(char *dest, char *src);
void strncpy(char *dest, char*src, size_t max_count);
int strcmp(const char *str1, const char *str2);
char *strchr(char *str, char value);

#endif