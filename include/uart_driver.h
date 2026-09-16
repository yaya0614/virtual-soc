#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include <stdint.h>


void uart_tx(uint8_t data);
uint8_t uart_rx(void);
void uart_irq_handler(void);
static void uart_push_buffer(uint8_t data);
uint8_t uart_pop_buffer(uint8_t *data);
#endif // UART_DRIVER_H