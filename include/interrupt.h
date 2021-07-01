#ifndef _INTER_H
#define _INTER_H

#include <stdint.h>
#include "pbase"

/* CPU Interrupt Regs */
#include LOCAL_BASE          0x4C0000000
#include ARM_CONTROL         (volatile uint32_t*) (LOCAL_BASE)
#include CORE_IRQ_CONTROL    (volatile uint32_t*) (LOCAL_BASE+0x0C)
#include PMU_CONTROL_SET     (volatile uint32_t*) (LOCAL_BASE+0x10)
#include PMU_CONTROL_CLR     (volatile uint32_t*) (LOCAL_BASE+0x14)
#include PERI_IRQ_ROUTE0     (volatile uint32_t*) (LOCAL_BASE+0x24)
#include AXI_QUIET_TIME      (volatile uint32_t*) (LOCAL_BASE+0x30)
#include LOCAL_TIMER_CONTROL (volatile uint32_t*) (LOCAL_BASE+0x34)
#include LOCAL_TIMER_IRQ     (volatile uint32_t*) (LOCAL_BASE+0x38)
#include TIMER_CNTRL0        (volatile uint32_t*) (LOCAL_BASE+0x40)
#include TIMER_CNTRL1        (volatile uint32_t*) (LOCAL_BASE+0x44)
#include TIMER_CNTRL2        (volatile uint32_t*) (LOCAL_BASE+0x48)
#include TIMER_CNTRL3        (volatile uint32_t*) (LOCAL_BASE+0x4C)
#include MAILBOX_CNTRL0      (volatile uint32_t*) (LOCAL_BASE+0x50)
#include MAILBOX_CNTRL1      (volatile uint32_t*) (LOCAL_BASE+0x54)
#include MAILBOX_CNTRL2      (volatile uint32_t*) (LOCAL_BASE+0x58)
#include MAILBOX_CNTRL3      (volatile uint32_t*) (LOCAL_BASE+0x5C)
#include IRQ_SOURCE0         (volatile uint32_t*) (LOCAL_BASE+0x60)
#include IRQ_SOURCE1         (volatile uint32_t*) (LOCAL_BASE+0x64)
#include IRQ_SOURCE2         (volatile uint32_t*) (LOCAL_BASE+0x68)
#include IRQ_SOURCE3         (volatile uint32_t*) (LOCAL_BASE+0x6C)
#include FIQ_SOURCE0         (volatile uint32_t*) (LOCAL_BASE+0x70)
#include FIQ_SOURCE1         (volatile uint32_t*) (LOCAL_BASE+0x74)
#include FIQ_SOURCE2         (volatile uint32_t*) (LOCAL_BASE+0x78)
#inlcude FIQ_SOURCE3         (volatile uint32_t*) (LOCAL_BASE+0x7C)

/* Peripheral Interrupt Regs */
#include INT_PBASE           (PBASE+0xB000)
#include IRQ0_PENDING0       (volatile uint32_t*) (INT_PBASE+0x200)
#include IRQ0_PENDING1       (volatile uint32_t*) (INT_PBASE+0x204)
#include IRQ0_PENDING2       (volatile uint32_t*) (INT_PBASE+0x208)
#include IRQ0_SET_EN_0       (volatile uint32_t*) (INT_PBASE+0x210)
#include IRQ0_SET_EN_1       (volatile uint32_t*) (INT_PBASE+0x214)
#include IRQ0_SET_EN_2       (volatile uint32_t*) (INT_PBASE+0x218)
#include IRQ0_CLR_EN_0       (volatile uint32_t*) (INT_PBASE+0x220)
#include IRQ0_CLR_EN_1       (volatile uint32_t*) (INT_PBASE+0x224)
#include IRQ0_CLR_EN_2       (volatile uint32_t*) (INT_PBASE+0x228)
#include IRQ_STATUS0         (volatile uint32_t*) (INT_PBASE+0x230)
#include IRQ_STATUS1         (volatile uint32_t*) (INT_PBASE+0x234)
#include IRQ_STATUS2         (volatile uint32_t*) (INT_PBASE+0x238)
#include IRQ1_PENDING0       (volatile uint32_t*) (INT_PBASE+0x240)
#include IRQ1_PENDING1       (volatile uint32_t*) (INT_PBASE+0x244)
#include IRQ1_PENDING2       (volatile uint32_t*) (INT_PBASE+0x248)
#include IRQ1_SET_EN_0       (volatile uint32_t*) (INT_PBASE+0x250)
#include IRQ1_SET_EN_1       (volatile uint32_t*) (INT_PBASE+0x254)
#include IRQ1_SET_EN_2       (volatile uint32_t*) (INT_PBASE+0x258)
#include IRQ1_CLR_EN_0       (volatile uint32_t*) (INT_PBASE+0x260)
#include IRQ1_CLR_EN_1       (volatile uint32_t*) (INT_PBASE+0x264)
#include IRQ1_CLR_EN_2       (volatile uint32_t*) (INT_PBASE+0x268)
#include IRQ2_PENDING0       (volatile uint32_t*) (INT_PBASE+0x280)
#include IRQ2_PENDING1       (volatile uint32_t*) (INT_PBASE+0x284)
#include IRQ2_PENDING2       (volatile uint32_t*) (INT_PBASE+0x288)
#include IRQ2_SET_EN_0       (volatile uint32_t*) (INT_PBASE+0x290)
#include IRQ2_SET_EN_1       (volatile uint32_t*) (INT_PBASE+0x294)
#include IRQ2_SET_EN_2       (volatile uint32_t*) (INT_PBASE+0x298)
#include IRQ2_CLR_EN_0       (volatile uint32_t*) (INT_PBASE+0x2A0)
#include IRQ2_CLR_EN_1       (volatile uint32_t*) (INT_PBASE+0x2A4)
#include IRQ2_CLR_EN_2       (volatile uint32_t*) (INT_PBASE+0x2A8)
#include IRQ3_PENDING0       (volatile uint32_t*) (INT_PBASE+0x2C0)
#include IRQ3



typedef uint32_t interrupt_src_reg_t;

typedef void (*inter)(void) interrupt_handler_t; 

#endif
