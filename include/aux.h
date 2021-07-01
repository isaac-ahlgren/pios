#ifndef _AUX_H
#define _AUX_H

#include <stdint.h>
#include "pbase.h"

#define AUX_BASE 	(PBASE+0x215000)

#define AUX_IRQ            (volatile uint32_t*) (AUX_BASE)
#define AUX_ENABLES	   (volatile uint32_t*) (AUX_BASE+0x04)
#define AUX_MU_IO_REG	   (volatile uint32_t*) (AUX_BASE+0x40)
#define AUX_MU_IER_REG     (volatile uint32_t*) (AUX_BASE+0x44)
#define AUX_MU_IIR_REQ     (volatile uint32_t*) (AUX_BASE+0x48)
#define AUX_MU_LCR_REG     (volatile uint32_t*) (AUX_BASE+0x4C)
#define AUX_MU_MCR_REG     (volatile uint32_t*) (AUX_BASE+0x50)
#define AUX_MU_LSR_REG     (volatile uint32_t*) (AUX_BASE+0x54)
#define AUX_MU_MSR_REQ     (volatile uint32_t*) (AUX_BASE+0x58)
#define AUX_MU_SCRATCH     (volatile uint32_t*) (AUX_BASE+0x5C)
#define AUX_MU_CNTL_REG    (volatile uint32_t*) (AUX_BASE+0x60)
#define AUX_MU_STAT_REG    (volatile uint32_t*) (AUX_BASE+0x64)
#define AUX_MU_BAUD_REG	   (volatile uint32_t*) (AUX_BASE+0x68)
#define AUX_SPI1_CNTL0_REG (volatile uint32_t*) (AUX_BASE+0x80)
#define AUX_SPI1_CNTL1_REG (volatile uint32_t*) (AUX_BASE+0x84)
#define AUX_SPI1_STAT_REG  (volatile uint32_t*) (AUX_BASE+0x88)
#define AUX_SPI1_PEEK_REG  (volatile uint32_t*) (AUX_BASE+0x8C)
#define AUX_SPI1_IO_REG    (volatile uint32_t*) (AUX_BASE+0xA0)

#endif

