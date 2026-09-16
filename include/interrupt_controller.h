#ifndef INTERUPT_CONTROLLER_H
#define INTERUPT_CONTROLLER_H
#include <stdbool.h>
#include <stdint.h>

#define IRQ_UART 0
#define IRQ_TIMER 1
#define IRQ_GPIO 2
#define IRQ_NONE   0xFFFFFFFFU

bool interrupt_controller_irq_pending (void);
uint32_t interrupt_controller_get_irq(void);


#endif // INTERUPT_CONTROLLER_H