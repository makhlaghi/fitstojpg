src=./src

objects=main.o ui.o fitsarrayvv.o arr2jpg.o stats.o arraymanip.o

vpath %.h $(src)
vpath %.c $(src)

CC=gcc
CFLAGS=-Wall -W -O -pedantic -I$(src)
LDLIBS=-lcfitsio -pthread -ljpeg -lm

fitstojpg: $(objects) 
	@$(CC) -o fitstojpg $(objects) $(LDLIBS) 
	@rm *.o
#	./fitstojpg -ia.fits

.SILENT: $(objects)

.PHONY: install

install:
	cp ./fitstojpg /usr/local/bin/
