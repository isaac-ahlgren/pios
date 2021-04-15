#include <stddef.h>
#include <stdbool.h>
#include "list.h"
#include "malloc.h"

char heap[8192];
Block* free_blocks;

void init_heap_alloc() {

    free_blocks = (Block*) heap;

    free_blocks->size = 8192 - sizeof(Block);

    free_blocks->next = 0;
    
    free_blocks->prev = 0;

}

void* get_address(Block* block) {

    char* addr = ((char*) block) + sizeof(Block);

    return (void*) addr;
}

Block* get_block(void* addr) {

    char* block = ((char*) addr) - sizeof(Block);
    
    return (Block*) block;
}    

/*
 * Return true if it can be split into
 * two seperate blocks. Expect bytes to
 * be aligned on the 8-byte boundary.
 */
bool can_split(size_t size, Block* block) {

    return (size < block->size - sizeof(Block));
    
}

/*
 * Return true if memory boundaries match up.
 */
bool can_coalesce(Block* block1, Block* block2) {

    return (((char*)block1) + sizeof(Block) + block1->size) == (char*) block2;
    
}

/*
 * Splits piece off of block
 * and returns remaining block.
 */
Block* split(size_t size, Block* block) {

    // convert to char, add bytes, convert back to block
    Block* split_point = (Block*) (((char *) block) + sizeof(Block) + size);
    
    // save data for second block
    split_point->size = block->size - sizeof(Block) - size;
    
    // insert split point into list
    list_insert_after((List_Element*) split_point, (List_Element*) block);
    
    // remove first split block 
    list_unlink((List_Element*) block);
    
    block->size = size;
    
    return split_point;
}

/*
 * Coalesces block into the front
 * of a block within the list and
 * returns new block
 */

Block* coalesce(Block* block, Block* block_list) {

    // add sizes of going-to-be coalesced block plus its descriptor
    block->size += block_list->size + sizeof(Block);
    
    // append complete block before coalesced block
    list_insert_after((List_Element*) block, (List_Element*) block_list);
    
    // removes coalesced block from list
    list_unlink((List_Element*) block_list);   
        
    return block;
}

void* malloc(size_t size) {
    size = align(size);
    
    Block* free = free_blocks;
    Block* save_block = 0;     // variable to save next block to replace head in case of removing of head block
    void* addr = 0;

    // find appropriate block
    while (free) {
	
	// if equal, take block size
	if (size == free->size) {
	    save_block = free->next;
	    list_unlink((List_Element*) free);
	    addr = get_address(free);
	    break;
	}
	// if block is bigger, split block
        else if (can_split(size, free)) {
            save_block = split(size, free);
            addr = get_address(free);
	    break;
	}
	
	free = free->next;
	
    }
    
    // if block was first in list, change free_blocks pointer
    if (free_blocks && free == free_blocks) {
        free_blocks = save_block;
    }
        
    
    return addr;
}



void free(void* addr) {

    Block* free = free_blocks;
    Block* save_block = 0;     // variable to save next block to replace head in case of removing of head block
    Block* block = get_block(addr);
    
    while (free) {
    
        if (can_coalesce(block, free)) {
            save_block = coalesce(block, free);
            break;
        }
        else if (get_address(free) > addr) {
            list_insert_before((List_Element*) block, (List_Element*) free);
            save_block = block;
            break;
        }
        else if (!free->next) {
            list_insert_after((List_Element*) block, (List_Element*) free);
            break;
        }    
        
        free = free->next;            
            
    }
    
    // if list is empty
    if (!free_blocks) {
        list_add((List_Element*) block, (List_Element**) &free_blocks);
    }         
    // if block was added to the front, change free_blocks pointer
    else if (free_blocks && free == free_blocks) {
        free_blocks = save_block;
    }
        

}                
