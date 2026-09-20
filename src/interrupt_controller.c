#include "interrupt_controller.h"
#include "gpio.h"
#include "timer.h"
#include "uart.h"
#include <stdio.h>

bool interrupt_controller_irq_pending (void){
    printf("interrupt irq result %s\n", gpio_irq_pending() || uart_irq_pending() || timer_irq_pending() ? "true" : "false");
    return gpio_irq_pending() || uart_irq_pending() || timer_irq_pending();
};
uint32_t interrupt_controller_get_irq(void){
    if (uart_irq_pending()) {
        return IRQ_UART;
    }

    if (timer_irq_pending()) {
        return IRQ_TIMER;
    }

    if (gpio_irq_pending()) {
        return IRQ_GPIO;
    }

    return IRQ_NONE;
}
    