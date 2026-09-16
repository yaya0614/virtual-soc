#include "../include/timer.h"
#include <stdio.h>
#define TIMER_INT_PENDING (1U << 0)
timer_registers timer0 = {0};

void timer_write(uint32_t offset, uint32_t value) {
    switch (offset){
        case TIMER_CTRL_OFFSET:
            timer0.TIMER_CTRL = value;
            break;
        case TIMER_COUNT_OFFSET:
            timer0.TIMER_COUNT = value;
            break;
        case TIMER_COMPARE_OFFSET:
            timer0.TIMER_COMPARE = value;
            break;
        case TIMER_INT_STATUS_OFFSET:
            timer0.TIMER_INT_STATUS &= ~value; 
            break;
        default:
            break;
    }
}


// 用來跑 timer 這個 hardware module 的邏輯，這個 function 會在每個 CPU step 被呼叫一次
void timer_tick(void) {
    // 只有在 timer enabled 的情況下才會增加 count，並且當 count 等於 compare 時，才會觸發 interrupt
    if(TIMER_CTRL_ENABLE & timer0.TIMER_CTRL) {
        timer0.TIMER_COUNT++;
        if(timer0.TIMER_COUNT == timer0.TIMER_COMPARE) {
            timer0.TIMER_INT_STATUS |= TIMER_INT_PENDING; 
            if(timer0.TIMER_CTRL & TIMER_CTRL_AUTO_RELOAD) { 
                timer0.TIMER_COUNT = 0; 
            } else {
                timer0.TIMER_CTRL &= ~TIMER_CTRL_ENABLE; 
            }
        }
    }
}
bool timer_irq_pending(void){
    return (timer0.TIMER_INT_STATUS != 0) && ((timer0.TIMER_CTRL & TIMER_CTRL_INT_EN) != 0);
}

    
uint32_t timer_read(uint32_t offset) {
    switch (offset){
        case TIMER_CTRL_OFFSET:
            printf("TIMER_CTRL: 0x%08X\n", timer0.TIMER_CTRL);
            return timer0.TIMER_CTRL;
            break;
        case TIMER_COUNT_OFFSET:
            printf("TIMER_COUNT: 0x%08X\n", timer0.TIMER_COUNT);
            return timer0.TIMER_COUNT;
            break;
        case TIMER_COMPARE_OFFSET:
            printf("TIMER_COMPARE: 0x%08X\n", timer0.TIMER_COMPARE);
            return timer0.TIMER_COMPARE;
            break;
        case TIMER_INT_STATUS_OFFSET:
            printf("TIMER_INT_STATUS: 0x%08X\n", timer0.TIMER_INT_STATUS);
            return timer0.TIMER_INT_STATUS;
            break;
        default:
            // Invalid offset, do nothing
            break;
    }
    return 0;
}