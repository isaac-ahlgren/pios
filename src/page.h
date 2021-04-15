#ifndef _PAGE_H
#define _PAGE_H

#define PAGE_SIZE 0x200000

struct ppage {
    struct ppage *next;
    struct ppage *prev;
    void *physical_addr;
};

void init_pfa_list(void);
struct ppage *allocate_physical_pages(unsigned int);
void free_physical_pages(struct ppage*);

#endif
