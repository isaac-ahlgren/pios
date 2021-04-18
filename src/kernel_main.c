#include "led.h"
#include "delay.h"
#include "rprintf.h"
#include "uart.h"
#include "mmu.h"
#include "fat.h"
#include "sd.h"
#include "common.h"

void bss_clear() {
    long * start = &__bss_start;
    long * end   = &__bss_end;

    while (start != end) {
        *start = 0;
        start++;
    }
}

void kernel_main() {    	
    miniuart_init();
    sd_init();
    mmu_on();
    fat_init();
    
    exec("/bin/a.out");

    while(1){

    }
}
