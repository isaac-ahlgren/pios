#include "page.h"
#include <string.h>

struct ppage physical_page_array[128];
struct ppage* free_pages;

void init_pfa_list(void) {
    memset(physical_page_array, 0, sizeof(struct ppage)*128);

    for (int i = 0; i < 127; i++) {
        physical_page_array[i].next   = &physical_page_array[i+1];
	physical_page_array[i+1].prev = &physical_page_array[i];
    }

    free_pages = physical_page_array;
}

struct ppage *allocate_physical_pages(unsigned int npages) {
    
    struct ppage *ret  = free_pages;

    if (npages && free_pages) {
        struct ppage *node = free_pages;
    
    	while (npages-- && node->next)
            node = node->next;

        free_pages = node->next;
        node->next = 0;

        if (free_pages) //Empty free pages
            free_pages->prev = 0;
    }
    
    return ret;
}

void free_physical_pages(struct ppage *ppage_list) {

    if (free_pages) {
        struct ppage *node = ppage_list;
    
        while (node->next)
            node = node->next;
    
        node->next = free_pages;
    
        if (free_pages) //Empty free pages
            free_pages->prev = node;
    }
    
    free_pages = ppage_list;
}

struct ppage *getfree() { return free_pages; }
   
