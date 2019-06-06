CC=g++
CFLAGS=-lncurses -lstdc++fs
SRC=$(wildcard *.cpp)

.PHONY: ao clean

ao: $(SRC)
	$(CC) -o ao $^ $(CFLAGS)

clean:
	rm -f *.o *.h.gch
