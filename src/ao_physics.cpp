#include "ao_physics.h"
#include <math.h>
#include <iostream>

physicsHandler::physicsHandler(int ships, int planets){

    maxShips = ships;
    maxPlanets = planets;

}

// Given the arrays of planets and ships, update them by one step
void physicsHandler::runStep(planet * planetArray, ship * shipArray, traj * trajectory, physInfo * inf){

    // Go through the ships
    for (int i = 0; i < maxShips; i++){

        if (shipArray[i].shouldPhys()){

            float forceX = 0;
            float forceY = 0;

            float x = shipArray[i].getX();
            float y = shipArray[i].getY();
            float rot = shipArray[i].getRot();
            float thr = shipArray[i].getThrust();

            float smallestR = 100000;;
            int closestPlanet = 0;

            int planetSize = 0;

            // Calculate total force from all nearby planets
            for (int j = 0; j < maxPlanets; j++){

                planetSize = planetArray[j].getSize();

                // If the planet has a size (i.e. has been initialised)
                if (planetSize > 0){

                    float r = sqrt(pow(x-planetArray[j].getX(), 2)+pow(y-planetArray[j].getY(), 2)) - planetSize;

                    if (r < physicsCutoff && abs(r) > 0.1){

                        if (r < smallestR){

                            smallestR = r;
                            closestPlanet = j;

                        }

                        float mag = forceScale * pow(planetSize, 2) / r;
                        float angle = atan2(planetArray[j].getY()-y, x-planetArray[j].getX());

                        forceX -= mag * cos(angle);
                        forceY += mag * sin(angle);

                    }

                }

            }

            // Caclulate force from thrust
            forceX -= thrustScale * thr * sin(rot*PI/180);
            forceY -= thrustScale * thr * cos(rot*PI/180);

            shipArray[i].update(forceX, forceY, planetArray[closestPlanet]);

            inf->x = shipArray[i].getX();
            inf->y = shipArray[i].getY();
            inf->vx = shipArray[i].getVelX();
            inf->vy = shipArray[i].getVelY();
            inf->fx = forceX;
            inf->fy = forceY;

        }

    }

}
