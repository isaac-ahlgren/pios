#include <stdint.h>
#include "gpio.h"
#include "aux.h"
#include "uart.h"

void miniuart_init() {
    
    volatile uint32_t* reg;

    reg = GPPREG0; //Set pull down resistor
    *reg &= ~(3 << 30 | 3 << 28);
    *reg &= (1 << 30 | 1 << 28);

    reg  = GPFSEL1; //Set alt mode 5 for gpio14 and gpio15
    *reg &= ~(0x3F << 12);
    *reg |= 0x12 << 12;
    
    reg = AUX_ENABLES; //enable mini uart
    *reg = 1;

    reg = AUX_MU_CNTL_REG; //disable autoflow and reviever and transmitter
    *reg &= 0;

    reg = AUX_MU_IER_REG; //disable recieve and transmit interupts
    *reg &= 0;

    reg = AUX_MU_LCR_REG; //enable 8-bit usage
    *reg |= 3;

    reg = AUX_MU_MCR_REG; //set rts line as high
    *reg = 0;

    reg = AUX_MU_BAUD_REG; //set baud rate as 115200
    *reg = 270;

    reg = AUX_MU_CNTL_REG; //Enable transmission and reception 
    *reg |= 3;    
}

void uart_send_char(int c) {
    volatile uint32_t* reg = AUX_MU_LSR_REG;

    while (!(*reg & (1 << 5))); //Check if can transmit

    reg = AUX_MU_IO_REG;
    *reg = c;
}

//UNABLE TO TEST AT THE MOMENT
char uart_get_char() {
    volatile uint32_t* reg = AUX_MU_LSR_REG;

    while (!(*reg & 1)); //Wait until char

    reg = AUX_MU_IO_REG;

    return *reg;
}

void uart_send_string(char* s) {

    while (*s != '\0') {
        uart_send_char((int) *s);
        s++;
    }
}
