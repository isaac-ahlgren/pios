#include <stdint.h>
#include "common.h"
#include "page.h"
#include "list.h"

struct ppage physical_page_array[1024];
struct ppage* free_pages = 0;

void init_pfa_list(void) {
    
    struct ppage** free = &free_pages;
    uint64_t addr = (uint64_t) (((uint64_t) &__end) & ~(PAGE_SIZE - 1)) + PAGE_SIZE;

    for (int i = 0; i < 128; i++) {
	physical_page_array[i].physical_addr = (uint64_t) addr;
        list_add((struct list_element*) &physical_page_array[i], (struct list_element**)free);
	addr += PAGE_SIZE;
    }	
}

struct ppage *allocate_physical_pages(unsigned int npages) {
    
    struct ppage *ret  = 0;

    if (npages && free_pages) {

    	struct ppage* node = free_pages;
	ret = free_pages;

	while (node && npages--)
            node = node->next;

	free_pages = node;

	if (node) {
            node->prev->next = 0;
	    node->prev = 0;
	}
    }

    return ret;
}

void free_physical_pages(struct ppage *ppage_list) {

    if (ppage_list) {
        
	if (free_pages) { //Connect to back
	    struct ppage* node = ppage_list;
	
	    if (node->prev) node->prev->next = 0;
	    node->prev = 0;	

            while (node->next)
	        node = node->next;
	
	    free_pages->prev = node;
	    node->next = free_pages;
	}

	free_pages = ppage_list;
    }

}
   
