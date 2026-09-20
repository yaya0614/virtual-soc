#include <stdio.h>
#include "gpio.h"
#include "soc_memory_map.h"
#include "timer.h"
#include "mmio.h"
#include "firmware.h"
#include "testbench.h"
#include "cpu.h"


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