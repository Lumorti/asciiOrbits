#include "ao_io.h"
#include <iostream>
#include <sys/ioctl.h>
#include <curses.h>
#include <math.h>

using namespace std;

// Init the curses terminal
charBuffer::charBuffer(){

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);

}

// Properly reset the terminal
void charBuffer::close(){

	endwin();

}

// Reset the screen to be all spaces
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

// Get the size of the terminal and update the global vars h and w
void charBuffer::updateSize(){

	getmaxyx(stdscr, h, w);

}

// Update where the center coordinate should be
void charBuffer::updateCenter(int x, int y){

	centerX = x;
	centerY = y;

}

// Add a planet to the draw cycle
void charBuffer::addPlanet(planet x){

	int planetSize = x.getSize();
	int planetX = x.getX()+int(w/2)-centerX;
	int planetY = x.getY()+int(h/2)-centerY;

	// Don't draw if further away than the cutoff
	if (pow(centerX-x.getX(), 2)+pow(centerY-x.getY(), 2) > pow(drawCutoff, 2)){return;}

	char planetOuter = x.getOuter();
	char planetInner = x.getInner();

	if (planetSize > 0){

		float angle = 0;
		int x1 = 0; int y = 0;
		int x2 = 0;

		// Start from the top and work downwards
		for (angle = 0; angle <= 180; angle += 30 / planetSize){

			x1 = planetX + int(xScale * planetSize * sin(angle*PI/180));
			x2 = planetX - int(xScale * planetSize * sin(angle*PI/180));
			y = planetY - int(planetSize * cos(angle*PI/180));

			// Draw the circumfrence
			mvwaddch(stdscr, y, x1, planetOuter);
			mvwaddch(stdscr, y, x2, planetOuter);

		}

	}

}

void charBuffer::addShip(ship x){

	if (pow(centerX-x.getX(), 2)+pow(centerY-x.getY(), 2) > drawCutoff){return;}

	if (!x.shouldHide()){

		int shipX = x.getX()+int(w/2)-centerX;
		int shipY = x.getY()+int(h/2)-centerY;
		int shipRot = x.getRot();

		mvwaddch(stdscr, shipY, shipX, 'O');

		int deltaX = int(1.5*sin(shipRot*PI/180));
		int deltaY = int(1.5*cos(shipRot*PI/180));

		int shipThrust = x.getThrust();
		mvwaddch(stdscr, shipY+deltaY, shipX+deltaX, ACS_BULLET);

		for (int i = 1; i < shipThrust+1; i++){

			mvwaddch(stdscr, shipY+i*deltaY, shipX+i*deltaX, ACS_DIAMOND);

		}



	}

}

// Update the screen
void charBuffer::draw(){

	wrefresh(stdscr);

}

// Write a single character to the buffer
void charBuffer::writeChar(int x, int y, char to){

	mvwaddch(stdscr, y, x, to);

}

// Write a single character to the buffer, relative to the center
void charBuffer::writeCharRel(int x, int y, char to){

	mvwaddch(stdscr, y+int(h/2), x+int(w/2), to);

}

// Move the cursor relative to the center
void charBuffer::mvCursorRel(int x, int y){

	wmove(stdscr, y+int(h/2), x+int(w/2));

}

// Write a string to the buffer, relative to the center
void charBuffer::writeStringRel(int x, int y, std::string to){

	mvwaddstr(stdscr, y+int(h/2), x+int(w/2), to.c_str());

}

void charBuffer::writeFloatToPrec(int x, int y, float f, int prec){

	stringstream stream;
	stream << fixed << setprecision(prec) << f;
	string s = stream.str();

	writeString(x, y, s);

}

// Write a string to the buffer
void charBuffer::writeString(int x, int y, std::string to){

	mvwaddstr(stdscr, y, x, to.c_str());

}
