#ifndef GPIO_H
#define GPIO_H
#include "soc_memory_map.h"

#define GPIO_DIR_OFFSET         0x00U
#define GPIO_OUT_OFFSET         0x04U
#define GPIO_IN_OFFSET          0x08U
#define GPIO_INT_EN_OFFSET      0x0CU
#define GPIO_INT_STATUS_OFFSET  0x10U

#define GPIO_DIR        (GPIO0_BASE + GPIO_DIR_OFFSET)
#define GPIO_OUT        (GPIO0_BASE + GPIO_OUT_OFFSET)
#define GPIO_IN         (GPIO0_BASE + GPIO_IN_OFFSET)
#define GPIO_INT_EN     (GPIO0_BASE + GPIO_INT_EN_OFFSET)
#define GPIO_INT_STATUS (GPIO0_BASE + GPIO_INT_STATUS_OFFSET)
#include <stdint.h>
#include <stdbool.h>
// offset 0x00 → DIR
// offset 0x04 → OUT
// offset 0x08 → IN
// offset 0x0C → INT_EN
// offset 0x10 → INT_STATUS

typedef struct {
    uint32_t DIR;
    uint32_t OUT;
    uint32_t IN;

    uint32_t INT_EN; // interrupt enable register 中斷致能腳
    uint32_t INT_STATUS; // interrupt status register 中斷狀態腳 主要針對 Input pin 來紀錄是否有變化
}GPIO_Registers;

uint32_t gpio_read(uint32_t offset);
// 設定 GPIO 寄存器的值，根據 offset 來決定要寫入哪個寄存器
void gpio_write(uint32_t offset, uint32_t value);
// 顯示 GPIO 的狀態，包括每個 pin 的方向和狀態
void gpio_status(void);
// setting input 值
void gpio_set_external_input(uint32_t pin, int value);
// 偵測 GPIO pin 的邊緣變化，previous 是前一次的值，current 是目前的值，pin_bit 是要偵測的 pin 位元
void gpio_detect_edge(uint32_t previous, uint32_t current, int pin_bit);
void gpio_status_with_interrupt(void);
// 判斷當前是否還有未處理的 GPIO 中斷，若有則回傳 true，否則回傳 false
bool gpio_irq_pending(void);

#endif