CC=g++
CFLAGS=-lncurses

.PHONY: all clean
all: ao

ao: ao_io.o ao_planet.o ao_ship.o ao.o
	$(CC) -o ao ao_io.o ao_ship.o ao_planet.o ao.o $(CFLAGS)

ao.o:
	$(CC) -c ao.cpp $(CFLAGS)

ao_io.o:
	$(CC) -c ao_io.cpp $(CFLAGS)

ao_ship.o:
	$(CC) -c ao_ship.cpp $(CFLAGS)

ao_planet.o:
	$(CC) -c ao_planet.cpp $(CFLAGS)

clean:
	rm -f *.o *.h.gch
