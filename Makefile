MCU=atmega8
F_CPU=12000000
CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude

CFLAGS=-Wall -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -Iusbdrv
OBJFLAGS=-j .text -j .data -O ihex
FFLAGS=-p ATmega8 -P /dev/ttyACM0 -c stk500v1 -b 19200 -U flash:w:main.hex

SOURCES=$(wildcard src/usbdrv/*.c src/*.c)
OBJECTS=$(SOURCES:%.c=%.o)
OBJECTS+=src/usbdrv/usbdrvasm.o

all: main.hex

%.hex: %.elf
	$(OBJCOPY) $(OBJFLAGS) $< $@

main.elf: ${OBJECTS}
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f src/*.o *.hex *.elf src/usbdrv/*.o

flash:
	$(AVRDUDE) $(FFLAGS)