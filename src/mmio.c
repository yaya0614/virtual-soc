#include "mmio.h"
#include "gpio.h"
#include "timer.h"
#include "uart.h"
#include <stdio.h>
#include "soc_memory_map.h"

void mmio_write(uint32_t address, uint32_t value) {
    if (address >= GPIO0_BASE && address < (GPIO0_BASE + GPIO0_SIZE)) { // GPIO Range
        uint32_t offset = address - GPIO0_BASE;
        gpio_write(offset, value);
    } else if (address >= TIMER0_BASE && address < (TIMER0_BASE + TIMER0_SIZE)) { // Timer Range
        uint32_t offset = address - TIMER0_BASE;
        timer_write(offset, value);
    }else if (address >= UART0_BASE && address < (UART0_BASE + UART0_SIZE)) { // UART Range
        uint32_t offset = address - UART0_BASE;
        uart_write(offset, value);
    } 
    else {
        printf("MMIO Write: Invalid address 0x%08X\n", address);
    }
}

uint32_t mmio_read(uint32_t address) {
    if (address >= GPIO0_BASE && address < (GPIO0_BASE + GPIO0_SIZE)) { // GPIO Range
        uint32_t offset = address - GPIO0_BASE;
        uint32_t value = gpio_read(offset);
        // printf("MMIO Read : Address 0x%08X, Value 0x%08X\n", address, value);
        return value;
    } else if (address >= TIMER0_BASE && address < (TIMER0_BASE + TIMER0_SIZE)) { // Timer Range
        uint32_t offset = address - TIMER0_BASE;
        uint32_t value = timer_read(offset);
        // printf("MMIO Read Timer: Address 0x%08X, Value 0x%08X\n", address, value);
        return value;
    }else if (address >= UART0_BASE && address < (UART0_BASE + UART0_SIZE)) { // UART Range
        uint32_t offset = address - UART0_BASE;
        uint32_t value = uart_read(offset);
        // printf("MMIO Read UART: Address 0x%08X, Value 0x%08X\n", address, value);
        return value;
    } 
    else {
        printf("MMIO Read: Invalid address 0x%08X\n", address);
        return 0; // Return a default value for invalid addresses
        // Handle other MMIO ranges or invalid addresses
    }
}

