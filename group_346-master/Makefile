# File:   Makefile                                                                                                                                                                                                                            
# Author: Ryan Wang, Zoher Hussein - Group_346                                                                                                                                                                                                                  
# Date:  10 Oct 2021                                                                                                                                                                                                                         
# Descr:  Makefile for game                                                                                                                                                                                                                   

# Definitions.                                                                                                                                                                                                                                
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr -I../../extra
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.                                                                                                                                                                                                                             
OBall: game.out


# Compile: create object files from C source files.                                                                                                                                                                                           
game.o: game.c displayscreen.h gaming.h ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../utils/pacer.h ../../drivers/ledmat.h ../../drivers/display.h ../../drivers/navswitch.h ../../utils/tinygl.h ../../utils/font.h
	    $(CC) -c $(CFLAGS) $< -o $@

gaming.o: gaming.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/avr/timer.h ../../utils/pacer.h ../../drivers/ledmat.h ../../drivers/display.h ../../drivers/navswitch.h gaming.h
	                         $(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/display.h ../../drivers/ledmat.h ../../drivers/test/system.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

startscreen.o: displayscreen.c displayscreen.h ../../drivers/avr/system.h ../../utils/font.h ../../utils/pacer.h ../../utils/tinygl.h ../../drivers/navswitch.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.                                                                                                                                                                                             
game.out: game.o system.o pio.o system.o timer.o pacer.o ledmat.o display.o navswitch.o tinygl.o font.o displayscreen.o gaming.o
	        $(CC) $(CFLAGS) $^ -o $@ -lm
	        $(SIZE) $@


# Target: clean project.                                                                                                                                                                                                                      
.PHONY: clean
clean:
	        -$(DEL) *.o *.out *.hex


# Target: program project.                                                                                                                                                                                                                    
.PHONY: program
program: game.out
	        $(OBJCOPY) -O ihex game.out game.hex
	        dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start
