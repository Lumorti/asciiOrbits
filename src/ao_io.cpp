#include <string>
#include "ao_io.h"
#include <iostream>
#include <sys/ioctl.h>
#include <curses.h>

charBuffer::charBuffer(){

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);

}

void charBuffer::close(){

	endwin();

}

void charBuffer::reset(){

	int h, w;
	getmaxyx(stdscr, h, w);

	for (int i = 0; i < h; i++){

		for (int j = 0; j < w; j++){

			mvwaddch(stdscr, i, j, ' ');

		}

	}

}

void charBuffer::hideCursor(){

	curs_set(0);

}

void charBuffer::showCursor(){

	curs_set(1);

}

void charBuffer::updateSize(){

	getmaxyx(stdscr, h, w);

}

void charBuffer::updateCenter(int x, int y){

	centerX = x;
	centerY = y;

}

void charBuffer::addPlanet(planet x){

	if (x.getSize() > 0){
		mvwaddch(stdscr, x.getY()+int(h/2)-centerY, x.getX()+int(w/2)-centerX, 'x');	
	}

}

void charBuffer::draw(){

	wrefresh(stdscr);

}

void charBuffer::writeChar(int x, int y, char to){

	mvwaddch(stdscr, y, x, to);

}

void charBuffer::writeCharRel(int x, int y, char to){

	mvwaddch(stdscr, y+int(h/2), x+int(w/2), to);

}

void charBuffer::mvCursorRel(int x, int y){

	wmove(stdscr, y+int(h/2), x+int(w/2));

}

void charBuffer::writeStringRel(int x, int y, const char* to){

	mvwaddstr(stdscr, y+int(h/2), x+int(w/2), to);

}
