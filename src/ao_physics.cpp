#include "ao_physics.h"
#include <math.h>
#include <iostream>
#include <fstream>

physicsHandler::physicsHandler(int ships, int planets){

    maxShips = ships;
    maxPlanets = planets;

}

// Given the arrays of planets and ships, update them by one step
void physicsHandler::runStep(planet * planetArray, ship * shipArray, traj * trajectory){

    std::ofstream myfile;
    myfile.open ("test.log", std::ios::app);

    // Go through the ships
    for (int i = 0; i < maxShips; i++){

        if (shipArray[i].shouldPhys()){

            myfile << "applying forces to ship " << i << std::endl;

            float forceX = 0;
            float forceY = 0;

            float x = shipArray[i].getX();
            float y = shipArray[i].getY();

            // Calculate total force from all nearby planets
            for (int j = 0; j < maxPlanets; j++){

                if (planetArray[j].getSize() > 0){

                    float r = pow(x-planetArray[j].getX(), 2)+pow(y-planetArray[j].getY(), 2);
                    myfile << " - checking non-zero planet " << j << std::endl;
                    myfile << " - - r =  " << r << std::endl;

                    if (r < pow(physicsCutoff, 2) && r != 0){

                        myfile << " - applying forces from planet " << j << std::endl;

                        float mag = forceScale * pow(planetArray[j].getSize(), 2) / r;
                        float angle = atan2(planetArray[j].getY()-y, x-planetArray[j].getX());

                        forceX += mag * cos(angle);
                        forceY -= mag * sin(angle);

                    }

                }

            }


            myfile << forceX << std::endl;
            myfile << forceY << std::endl;

            myfile << "x before: " << x << std::endl;

            shipArray[i].setX(x + forceX);
            shipArray[i].setY(y + forceY);

            myfile << "x after: " << shipArray[i].getX() << std::endl;

        }

    }

    myfile.close();

}
