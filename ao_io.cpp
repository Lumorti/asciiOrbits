#include "ao_io.h"
#include <iostream>
#include <sys/ioctl.h>

void charBuffer::drawBuffer(){

	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	int yStart = int((bufferY - w.ws_row) / 2);
	int xStart = int((bufferX - w.ws_col) / 2);

	for (int i = yStart; i < yStart + w.ws_row; i++){

		for (int j = xStart; j < xStart + w.ws_col; j++){

			std::cout << buffer[i][j];

		}

	}

}

void charBuffer::resetBuffer(){

	for (int i = 0; i < bufferY; i++){

		for (int j = 0; j < bufferX; j++){

			buffer[i][j] = '.';

		}

	}

}

void charBuffer::setChar(int x, int y, char to){

	buffer[y][x] = to;

}

void charBuffer::setCharRel(int x, int y, char to){

	buffer[y+int(bufferY/2)][x+int(bufferX/2)] = to;

}

