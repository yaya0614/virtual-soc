#include "../include/cpu.h"
#include <stdbool.h>
#include "../include/interrupt_controller.h"
#include "../include/firmware.h"
#include "../include/gpio.h"
#include "../include/timer.h"
#include "../include/uart.h"
#include <stdio.h>

void cpu_handle_interrupt(void){
    printf("[CPU] Handling interrupt...\n");
    switch(interrupt_controller_get_irq()){
        case IRQ_UART:
            uart_irq_handler();
            break;
        case IRQ_TIMER:
            timer_irq_handler();
            break;
        case IRQ_GPIO:
            gpio_irq_handler();
            break;
        default:
            break;
    }
};


void cpu_step(void){
    if(interrupt_controller_irq_pending()){
        cpu_handle_interrupt();
    }
    firmware_step();
};  
