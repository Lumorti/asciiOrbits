#include <string>

class gameLoader {

    int currentSave = 0;
    std::string saveDir = "./";

    int numSaves = 0;
    const static int maxSaves = 20;
    std::string saveNames[maxSaves];

	public:

	gameLoader();

    int getNumSaves();
    std::string getSaveName(int);
    std::string load(int);
    void save(int);

};
