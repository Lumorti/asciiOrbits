CC=g++
CFLAGS=-lncurses

.PHONY: all clean
all: ao

ao: ao_io.o ao_planet.o ao.o 
	$(CC) $(CFLAGS) -o ao ao_io.o ao.o ao_planet.o

ao.o:
	$(CC) $(CFLAGS) -c ao.cpp

ao_io.o:
	$(CC) $(CFLAGS) -c ao_io.cpp

ao_planet.o:
	$(CC) $(CFLAGS) -c ao_planet.cpp

clean:
	rm *.o *.h.gch 
