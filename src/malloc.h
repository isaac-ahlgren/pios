#ifndef _MALLOC_H
#define _MALLOC_H

#include <stddef.h>

typedef struct block {
    struct block* next; // next block
    struct block* prev; // previous block
    size_t size;        // size of block
} Block;

// aligns to 8-byte boundary
static inline size_t align(size_t n) {

    return (n + sizeof(void*) - 1) & ~(sizeof(void*) - 1);

}

#endif

