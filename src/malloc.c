#include <stddef.h>
#include "malloc.h"

char heap[8192];
Block* free_blocks;

void init_heap_alloc() {

    free_blocks = heap;

    free_blocks->size = align(8192 - sizeof(Block));

    free_block->next = 0;

}


void* malloc(size_t size) {
    
    Block* free = free_blocks;
    void* mem = 0;

    // find appropriate block
    while (free != 0) {

        if (free->size >= size) {

	    mem = free->data;
	    break;
	}
        
	
    

