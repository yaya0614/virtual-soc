#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdbool.h>
#include "../include/soc_memory_map.h"


typedef struct {
    uint32_t UART_CTRL;
    uint32_t UART_STATUS;
    uint32_t UART_TX_DATA;
    uint32_t UART_RX_DATA;
    uint32_t UART_BAUD_RATE;
    uint32_t UART_INT_EN;
    uint32_t UART_INT_STATUS;
}uart_registers;


void uart_write(uint32_t offset, uint32_t value);
uint32_t uart_read(uint32_t offset);
void uart_receive_signal(uint8_t data);
bool uart_irq_pending(void);



#endif // UART_H