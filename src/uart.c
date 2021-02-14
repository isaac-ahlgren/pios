#include <stdint.h>
#include "gpio.h"
#include "aux.h"

void init_miniuart() {
    
    uint32_t* reg;

    // reg = (uint32_t*) GPPREG1; //Set pulldown resistor for gpio14 and gpio15
    // *reg &= ~(0xF << 28);
    //*reg |= 0xA << 28;

    reg  = (uint32_t*) GPFSEL1; //Set alt mode 5 for gpio14 and gpio15
    *reg &= ~(0x3F << 12);
    *reg |= 0x12 << 12;
    
    reg = (uint32_t*) AUX_ENABLES; //enable mini uart
    *reg = 1;

    reg = (uint32_t*) AUX_MU_IER_REG; //disable recieve and transmit interupts
    *reg &= ~(0x3);

    reg = (uint32_t*) AUX_MU_LCR_REG; //enable 8-bit usage
    *reg |= 1;

    reg = (uint32_t*) AUX_MU_MCR_REG; //set rts line as high
    *reg = 0;

    reg = (uint32_t*) AUX_MU_BAUD_REG; //set baud rate as 115200
    *reg = 270;
    
} 	
