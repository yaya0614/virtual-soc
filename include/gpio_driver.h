#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H
#include <stdint.h>
#include <stdbool.h>
void gpio_irq_handler(void);
void gpio_set_output(uint32_t pin, uint32_t pin_value);
int gpio_read_pin(uint8_t pin);
static void gpio_push_buffer(uint32_t pin,uint8_t value);
bool gpio_pop_buffer(uint32_t *pin, uint8_t *value);

#endif // GPIO_DRIVER_H