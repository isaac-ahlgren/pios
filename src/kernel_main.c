#include "led.h"
#include "delay.h"
#include "kernel_util.h"
#include "rprintf.h"
#include "uart.h"
#include "mmu.h"
#include "fat.h"
#include "sd.h"
#include "common.h"

void bss_clear() {
    long * start = &__bss_start;
    long * end   = &__bss_end;

    while (start != end) {
        *start = 0;
        start++;
    }
}

void kernel_main() {
     	
    miniuart_init();
    sd_init();
//    led_init();
    fat_init();
    FILE file;
    file_open(&file, "/bin/stuff");

    char buf[21];
    read_file(&file, buf, 20);
    buf[21] = '\0';

    uart_send_string(buf);

    while(1){
 //    led_on();
 //     delay(500);
        
 //     led_off();
 //     delay(500);
 //     esp_printf((func_ptr) uart_send_char, "F");
      //uart_send_char(46);
    }
}
