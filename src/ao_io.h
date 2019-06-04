#include "ao_planet.h"

class charBuffer {

	static const int bufferX = 200;
	static const int bufferY = 200;
	char buffer[bufferY][bufferX];

	public:

	charBuffer();

	void draw();
	void reset();

	void close();
	void writeChar(int, int, char);
	void writeCharRel(int, int, char);
	void mvCursorRel(int, int);
	void writeStringRel(int, int, const char*);
	void addPlanet(planet);

};
