#include <stddef.h>

void* memset(void *m, int c, size_t s) {

    unsigned char* mem = (unsigned char*) m;

    for (int i = 0; i < s; i++) {

        mem[i] = (unsigned char) c;

    }

    return m;
}

void* memcpy(void *dest, void* src, size_t s) {

    unsigned char* de = (unsigned char*) dest;
    unsigned char* sr = (unsigned char*) src;
    
    for (int i = 0; i < s; i++) {
    
        de[i] = sr[i];
        
    }
    
    return dest;
}        
