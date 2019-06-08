#include "ao_planet.h"
#include "ao_ship.h"
#include <string>
#include <iomanip>
#include <sstream>
#include "ao_const.h"


class charBuffer {

	int h = 24;
	int w = 80;

	int centerX = 0;
	int centerY = 0;

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
	void writeStringRel(int, int, std::string);
	void writeString(int, int, std::string);
	void writeFloatToPrec(int, int, float, int);
	void addPlanet(planet);
	void addShip(ship);
	void hideCursor();
	void showCursor();

};
