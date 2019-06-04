CC=g++
CFLAGS=

.PHONY: default all clean
default: ao
all: default

ao: main.o ao_io.o
	$(CC) -o ao ao_io.o main.o

main.o:
	$(CC) -c main.cpp

ao_io.o:
	$(CC) -c ao_io.cpp

clean:
	rm *.o 
