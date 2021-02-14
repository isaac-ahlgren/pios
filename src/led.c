#include <stdint.h>
#include "led.h"
#include "gpio.h"

void led_init() {

    uint32_t* reg = (uint32_t*) GPFSEL4; //Location of GPIO pin 42

    *reg &= 0xFFFFFE3F;
    *reg |= 0x00000040;
}

void led_on() {

    uint32_t* reg = (uint32_t*) GPSET1; //Location of GPIO control

    *reg |= (1 << 10);
}

void led_off() {

    uint32_t* reg = (uint32_t*) GPCLR1; //Location of GPIO clear

    *reg |= (1 << 10);
}

void delay(int ms) {

    volatile uint32_t* time = (uint32_t*) 0xFE003004;
    uint32_t targtime = ms*1000 + *time;

    while (targtime > *time)
        ;
}
