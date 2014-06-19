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
PROG=main_testes
 

all: $(PROG).hex

$(PROG).hex: $(PROG).elf
	$(OBJCOPY) -O $(BIN_FORMAT) -R .eeprom $< $@

$(PROG).elf: $(PROG).o MicroKernel/ATmega.o MicroKernel/ListaTarefas.o MicroKernel/MicroKernel.o MicroKernel/Scheduler_Fixo.o MicroKernel/Semaforo.o MicroKernel/Sinais.o MicroKernel/Timers.o
	$(CC) $(CFLAGS) -o $@ $(PROG).o MicroKernel/ATmega.o MicroKernel/ListaTarefas.o MicroKernel/MicroKernel.o MicroKernel/Scheduler_Fixo.o MicroKernel/Semaforo.o MicroKernel/Sinais.o MicroKernel/Timers.o

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

clean:
	$(RM) MicroKernel/*.o ${PROG}.elf ${PROG}.hex
 
upload: ${PROG}.hex
	$(AVRDUDE) -c $(PROTOCOL) -p $(PART) -P $(PORT) \
		-b $(BAUD) -U flash:w:${PROG}.hex
