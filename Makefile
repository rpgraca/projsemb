# tools
AVRDUDE=avrdude -F -V
OBJCOPY=avr-objcopy
CC=avr-gcc
RM=rm -f
 
# parameters
MCU=atmega328
F_CPU=16000000UL
BIN_FORMAT=ihex
PORT=/dev/ttyUSB0
BAUD=57600
PROTOCOL=arduino
PART=ATMEGA328P
CFLAGS=-Wall -O0 -DF_CPU=$(F_CPU) -mmcu=$(MCU) -Wl,-u,vfprintf -lprintf_flt -lm
PROG=main_testes
 

all: $(PROG).hex

$(PROG).hex: $(PROG).elf
	$(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom $< $@

$(PROG).elf: $(PROG).o MicroKernel/ATmega.o MicroKernel/ListaTarefas.o MicroKernel/MicroKernel.o MicroKernel/Scheduler_Fixo.o MicroKernel/Semaforo.o MicroKernel/Sinais.o MicroKernel/Timers.o uart.o ext_libs.o uart2.o
	$(CC) $(CFLAGS) -o $@ $(PROG).o MicroKernel/ATmega.o MicroKernel/ListaTarefas.o MicroKernel/MicroKernel.o MicroKernel/Scheduler_Fixo.o MicroKernel/Semaforo.o MicroKernel/Sinais.o MicroKernel/Timers.o uart.o ext_libs.o uart2.o

$(PROG).O: $(PROG).c
	$(CC) $(CFLAGS) -o $@ $< -c
MicroKernel/ATmega.o: MicroKernel/ATmega.c
	$(CC) $(CFLAGS) -o $@ $< -c
MicroKernel/ListaTarefas.o: MicroKernel/ListaTarefas.c
	$(CC) $(CFLAGS) -o $@ $< -c
MicroKernel/MicroKernel.o: MicroKernel/MicroKernel.c
	$(CC) $(CFLAGS) -o $@ $< -c
MicroKernel/Scheduler_Fixo.o: MicroKernel/Scheduler_Fixo.c  
	$(CC) $(CFLAGS) -o $@ $< -c
MicroKernel/Semaforo.o: MicroKernel/Semaforo.c  
	$(CC) $(CFLAGS) -o $@ $< -c
MicroKernel/Sinais.o: MicroKernel/Sinais.c  
	$(CC) $(CFLAGS) -o $@ $< -c
MicroKernel/Timers.o: MicroKernel/Timers.c
	$(CC) $(CFLAGS) -o $@ $< -c
uart.o: uart.c
	$(CC) $(CFLAGS) -o $@ $< -c
ext_libs.o: ext_libs.c
	$(CC) $(CFLAGS) -o $@ $< -c
uart2.o: uart2.c
	$(CC) $(CFLAGS) -o $@ $< -c

clean:
	$(RM) ${PROG}.o MicroKernel/*.o ${PROG}.elf ${PROG}.hex
 
upload: ${PROG}.hex
	$(AVRDUDE) -c $(PROTOCOL) -p $(PART) -P $(PORT) \
		-b $(BAUD) -U flash:w:${PROG}.hex
