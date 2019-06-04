CC=g++
CFLAGS=-lncurses

.PHONY: all clean
all: ao

ao: ao.o ao_io.o
	$(CC) $(CFLAGS) -o ao ao_io.o ao.o

ao.o:
	$(CC) $(CFLAGS) -c ao.cpp

ao_io.o:
	$(CC) $(CFLAGS) -c ao_io.cpp

clean:
	rm *.o *.h.gch 
