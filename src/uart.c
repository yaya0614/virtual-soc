// 實際模擬 uart hardware model 動作
#include "uart.h"
#include "soc_memory_map.h"
#include "testbench.h"
#include <stdio.h>

// static 表示只有 uart.c 可以改變 uart0裡面的值，其他檔案都需要透過 uart_write() 來改變 uart0 裡面的值，這樣可以避免其他檔案直接改變 uart0 裡面的值，造成不可預期的行為
// uart.ctrl = 123;     main.c 不行這樣改
static uart_registers uart0 = {
    .UART_CTRL = 0,
    .UART_STATUS = UART_STATUS_TX_READY, // Initially ready to transmit
    .UART_TX_DATA = 0,
    .UART_RX_DATA = 0,
    .UART_BAUD_RATE = 0,
    .UART_INT_EN = 0,
    .UART_INT_STATUS = 0
};
void uart_write(uint32_t offset, uint32_t value) {
    switch (offset) {
        case UART_CTRL_OFFSET: 
            uart0.UART_CTRL = value ;
            break;
        case UART_STATUS_OFFSET: 
            uart0.UART_STATUS = value;
            break;
        case UART_TX_DATA_OFFSET:
            if (!(uart0.UART_CTRL & UART_CTRL_TX_EN)) {
                break;
            }
            uart0.UART_TX_DATA = value & 0xFFU;
            uart0.UART_STATUS &= ~UART_STATUS_TX_READY;
            external_uart_rx((uint8_t)uart0.UART_TX_DATA);

            uart0.UART_STATUS |= UART_STATUS_TX_READY;

            break;
        case UART_RX_DATA_OFFSET: 
            break;
        case UART_BAUD_RATE_OFFSET:
            uart0.UART_BAUD_RATE = value;
            break;
        case UART_INT_EN_OFFSET: 
            uart0.UART_INT_EN = value & (UART_INT_EN_TX_INT_EN | UART_INT_EN_RX_INT_EN);
            break;
        case UART_INT_STATUS_OFFSET: 
            uart0.UART_INT_STATUS &= ~value;
            break;
        default:
            break;
    }
}


uint32_t uart_read(uint32_t offest){
    switch (offest)
    {
    case UART_CTRL_OFFSET:
        return uart0.UART_CTRL;
    case UART_STATUS_OFFSET:
        return uart0.UART_STATUS;
    case UART_TX_DATA_OFFSET:
        return uart0.UART_TX_DATA;
    case UART_RX_DATA_OFFSET:
        uart0.UART_STATUS &= ~UART_STATUS_RX_READY;
        return uart0.UART_RX_DATA;
    case UART_BAUD_RATE_OFFSET:
        return uart0.UART_BAUD_RATE;
    case UART_INT_EN_OFFSET:
        return uart0.UART_INT_EN;
    case UART_INT_STATUS_OFFSET:
        return uart0.UART_INT_STATUS;
    default:
        return 0; 
    }
}   
    
bool uart_irq_pending(void){
    printf("[UART] Checking IRQ pending: INT_STATUS=0x%08X, INT_EN=0x%08X\n", uart0.UART_INT_STATUS, uart0.UART_INT_EN);
    return (uart0.UART_INT_STATUS & uart0.UART_INT_EN) != 0;
};

void uart_receive_signal(uint8_t data){
    printf("[UART] receive_signal start\n");

    printf("[UART] CTRL = 0x%08X\n", uart0.UART_CTRL);
    printf("[UART] STATUS = 0x%08X\n", uart0.UART_STATUS);
    if(!(uart0.UART_CTRL & UART_CTRL_RX_EN)) {
        return; // RX not enabled, ignore
    }
    printf("[UART] RX_EN is enabled\n");
    if (uart0.UART_STATUS & UART_STATUS_RX_READY) { // UART_STATUS_RX_READY = 1 表示 UART 的 receive buffer 已經有資料，還沒被 CPU 讀取
        printf("[UART] RX buffer still occupied\n");
        return;
    }
    printf("[UART] RX_READY can receive: '%c'\n", data); // UART 硬體接收到資料
    uart0.UART_RX_DATA = data;
    uart0.UART_STATUS |= UART_STATUS_RX_READY;
    
    uart0.UART_INT_STATUS |= UART_INT_STATUS_RX_INT_PENDING;
    printf("[UART] RX interrupt pending\n");
};
