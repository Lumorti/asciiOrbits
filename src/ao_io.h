
class charBuffer {

	static const int bufferX = 200;
	static const int bufferY = 200;
	char buffer[bufferY][bufferX];

	public:

	void drawBuffer();
	void resetBuffer();

	void setChar(int, int, char);
	void setCharRel(int, int, char);

};
