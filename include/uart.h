#ifndef _UART_H
#define _UART_H

#include <stdint.h>

#define UART(x) uart_send_string(x)

void miniuart_init();
void uart_send_char(uint32_t);
char uart_get_char();
void uart_send_string(char*);

#endif
