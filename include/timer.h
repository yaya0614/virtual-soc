#ifndef TIMER_H
#define TIMER_H


#define TIMER_CTRL_OFFSET        0x00U
#define TIMER_COUNT_OFFSET       0x04U
#define TIMER_COMPARE_OFFSET     0x08U
#define TIMER_INT_STATUS_OFFSET  0x0CU

// define bit masks for the control register
#define TIMER_CTRL_ENABLE        (1U << 0)
#define TIMER_CTRL_INT_EN        (1U << 1)
#define TIMER_CTRL_AUTO_RELOAD   (1U << 2)
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t TIMER_CTRL;
    uint32_t TIMER_COUNT;
    uint32_t TIMER_COMPARE;
    uint32_t TIMER_INT_STATUS;
}timer_registers;

void timer_write(uint32_t offset, uint32_t value);
uint32_t timer_read(uint32_t offset);
void timer_tick(void);
void timer_clear_interrupt(void);
bool timer_irq_pending(void);


#endif