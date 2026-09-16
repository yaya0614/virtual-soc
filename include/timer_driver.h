#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H
#include <stdint.h>
#include <stdbool.h>
#define TIMER_INT_PENDING (1U << 0) // 0x01的意思

void timer_irq_handler(void);
void timer_set_compare(uint32_t compare_value);
void timer_start(void);
void timer_enable_interrupt(void);
void timer_disable_interrupt(void);
void timer_push_event(void);
bool timer_pop_event(void);

#endif // TIMER_DRIVER_H