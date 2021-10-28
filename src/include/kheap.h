//

#ifndef _KHEAP_H_
#define _KHEAP_H_

#include "memmap.h"
#include "virt_mem.h"
#include "tty.h"
#include "stdlib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
//-------------------------------------------------------------------

typedef struct _KHEAPBLOCKBM {
	struct _KHEAPBLOCKBM	                *next;
	uint32					size;
	uint32					used;
	uint32					bsize;
    uint32                                  lfb;
} KHEAPBLOCKBM;
 
typedef struct _KHEAPBM {
	KHEAPBLOCKBM			*fblock;
} KHEAPBM;
 

void kheap_init();

void *kheap_morecore(uint32_t size);
void kheap_free(KHEAPBM *heap, void *ptr);
void *kheap_malloc(KHEAPBM *heap, uint32 size);

void kheap_print_stat();
void kheap_test();

#endif /* _HEAP_H_ */