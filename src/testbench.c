#include "../include/testbench.h"
#include "../include/uart_driver.h"
#include "../include/gpio_driver.h"
#include "../include/gpio.h"
#include "../include/uart.h"
#include <stdio.h>

void external_uart_rx(uint8_t data){
    printf("[External RX] %c\n", data);
};

void external_uart_tx(uint8_t data){
    printf("[External TX] %c\n", data);
    uart_receive_signal(data);
};

void button_press(uint32_t pin){
    printf("[Button Press] Button %d pressed\n", pin);
    gpio_set_external_input(pin, 1);
    int read_pin = gpio_read_pin(pin);
    printf("[Button Press] GPIO pin %d state after press: %d\n", pin, read_pin);
};

void button_release(uint32_t pin){
    printf("[Button Release] Button %d released\n", pin);
    gpio_set_external_input(pin, 0);
    int read_pin = gpio_read_pin(pin);
    
    printf("[Button Release] GPIO pin %d state after release: %d\n", pin, read_pin);
};


void testbench_step(uint32_t tick){
    printf("[TESTBENCH]\n");
    switch(tick) {
        case 0:
            external_uart_tx('1');
            break;
        case 1:
            external_uart_tx('0');
            break;
        case 2:
            gpio_read_pin(0);
            break;
        case 3:
            button_press(1);
            break;
        case 4:
            button_release(1);
            break;
        default:
            break;
    }
};

