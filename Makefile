CC = clang
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = mini_soc

SRC = src/main.c \
      src/cpu.c \
      src/firmware.c \
      src/interrupt_controller.c \
      src/testbench.c \
      src/mmio.c \
      src/gpio.c \
      src/gpio_driver.c \
      src/timer.c \
      src/timer_driver.c \
      src/uart.c \
      src/uart_driver.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)