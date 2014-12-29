#ifndef _uart_included_h_
#define _uart_included_h_

#include <stdint.h>

void uart_init(uint32_t baud);
void uart_putchar(uint8_t c);
void uart_send_str(/*unsigned*/ char *str);
uint8_t uart_getchar(void);
uint8_t uart_available(void);
void uart_flush_input(void);	// discard any buffered input

#endif
