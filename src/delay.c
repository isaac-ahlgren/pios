#include <stdint.h>
#include "delay.h"

void delay_ms(unsigned int ms) {

    volatile uint32_t* time = TIMER_LOW;
    uint32_t targtime = ms*1000 + *time;

    while (targtime > *time)
        ;
}

void delay_mc(unsigned int mc) {

    volatile uint32_t* time = TIMER_LOW;
    uint32_t targtime = mc + *time;
    
    while (targtime > *time)
        ;
}    

void delay_cycles(unsigned int n)
{
    if(n) while(n--) { asm volatile("nop"); }
}
