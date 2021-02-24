#ifndef _AUX_H
#define _AUX_H

#define AUX_BASE 	0xFE215000

#define AUX_ENABLES	    (volatile uint32_t*) (AUX_BASE+0x04)
#define AUX_MU_IO_REG	(volatile uint32_t*) (AUX_BASE+0x40)
#define AUX_MU_IER_REG  (volatile uint32_t*) (AUX_BASE+0x44)
#define AUX_MU_LCR_REG  (volatile uint32_t*) (AUX_BASE+0x4C)
#define AUX_MU_MCR_REG  (volatile uint32_t*) (AUX_BASE+0x50)
#define AUX_MU_BAUD_REG	(volatile uint32_t*) (AUX_BASE+0x68)
#define AUX_MU_CNTL_REG (volatile uint32_t*) (AUX_BASE+0x60)
#define AUX_MU_STAT_REG (volatile uint32_t*) (AUX_BASE+0x64)

#endif

