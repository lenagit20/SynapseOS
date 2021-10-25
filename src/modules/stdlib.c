#include "../include/stdlib.h"
#include "../include/qemu_log.h"
#include "../include/tty.h"

int abs(int number) {
  return number >= 0 ? number : -number;
}

void panic(const char *text) {
    qemu_printf("\n    KERNEL PANIC\n %s\n", text);
    if (tty_initialized == 1) {
        tty_printf("\n    KERNEL PANIC\n %s\n", text);
    }
    asm volatile("hlt");
}


void* memset(void* ptr, uint8_t val, size_t n) {
	uint32_t num_dwords = n/4;
  	uint32_t num_bytes = n%4;
  	uint32_t *dst32 = (uint32_t*)ptr;
  	uint8_t *dst8 = ((uint8_t*)ptr)+num_dwords*4;
  	uint8_t val8 = (uint8_t)val;
  	uint32_t val32 = val|(val<<8)|(val<<16)|(val<<24);
  	uint32_t i;

  	for (i=0;i<num_dwords;i++) {
    	dst32[i] = val32;
  	}
  	for (i=0;i<num_bytes;i++) {
    	dst8[i] = val8;
  	}
  	return ptr;
}


void memset_word(void *mem, uint16 value, size_t count) {
    asm("movl %0, %%eax \n movl %1, %%edi \n movl %2, %%ecx \n rep stosl"::"a"((uint32)value | ((uint32)value << 16)),"b"(mem),"c"(count >> 1));
}


void memcpy(void *dest, void *src, size_t count) {
    asm("movl %0, %%edi \n movl %1, %%esi \n movl %2, %%ecx \n rep movsl"::"a"(dest),"b"(src),"c"(count >> 2));
    asm("movl %0, %%ecx \n rep movsb"::"a"(count & 3));
}


int memcmp(void *mem1, void *mem2, size_t count) { 
    char above, below; 
    asm("movl %0, %%esi \n movl %1, %%edi \n movl %2, %%ecx \n repe cmpsb"::"a"(mem1),"b"(mem2),"c"(count)); 
    asm("seta %0 \n setb %1":"=a"(above),"=b"(below)); 
    return above - below;
}


void *memchr(void *mem, char value, size_t count) {
    void *result;
    asm("movb %b0, %%al \n movl %1, %%edi \n movl %2, %%ecx \n repe cmpsb"::"a"(value),"b"(mem),"c"(count));
    asm("movl %%edi, %0":"=a"(result));
    if (result < mem + count) {
        return result;
    } else {
        return S_NULL;
    }
}


size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len] != 0) {
		len++;
	}
	return len;
}


void strcpy(char *dest, char *src) {
    memcpy(dest, src, strlen(src) + 1);
}


void strncpy(char *dest, char *src, size_t max_count) {
    size_t len = min(max_count - 1, strlen(src));
    memcpy(dest, src, len);
    dest[len] = '\0';
}


int strcmp(const char *str1, const char *str2) {
    int s1, s2;
    do {
        s1 = *str1++;
        s2 = *str2++;
        if (s1 == 0) {
            break;
        }
    } while (s1 == s2);
    return (s1 < s2) ? -1 : (s1 > s2);
}


char *strchr(char *str, char value) {
    return memchr(str, value, strlen(str));
}