#ifndef SOC_MEMORY_MAP_H
#define SOC_MEMORY_MAP_H

// define GPIO
#define GPIO0_BASE 0x40000000U
#define GPIO0_SIZE 0x1000U

// define TIMER
#define TIMER0_BASE 0x40003000U
#define TIMER0_SIZE 0x1000U

// define UART
#define UART0_BASE 0x40006000U
#define UART0_SIZE 0x1000U


#define TIMER_CTRL_OFFSET        0x00U
#define TIMER_COUNT_OFFSET       0x04U
#define TIMER_COMPARE_OFFSET     0x08U
#define TIMER_INT_STATUS_OFFSET  0x0CU


#define UART_CTRL_OFFSET        0x00U
#define UART_STATUS_OFFSET      0x04U
#define UART_TX_DATA_OFFSET     0x08U
#define UART_RX_DATA_OFFSET     0x0CU
#define UART_BAUD_RATE_OFFSET   0x10U
#define UART_INT_EN_OFFSET      0x14U
#define UART_INT_STATUS_OFFSET  0x18U


// CTRL
#define UART_CTRL_TX_EN    (1 << 0)
#define UART_CTRL_RX_EN    (1 << 1)

// STATUS 表示 UART 的狀態，TX_READY 1 表示可以傳送資料，RX_READY 1 表示有資料可以接收
#define UART_STATUS_TX_READY   (1 << 0)
#define UART_STATUS_RX_READY   (1 << 1)

// INT_EN
#define UART_INT_EN_TX_INT_EN    (1 << 0)
#define UART_INT_EN_RX_INT_EN    (1 << 1)

// INT_STATUS 有沒有要處理的中斷，TX_INT_PENDING 表示有傳送中斷，RX_INT_PENDING 表示有接收中斷
#define UART_INT_STATUS_TX_INT_PENDING    (1 << 0)
#define UART_INT_STATUS_RX_INT_PENDING    (1 << 1)

#endif