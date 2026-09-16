#ifndef FIRMWARE_H
#define FIRMWARE_H
#include <stdint.h>
void firmware_init(void);
void firmware_step(void);

void gpio_handle(void);
void timer_handle(void);
void uart_handle(void);
void uart_irq_logic(uint8_t data);
void gpio_irq_logic(uint32_t pin, uint8_t value);
void timer_event_logic(void);
#endif // FIRMWARE_H