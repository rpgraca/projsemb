# tools
AVRDUDE=avrdude -F -V
OBJCOPY=avr-objcopy
CC=avr-gcc
RM=rm -f
 
# parameters
MCU=atmega328
F_CPU=16000000UL
BIN_FORMAT=ihex
PORT=/dev/ttyACM0
BAUD=115200
PROTOCOL=arduino
PART=ATMEGA328P
CFLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
PROG=uk
 
.SUFFIXES: .elf .hex
 
.c.elf:
	$(CC) $(CFLAGS) -o $@ $<
 
.elf.hex:
	$(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom $< $@
 
.PHONY: all
all: ${PROG}.hex
 
${PROG}.hex: ${PROG}.elf
 
${PROG}.elf: ${PROG}.c
 
.PHONY: clean
clean:
	$(RM) ${PROG}.elf ${PROG}.hex
 
.PHONY: upload
upload: ${PROG}.hex
	$(AVRDUDE) -c $(PROTOCOL) -p $(PART) -P $(PORT) \
		-b $(BAUD) -U flash:w:${PROG}.hex
