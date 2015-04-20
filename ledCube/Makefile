#==========================
#
#  makefile for attiny2313
#
#  2015.02 - Samuel Munz
# 
#==========================
MCU=attiny2313
avrdude_name=t2313

# Processor frequency.
F_CPU =  8000000UL
#         F_CPU =  1000000UL
#         F_CPU =  8000000UL
#         F_CPU = 12000000UL
#         F_CPU = 16000000UL
#         F_CPU = 20000000UL

CC=avr-gcc
OBJCOPY=avr-objcopy
#==========================
#Programmer
#usbasp von http://www.fischl.de/usbasp/
PROGRAMMER = -c usbasp

#==========================
# optimeze 3 :
CFLAGS  = -g -mmcu=$(MCU) -Wall -Wstrict-prototypes -O3 -mcall-prologues -DF_CPU=$(F_CPU) 
#==========================
all: main.hex
#==========================
help: 
	clear
	@echo
	@echo "Moegliche Befehle:"
	@echo "		make - compiliert Dein Programm und erzeugt die .hex-Datei"
	@echo "		make all - wie make"
	@echo "		make load - compiliert Dein Programm und schiebt es in den AVR"
	@echo "		make clean - loescht die beim Compilieren erzeugten Dateien"
	@echo
	@echo "		make help - zeigt diesen Hilfetext"
	@echo
	@echo "		make rdfuses - gibt Dir Informationen ueber die gesetzten Fusebits und mehr"
	@echo "		make wrfuse4mhz - internen Oszillator auf 4 MHz setzen"
	@echo "		make wrfuse8mhz - internen Oszillator auf 8 MHz setzen"
	@echo "		make wrfuse8mhz_clkout- internen Oszillator auf 8 MHz setzenclk out PD2"
	@echo "		make wrfusedefaults - Fuses auf Werkseinstellungen zuruecksetzen"
	@echo
	
#-------------------
main.hex : main.out 
	$(OBJCOPY) -R .eeprom -O ihex main.out main.hex 
main.out : main.o 
	$(CC) $(CFLAGS) -o main.out -Wl,-Map,main.map main.o 
main.o : main.c 
	$(CC) $(CFLAGS) -Os -c main.c
	
#------------------
load: main.hex
	avrdude -p $(avrdude_name) $(PROGRAMMER) -e -U flash:w:"main.hex"
	

#-------------------
# fuse byte settings attiny2313:
# Werkseinstellungen sind:
#   
#  Low Fuse      	= 0x64 
#  High Fuse     	= 0xdf
#  Extended Fuse 	= 0xff
#
#lfuse 	A4
#lfuse 24
# internen Oszillator setzen:
#  4 MHz: Low Fuse = 0x62 
#  8 MHz: Low Fuse = 0x64 

#  Check this with make rdfuses
rdfuses:
	avrdude -p t2313 $(PROGRAMMER) -v -q	

# Fusebits zu Werkseinstellungen zuruecksetzen
wrfusedefaults:
	avrdude -p $(avrdude_name) $(PROGRAMMER) -u -v -U lfuse:w:0x64:m
	avrdude -p $(avrdude_name) $(PROGRAMMER) -u -v -U hfuse:w:0xdf:m
	avrdude -p $(avrdude_name) $(PROGRAMMER) -u -v -U efuse:w:0xff:m
	
# Frequenz des internen Oszillators auf 4 MHz setzen
wrfuse4mhz:
	avrdude -p $(avrdude_name) $(PROGRAMMER) -u -v -U lfuse:w:0x62:m

# Frequenz des internen Oszillators auf 8 MHz setzen
wrfuse8mhz:
	avrdude -p $(avrdude_name) $(PROGRAMMER) -u -v -U lfuse:w:0xE4:m

wrfuse8mhz_clkout:
	avrdude -p $(avrdude_name) $(PROGRAMMER) -u -v -U lfuse:w:0xA4:m

#-------------------
clean:
	rm -f *.o *.map *.out *.hex
	
#-------------------
