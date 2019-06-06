#include "ao_planet.h"
#include "ao_ship.h"

class charBuffer {

	int h = 24;
	int w = 80;

	int centerX = 0;
	int centerY = 0;

	const float xScale = 1.5;
	const float PI = 3.14159265;
	const float drawCutoff = 100;

	public:

	charBuffer();

	void draw();
	void reset();

	void close();
	void updateSize();
	void updateCenter(int, int);
	void writeChar(int, int, char);
	void writeCharRel(int, int, char);
	void mvCursorRel(int, int);
	void writeStringRel(int, int, const char*);
	void addPlanet(planet);
	void addShip(ship);
	void hideCursor();
	void showCursor();

};
