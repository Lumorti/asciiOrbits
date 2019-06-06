#ifndef PLANET_H
#define PLANET_H

class planet {

	int size;
	int x;
	int y;
	char outerLetter;
	char innerLetter;

	public:

	planet();
	planet(int, int, int);

	int getX();
	int getY();
	int getSize();
	char getOuter();
	char getInner();

};

#endif // PLANET_H
