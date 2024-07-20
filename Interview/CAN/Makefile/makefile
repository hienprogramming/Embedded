# Makefile

TARGET = main
OBJS = main.o system_stm32f4xx.o crc.o

CFLAGS = -Wall -O2 -mcpu=cortex-m4 -mthumb -I.
LDFLAGS = -T stm32f4.ld -nostartfiles

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET).elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin