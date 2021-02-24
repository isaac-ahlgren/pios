#ifndef _UART_H
#define _UART_H

void init_miniuart();
void uart_send_char(char);
char uart_get_char();
void uart_send_string(char*);

#endif