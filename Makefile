# The following line avoids deleting intermediate files when done.
.SECONDARY:

PORT := $(shell ./discover-arduino-uno-r3-port)

CC=avr-gcc
CFLAGS=-Wall -Os -mmcu=atmega328p -DF_CPU=16000000UL

.PHONY: burn clean

rtos:
	avr-gcc -Wall -Os -mmcu=atmega2560 -DF_CPU=16000000UL ./deps/src/event_groups.c

burn: blink.hex
	@echo The Arduino UNO r3 is on port "'"$(PORT)"'".
	avrdude -v -patmega328p -carduino -b115200 -D -P $(PORT) -Uflash:w:$<:i

clean:
	rm -f blink.o
	rm -f blink.elf
	rm -f blink.hex
	rm -f blink.s

blink.o: arduino-uno-r3.h atmega328.h

blink.s: arduino-uno-r3.h atmega328.h

%.s: %.c
	$(CC) -c $(CFLAGS) $< -S -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.elf: %.o
	$(CC) $(CFLAGS) $< -o $@

%.hex: %.elf
	avr-objcopy -j .text -j .data -O ihex $< $@
