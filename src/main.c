#include <stdio.h>
#include "../include/gpio.h"
#include "../include/soc_memory_map.h"
#include "../include/timer.h"
#include "../include/mmio.h"
#include "../include/firmware.h"
#include "../include/testbench.h"
#include "../include/cpu.h"


int main() {
    firmware_init(); 
    for(uint32_t tick = 0; tick < 6; tick++) {
        printf("\n--- Tick %d ---\n", tick);
        testbench_step(tick);
        printf("[TESTBENCH] Firmware step\n");
        timer_tick();
        cpu_step(); 
    }
    return 0;
}