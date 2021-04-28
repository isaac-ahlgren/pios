#ifndef _PAGE_H
#define _PAGE_H

#include <stdint.h>

#define PAGE_SIZE 0x1000

struct ppage {
    struct ppage *next;
    struct ppage *prev;
    uint64_t physical_addr;
};

void init_pfa_list(void);
struct ppage *allocate_physical_pages(unsigned int);
void free_physical_pages(struct ppage*);

#endif
