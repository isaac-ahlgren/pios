#include "list.h"

extern long * __bss_start, __bss_end; //https://sourceware.org/binutils/docs/ld/Source-Code-Reference.html
int i; //Or else there is no bss segment to clear

void bss_clear() {
    long * start = __bss_start;
    long * end   = __bss_end;

    while (start != end) {
        *start = 0;
        start++;
    }
}

void kernel_main() {

    while(1){
    }
}
