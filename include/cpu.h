#ifndef CPU_H
#define CPU_H

void uart_irq_handler(void);
void timer_irq_handler(void);
void gpio_irq_handler(void);
void cpu_handle_interrupt(void);
void cpu_step(void);  
#endif // CPU_H