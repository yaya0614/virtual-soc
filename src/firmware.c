// CPU firmware 邏輯 
#include "firmware.h"
#include "gpio.h"
#include "gpio_driver.h"
#include "timer.h"
#include "timer_driver.h"
#include "uart_driver.h"
#include "mmio.h"
#include "soc_memory_map.h"
#include "cpu.h"
#include <stdint.h>
#include <stdio.h>

static uint32_t firmware_ticks = 0;
void timer_handle(void){
    if(timer_pop_event()){
        timer_event_logic();
    }
};


void gpio_handle(void){
    uint32_t pin;
    uint8_t value;
    if (gpio_pop_buffer(&pin, &value)) {
        gpio_irq_logic(pin, value);
    }
};

void uart_handle(void){
    uint8_t data;              
    if (uart_pop_buffer(&data)) {
        uart_irq_logic(data);
    }
};

void timer_event_logic(void)
{
    firmware_ticks++;
    printf("[CPU] Timer event logic executed, firmware_ticks: %u\n", firmware_ticks);

    if (firmware_ticks % 1 == 0){
        printf("[CPU] Timer event logic executed gpio_toggle\n");
    }
        // gpio_toggle(0);

    if (firmware_ticks % 2 == 0){
        printf("[CPU] Timer event logic executed uart_send_status\n");
    }
        // uart_send_status();

    if (firmware_ticks % 3 == 0){
        printf("[CPU] Timer event logic executed system_health_check\n");
    }
        // system_health_check();
}

void uart_irq_logic(uint8_t data){
    switch(data) {
        case '0':
            printf("[CPU] UART IRQ Handler: Received 'GPIO0-LOW'\n");
            gpio_set_output(0, 0x00);
            break;
        case '1':
            printf("[CPU] UART IRQ Handler: Received 'GPIO0-HIGH'\n");
            gpio_set_output(0, 0x01); 
            break;
            
        default:
            printf("[CPU] UART IRQ Handler: Received '%c'\n", data);
            break;
    }
};

void gpio_irq_logic(uint32_t pin, uint8_t value){
    switch (pin){
    case 1:
        if(value){
            printf("[CPU] GPIO IRQ Handler: Received 'GPIO1-HIGH'\n");
            uart_tx('1'); 
        }else{
            printf("[CPU] GPIO IRQ Handler: Received 'GPIO1-LOW'\n");
            uart_tx('0'); 
        }
        break;
    case 2:
        if(value){
            printf("[CPU] GPIO IRQ Handler: Received 'GPIO2-HIGH'\n");
            uart_tx('1'); 
        }else{
            printf("[CPU] GPIO IRQ Handler: Received 'GPIO2-LOW'\n");
            uart_tx('0'); 
        }
        break;
    default:
        break;
    }
};

void firmware_init(void){
    // GPIO INIT
    mmio_write(GPIO_INT_EN, 0xFFFFFFFFU); 
    mmio_write(GPIO_INT_STATUS, 0xFFFFFFFFU);
    mmio_write(GPIO_DIR, 0x01); // Set GPIO0 to output, others as input
    
    // USAT INIT
    mmio_write(UART0_BASE + UART_CTRL_OFFSET, UART_CTRL_TX_EN | UART_CTRL_RX_EN); // Enable TX and RX
    mmio_write(UART0_BASE + UART_INT_EN_OFFSET, UART_INT_EN_TX_INT_EN | UART_INT_EN_RX_INT_EN);
    mmio_read(UART0_BASE + UART_CTRL_OFFSET); 
    mmio_read(UART0_BASE + UART_STATUS_OFFSET); 
    
    // TIMER INIT
    mmio_write(TIMER0_BASE + TIMER_CTRL_OFFSET, TIMER_CTRL_ENABLE | TIMER_CTRL_INT_EN | TIMER_CTRL_AUTO_RELOAD); 
    mmio_write(TIMER0_BASE + TIMER_COMPARE_OFFSET, 0x05);
};


void firmware_step(void){
    printf("[CPU] Firmware step executed\n");
    gpio_handle();
    timer_handle();
    uart_handle();
};