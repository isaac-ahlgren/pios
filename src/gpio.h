#ifndef _GPIO_H
#define _GPIO_H

#include <stdint.h>
#include "pbase.h"


#define GPIOBASE 	(PBASE+0x200000)

#define GPFSEL0		(volatile uint32_t*) (GPIOBASE)
#define GPFSEL1		(volatile uint32_t*) (GPIOBASE+0x04)
#define GPFSEL2		(volatile uint32_t*) (GPIOBASE+0x08)
#define GPFSEL3		(volatile uint32_t*) (GPIOBASE+0x0C)
#define GPFSEL4		(volatile uint32_t*) (GPIOBASE+0x10)
#define GPFSEL5		(volatile uint32_t*) (GPIOBASE+0x14)

#define GPSET0		(volatile uint32_t*) (GPIOBASE+0x1C)
#define GPSET1		(volatile uint32_t*) (GPIOBASE+0x20)

#define GPCLR0		(volatile uint32_t*) (GPIOBASE+0x28)
#define GPCLR1		(volatile uint32_t*) (GPIOBASE+0x2C)

#define GPPREG0	 	(volatile uint32_t*) (GPIOBASE+0xE4)

#endif
