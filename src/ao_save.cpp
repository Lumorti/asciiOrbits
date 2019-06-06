#include "ao_save.h"
#include <dirent.h>

gameLoader::gameLoader(){




}

int gameLoader::getNumSaves(){

    numSaves = 0;

    DIR *dir;
    struct dirent *ent;
    std::string fileName;
    if ((dir = opendir (saveDir.c_str())) != NULL) {

        while ((ent = readdir (dir)) != NULL) {

            fileName = std::string(ent->d_name);
            if (fileName.length() > 4){

                if (fileName.substr(fileName.length()-4, 3) == ".sav"){

                    saveNames[numSaves] = fileName;
                    numSaves++;

                    if (numSaves > maxSaves){break;}

                }

            }

        }

        closedir (dir);

    }

    return numSaves;

}

std::string gameLoader::getSaveName(int saveNum){

    return " ";

}

void gameLoader::save(int saveNum){





}

std::string gameLoader::load(int saveNum){

    currentSave = saveNum;
    return " ";

}
