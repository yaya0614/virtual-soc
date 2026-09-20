#include "timer_driver.h"
#include "soc_memory_map.h"
#include "mmio.h"
#include "timer.h"
#include <stdio.h>
static volatile uint32_t timer_event_count = 0;

void timer_irq_handler(void){
    uint32_t timer_status = mmio_read(TIMER0_BASE + TIMER_INT_STATUS_OFFSET);
    if(timer_status & TIMER_INT_PENDING){
        printf("[CPU] Handling timer interrupt\n");
        timer_push_event();
    }
    mmio_write(TIMER0_BASE + TIMER_INT_STATUS_OFFSET, 0x01); 
};

void timer_push_event(void){
    timer_event_count++;
};

bool timer_pop_event(void){
    if (timer_event_count == 0)
        return false;

    timer_event_count--;
    return true;
}

void timer_set_compare(uint32_t compare_value);
void timer_start(void);
void timer_enable_interrupt(void){
    mmio_write(TIMER0_BASE + TIMER_CTRL_OFFSET, mmio_read(TIMER0_BASE + TIMER_CTRL_OFFSET) | TIMER_CTRL_INT_EN);
};
void timer_disable_interrupt(void){};