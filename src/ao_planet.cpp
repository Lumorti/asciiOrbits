#include "ao_planet.h"

planet::planet(int asize, int ax, int ay){

	size = asize;
	x = ax;
	y = ay;

}

planet::planet(){

	size = 0;
	x = 0;
	y = 0;

}

int planet::getX(){

	return x;

}

int planet::getY(){

	return y;

}

int planet::getSize(){

	return size;

}
