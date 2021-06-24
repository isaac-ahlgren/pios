#ifndef _DELAY_H
#define _DELAY_H

#include "pbase.h"

#define TIMER_BASE                         (PBASE+0x3000)

#define TIMER_LOW     (volatile uint32_t*) (TIMER_BASE+0x04)

void delay_ms(unsigned int);
void delay_mc(unsigned int);
void delay_cycles(unsigned int);

#endif
