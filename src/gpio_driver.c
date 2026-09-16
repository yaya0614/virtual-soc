#include "../include/gpio_driver.h"
#include "../include/soc_memory_map.h"
#include "../include/gpio.h"
#include "../include/mmio.h"
#include <stdio.h>
#include <stdint.h>


typedef struct {
    uint32_t pin;
    uint8_t value;
} gpio_event_t;

#define GPIO_BUFFER_SIZE 16
static gpio_event_t gpio_event_buffer[GPIO_BUFFER_SIZE];
static uint8_t write_idx = 0, read_idx = 0;


static void gpio_push_buffer(uint32_t pin,uint8_t value){
    gpio_event_buffer[write_idx].pin = pin;
    gpio_event_buffer[write_idx].value = value;
    write_idx = (write_idx + 1) % GPIO_BUFFER_SIZE;
};

bool gpio_pop_buffer(uint32_t *pin, uint8_t *value){
    if (read_idx == write_idx) {
        return false; 
    }
    *pin = gpio_event_buffer[read_idx].pin;
    *value = gpio_event_buffer[read_idx].value;
    read_idx = (read_idx + 1) % GPIO_BUFFER_SIZE;
    return true;
};
void gpio_irq_handler(void){
    uint32_t gpio_status = mmio_read(GPIO_INT_STATUS);
    for(int pin = 0; pin < 32; pin++){
        if(gpio_status & (1U << pin)){ // 此 pin 有發生中斷
            // 我要讀他是 0、1
            uint8_t pin_value = (mmio_read(GPIO_IN) >> pin) & 0x01;
            gpio_push_buffer(pin, pin_value);
        }
    }
    mmio_write(GPIO_INT_STATUS, 0xFFFFFFFFU); // Clear all GPIO interrupts
      
};

void gpio_set_output(uint32_t pin, uint32_t pin_value){
    uint32_t gpio_dir = mmio_read(GPIO_DIR);
    uint32_t gpio_out = mmio_read(GPIO_OUT);
    if(gpio_dir & (1U << pin)){
        mmio_write(GPIO_OUT, pin_value);    
    }
};

int gpio_read_pin(uint8_t pin){
    uint32_t gpio_in = mmio_read(GPIO_IN);
    return (gpio_in & (1U << pin)) ? 1 : 0;
};
