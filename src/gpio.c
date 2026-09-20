#include "gpio.h"
#include <stdio.h>
GPIO_Registers gpio0 = {0};

uint32_t gpio_read(uint32_t offset) {
    switch (offset) {
        case 0x00:
            return gpio0.DIR;
        case 0x04:
            return gpio0.OUT;
        case 0x08:
            return gpio0.IN;
        case 0x0C:
            return gpio0.INT_EN;
        case 0x10:
            return gpio0.INT_STATUS;
        default:
            return 0; 
    }
}

void gpio_write(uint32_t offset, uint32_t value) {
    switch (offset) {
        case 0x00:
            gpio0.DIR = value;
            break;
        case 0x04:
            if (!((~gpio0.DIR) & value)) { 
                gpio0.OUT = value;
                printf("GPIO Write: Successfully wrote 0x%08X to OUT register\n", gpio0.OUT);
            }else {
                printf("Error: Attempt to write to an input pin\n");
            }
            break;
        case 0x0C:
            gpio0.INT_EN = value;
            break;
        case 0x10:
            // gpio0.INT_STATUS ^= value;  這樣寫會有風險，當 status 0000 value 0001，會變成 0001，這樣就會把原本的 status bit 1 清掉，變成 0000，這樣就會有問題 => 產生假資料
            gpio0.INT_STATUS &= ~value; // 只要有0就會清掉，這樣就不會有假資料
            break;
        default:
            // Invalid offset, do nothing
            break;
    }
}
void gpio_set_external_input(uint32_t pin, int value) {
    uint32_t pin_mask = 1U << pin;
    if ((gpio0.DIR & pin_mask) != 0) { // 用輸出的反邏輯來檢查邊界條件，若輸入值與輸出方向有重疊，表示有錯誤
        return;
    } 
    uint32_t previous = gpio0.IN;
    if(value){
        gpio0.IN |= pin_mask;    // 只把這一個 pin 設成 1，其他 pin 保持原樣
    }else{
        gpio0.IN &= ~pin_mask;   
    }
    uint32_t changed = previous ^ gpio0.IN;
    if(changed) { 
        gpio0.INT_STATUS |= changed & gpio0.INT_EN; 
    }
    
}
void gpio_detect_edge(uint32_t previous, uint32_t current, int pin_bit) {
    uint32_t mask = 1U << pin_bit;
    uint32_t changed = previous ^ current;
    if (changed & mask) {   
        if(current & mask) {
            printf("Rising edge detected on pin %d\n", pin_bit);
            
        } else {
            printf("Falling edge detected on pin %d\n", pin_bit);
        }
    }
}

void gpio_status(void) {
    printf("GPIO Status:\n");
    for (int i = 0; i < 32; i++) {
        printf("Pin %d: Direction: %s, GPIO_Status: %s\n", i, (gpio0.DIR & (1U << i)) ? "Output" : "Input", (gpio0.DIR & (1U << i)) ? (gpio0.OUT & (1U << i)) ? "1" : "0" : (gpio0.IN & (1U << i)) ? "1" : "0");
    }
};

void gpio_status_with_interrupt(void) {
    printf("GPIO Status with Interrupt:\n");
    for (int i = 0; i < 32; i++) {
        printf("Pin %d: Direction: %s, GPIO_Status: %s, Interrupt Enabled: %s, Interrupt Status: %s\n", 
            i, 
            (gpio0.DIR & (1U << i)) ? "Output" : "Input", 
            (gpio0.DIR & (1U << i)) ? (gpio0.OUT & (1U << i)) ? "1" : "0" : (gpio0.IN & (1U << i)) ? "1" : "0",
            (gpio0.INT_EN & (1U << i)) ? "Yes" : "No",
            (gpio0.INT_STATUS & (1U << i)) ? "Yes" : "No"
        );
    }
}

bool gpio_irq_pending(void) {
    return gpio0.INT_STATUS != 0;
}
