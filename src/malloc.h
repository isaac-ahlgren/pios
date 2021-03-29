#ifndef _MALLOC_H
#define _MALLOC_H

#include <stddef.h>

typedef struct block {
    size_t size;        // size of block
    struct block* next; // next block
    void data[1];       // pointer to first word in data
} Block;

// aligns to 8-byte boundary
inline align(size_t n) {

    return (n + sizeof(void*) - 1) & ~(sizeof(void*));

}

#endif

