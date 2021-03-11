#include "led.h"
#include "kernel_util.h"
#include "rprintf.h"
#include "uart.h"
#include "page.h"
#include "common.h"

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
    
    miniuart_init();
//    led_init();
    
    esp_printf((func_ptr)uart_send_char, "END OF KERNEL: %x\n", &__end);
    uart_send_char('\n');

    init_pfa_list();
    int i = 0;
    struct ppage* node = getfree();

    uart_send_string("AFTER INITIALIZATION\n");
    while (node) {
        esp_printf((func_ptr) uart_send_char, "%d addr: %x\n", ++i, node->physical_addr);
	node = node->next;
    }
    uart_send_char('\n');

    uart_send_string("ALLOCATED PAGES\n");
    i = 0;
    struct ppage* page = allocate_physical_pages(10);
    node = page;
    while (node) {
        esp_printf((func_ptr) uart_send_char, "%d addr: %x\n", ++i, node->physical_addr); 
        node = node->next;
    }
    uart_send_char('\n');

    uart_send_string("FREED PAGES\n");
    i = 0;
    node = getfree();
    while (node) {
        esp_printf((func_ptr) uart_send_char, "%d addr: %x\n", ++i, node->physical_addr);
	node = node->next;
    }
    uart_send_char('\n');

    free_physical_pages(page);
    uart_send_string("FREED PAGES AFTER FREEING\n");
    i = 0;
    node = getfree();
    while (node) {
        esp_printf((func_ptr) uart_send_char, "%d addr: %x\n", ++i, node->physical_addr);
	node = node->next;
    }
    uart_send_char('\n');

    page = allocate_physical_pages(5);
    node = page->next;
    free_physical_pages(node);

    i = 0;
    while (page) {
        esp_printf((func_ptr) uart_send_char, "%d addr: %x\n", ++i, node->physical_addr);
	page = page->next;
    }
    uart_send_char('\n');

    i = 0;
    node = getfree();
    while (node) {
        esp_printf((func_ptr) uart_send_char, "%d addr: %x\n", ++i, node->physical_addr);
	node = node->next;
    }


    while(1){
 //    led_on();
 //     delay(500);
        
 //     led_off();
 //     delay(500);
 //     esp_printf((func_ptr) uart_send_char, "F");
      //uart_send_char(46);
    }
}
