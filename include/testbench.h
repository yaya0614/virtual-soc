#ifndef TESTBENCH_H
#define TESTBENCH_H
#include <stdint.h>


void external_uart_tx(uint8_t data); // 模擬外部設備傳送資料給 UART
void external_uart_rx(uint8_t data); // 模擬外部設備接收 UART 傳送的資料
void testbench_step(uint32_t tick);
void button_press(uint32_t pin);
void button_release(uint32_t pin);

#endif // TESTBENCH_H