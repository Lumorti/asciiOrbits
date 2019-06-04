
class charBuffer {

	static const int bufferX = 200;
	static const int bufferY = 200;
	char buffer[bufferY][bufferX];

	public:

	charBuffer();

	void draw();
	void reset();

	void writeChar(int, int, char);
	void writeCharRel(int, int, char);
	void writeStringRel(int, int, char[]);

};
