#ifndef MMIO_H
#define MMIO_H

#include <stdint.h>
uint32_t mmio_read(uint32_t address);
void mmio_write(uint32_t address, uint32_t value);
#endif // MMIO_H