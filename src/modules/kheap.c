//

#include "../include/kheap.h"
int kheap_is_init; // was kheap manager initialised or not.         TODO: is it unused?

void kheap_init(KHEAPBM *heap) {
	heap->fblock = 0;
}
 
int k_heapBMAddBlock(KHEAPBM *heap, uintptr_t addr, uint32 size, uint32 bsize) {
	KHEAPBLOCKBM		*b;
	uint32				bcnt;
	uint32				x;
	uint8				*bm;
 
	b = (KHEAPBLOCKBM*)addr;
	b->size = size - sizeof(KHEAPBLOCKBM);
	b->bsize = bsize;
 
	b->next = heap->fblock;
	heap->fblock = b;
 
	bcnt = b->size / b->bsize;
	bm = (uint8*)&b[1];
 
	/* clear bitmap */
	for (x = 0; x < bcnt; ++x) {
			bm[x] = 0;
	}
 
	/* reserve room for bitmap */
	bcnt = (bcnt / bsize) * bsize < bcnt ? bcnt / bsize + 1 : bcnt / bsize;
	for (x = 0; x < bcnt; ++x) {
			bm[x] = 5;
	}
 
	b->lfb = bcnt - 1;
 
	b->used = bcnt;
 
	return 1;
}
 
static uint8 k_heapBMGetNID(uint8 a, uint8 b) {
	uint8		c;	
	for (c = a + 1; c == b || c == 0; ++c);
	return c;
}
 
void *kheap_malloc(KHEAPBM *heap, uint32 size) {
	KHEAPBLOCKBM		*b;
	uint8				*bm;
	uint32				bcnt;
	uint32				x, y, z;
	uint32				bneed;
	uint8				nid;
 
	/* iterate blocks */
	for (b = heap->fblock; b; b = b->next) {
		/* check if block has enough room */
		if (b->size - (b->used * b->bsize) >= size) {
 
			bcnt = b->size / b->bsize;		
			bneed = (size / b->bsize) * b->bsize < size ? size / b->bsize + 1 : size / b->bsize;
			bm = (uint8*)&b[1];
 
			for (x = (b->lfb + 1 >= bcnt ? 0 : b->lfb + 1); x < b->lfb; ++x) {
				/* just wrap around */
				if (x >= bcnt) {
					x = 0;
				}		
 
				if (bm[x] == 0) {	
					/* count free blocks */
					for (y = 0; bm[x + y] == 0 && y < bneed && (x + y) < bcnt; ++y);
 
					/* we have enough, now allocate them */
					if (y == bneed) {
						/* find ID that does not match left or right */
						nid = k_heapBMGetNID(bm[x - 1], bm[x + y]);
 
						/* allocate by setting id */
						for (z = 0; z < y; ++z) {
							bm[x + z] = nid;
						}
 
						/* optimization */
						b->lfb = (x + bneed) - 2;
 
						/* count used blocks NOT bytes */
						b->used += y;
 
						return (void*)(x * b->bsize + (uintptr_t)&b[1]);
					}
 
					/* x will be incremented by one ONCE more in our FOR loop */
					x += (y - 1);
					continue;
				}
			}
		}
	}
 
	return 0;
}
 
void kheap_free(KHEAPBM *heap, void *ptr) {
	KHEAPBLOCKBM		*b;	
	uintptr_t				ptroff;
	uint32				bi, x;
	uint8				*bm;
	uint8				id;
	uint32				max;
 
	for (b = heap->fblock; b; b = b->next) {
		if ((uintptr_t)ptr > (uintptr_t)b && (uintptr_t)ptr < (uintptr_t)b + sizeof(KHEAPBLOCKBM) + b->size) {
			/* found block */
			ptroff = (uintptr_t)ptr - (uintptr_t)&b[1];  /* get offset to get block */
			/* block offset in BM */
			bi = ptroff / b->bsize;
			/* .. */
			bm = (uint8*)&b[1];
			/* clear allocation */
			id = bm[bi];
			/* oddly.. GCC did not optimize this */
			max = b->size / b->bsize;
			for (x = bi; bm[x] == id && x < max; ++x) {
				bm[x] = 0;
			}
			/* update free block count */
			b->used -= x - bi;
			return;
		}
	}
 
	/* this error needs to be raised or reported somehow */
	return;
}

void kheap_test(){
	KHEAPBM     kheap;
    char        *ptr;
 
    kheap_init(&kheap);                              /* initialize the heap */
    k_heapBMAddBlock(&kheap, 0x100000, 0x100000, 16);  /* add block to heap 
                                                       (starting 1MB mark and length of 1MB) 
                                                       with default block size of 16 bytes
                                                       */
    ptr = (char*)kheap_malloc(&kheap, 256);           /* allocate 256 bytes (malloc) */
    kheap_free(&kheap, ptr);                         /* free the pointer (free) */
}