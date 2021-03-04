#ifndef _UART_H
#define _UART_H

#include <stdint.h>

void miniuart_init();
void uart_send_char(uint32_t);
char uart_get_char();
void uart_send_string(char*);

#endif
