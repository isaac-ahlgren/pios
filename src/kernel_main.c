#include "led.h"
#include "kernel_util.h"
#include "uart.h"

extern long __bss_start, __bss_end; //https://sourceware.org/binutils/docs/ld/Source-Code-Reference.html
int i; //Or else there is no bss segment to clear

void bss_clear() {
    long * start = &__bss_start;
    long * end   = &__bss_end;

    while (start != end) {
        *start = 0;
        start++;
    }
}

void kernel_main() {
    int lvl = get_except_lvl();
    
    miniuart_init();
   // led_init();
    while(1){
     //   led_on();

       // delay(500);
        
       // led_off();
        //delay(500);
        esp_vprintf(uart_send_string, "Fuc%c you\n", 'k');
    }
}
