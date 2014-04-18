src=./src

objects=main.o ui.o fitsarrayvv.o arr2jpg.o stats.o

vpath %.h $(src)
vpath %.c $(src)

CC=gcc
CFLAGS=-Wall -W -O -pedantic -I$(src)
LDLIBS=-lcfitsio -pthread -ljpeg -lm

mockgals: $(objects) 
	@$(CC) -o fits2jpg $(objects) $(LDLIBS) 
	@rm *.o
	./fits2jpg -cc

.SILENT: $(objects)
