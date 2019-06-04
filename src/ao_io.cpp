#include "ao_io.h"
#include <iostream>
#include <sys/ioctl.h>
#include <string.h>
#include <curses.h>

charBuffer::charBuffer(){

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);

}

void charBuffer::reset(){

	int h, w;
	getmaxyx(stdscr, h, w);

	for (int i = 0; i < h; i++){

		for (int j = 0; j < w; j++){

			mvwaddch(stdscr, i, j, '.');

		}

	}


}

void charBuffer::draw(){

	wrefresh(stdscr);

}

void charBuffer::writeChar(int x, int y, char to){

	mvwaddch(stdscr, y, x, to);

}

void charBuffer::writeCharRel(int x, int y, char to){

	int h, w;
	getmaxyx(stdscr, h, w);
	mvwaddch(stdscr, y+int(h/2), x+int(w/2), to);

}

void charBuffer::writeStringRel(int x, int y, char to[]){

	int h, w;
	getmaxyx(stdscr, h, w);
	mvwaddstr(stdscr, y+int(h/2), x+int(w/2), to);

}
