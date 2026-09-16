// CPU 怎麼使用 UART
#include "../include/uart_driver.h"
#include "../include/uart.h"
#include "../include/soc_memory_map.h"
#include "../include/mmio.h"
#include "../include/gpio.h"
#include "../include/gpio_driver.h"
#include "../include/firmware.h"
#include <stdio.h>

#define UART_RX_BUF_SIZE 16
static uint8_t rx_buf[UART_RX_BUF_SIZE];
static uint8_t write_idx = 0, read_idx = 0;   // 下一筆資料要寫入(push)的位置

// cpu 要傳資料給 uart，cpu 會呼叫這個函式，uart 會把資料傳給外部設備
void uart_tx(uint8_t data){

    if(!(mmio_read(UART_CTRL_OFFSET + UART0_BASE) & UART_CTRL_TX_EN)) {
        return; // TX not enabled, ignore
    }
    printf("[CPU] UART waiting for TX_READY...\n");
    if (!(mmio_read(UART0_BASE + UART_STATUS_OFFSET) & UART_STATUS_TX_READY)) { 
    }
    printf("[CPU] UART TX_READY, sending data...\n");
    printf("[CPU] UART transmitting: '%c'\n", data);
    mmio_write(UART0_BASE + UART_TX_DATA_OFFSET, data);
};


uint8_t uart_rx(void){
    if(!(mmio_read(UART_CTRL_OFFSET + UART0_BASE) & UART_CTRL_RX_EN)) {
        return 0; // RX not enabled, ignore
    }
    while (!(mmio_read(UART0_BASE + UART_STATUS_OFFSET)
            & UART_STATUS_RX_READY)) { 
    }
    return (uint8_t)mmio_read(UART0_BASE + UART_RX_DATA_OFFSET);
};

static void uart_push_buffer(uint8_t data){
    rx_buf[write_idx] = data;
    write_idx = (write_idx + 1) % UART_RX_BUF_SIZE; 
};

uint8_t uart_pop_buffer(uint8_t *data){
    if(write_idx == read_idx) { // 當 write_idx 和 read_idx 相等，表示兩個指標指向同一格。沒有資料要從 buffer pop
        return false; 
    }
    *data = rx_buf[read_idx];
    read_idx = (read_idx + 1) % UART_RX_BUF_SIZE;
    return true;
};

void uart_irq_handler(void){
    if(mmio_read(UART0_BASE + UART_INT_STATUS_OFFSET) & UART_INT_STATUS_RX_INT_PENDING) {
        uint8_t data = (uint8_t)mmio_read(UART0_BASE + UART_RX_DATA_OFFSET);
        uart_push_buffer(data); 
        mmio_write(UART0_BASE + UART_INT_STATUS_OFFSET, UART_INT_STATUS_RX_INT_PENDING); // Clear RX interrupt
    }
};

