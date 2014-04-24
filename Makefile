src=./src

objects=main.o ui.o fitsarrayvv.o arr2jpg.o stats.o

vpath %.h $(src)
vpath %.c $(src)

CC=gcc
CFLAGS=-Wall -W -O -pedantic -I$(src)
LDLIBS=-lcfitsio -pthread -ljpeg -lm

fits2jpg: $(objects) 
	@$(CC) -o fits2jpg $(objects) $(LDLIBS) 
	@rm *.o
#	./fits2jpg -ib.fits

.SILENT: $(objects)

.PHONY: install

install:
	cp ./fits2jpg /usr/local/bin/
