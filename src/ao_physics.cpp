#include "ao_physics.h"
#include <math.h>
#include <iostream>

physicsHandler::physicsHandler(int ships, int planets){

    maxShips = ships;
    maxPlanets = planets;

}

struct forceInfo {

    float x;
    float y;
    int cloestIndex;

};

struct int2 {

    int x;
    int y;

};

forceInfo getForces(ship ship, planet * planetArray){

    float forceX = 0;
    float forceY = 0;

    float x = ship.getX();
    float y = ship.getY();
    float rot = ship.getRot();
    float thr = ship.getThrust();

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

                float mag = forceScale * planetSize / r;
                float angle = atan2(planetArray[j].getY()-y, x-planetArray[j].getX());

                forceX -= mag * cos(angle);
                forceY += mag * sin(angle);

            }

        }

    }

    // Caclulate force from thrust
    forceX -= thrustScale * pow(thr, 2) * sin(rot*PI/180);
    forceY -= thrustScale * pow(thr, 2) * cos(rot*PI/180);

    forceInfo forces;
    forces.x = forceX;
    forces.y = forceY;
    forces.cloestIndex = closestPlanet;

    return forces;

}

// Given the arrays of planets and ships, update them by one step
void physicsHandler::runStep(planet * planetArray, ship * shipArray, traj * trajectory, physInfo * inf){

    // Go through the ships
    for (int i = 0; i < maxShips; i++){

        if (shipArray[i].shouldPhys()){

            forceInfo forces = getForces(shipArray[i], planetArray);

            shipArray[i].update(forces.x, forces.y, planetArray[forces.cloestIndex]);

            inf->x = shipArray[i].getX();
            inf->y = shipArray[i].getY();
            inf->vx = shipArray[i].getVelX();
            inf->vy = shipArray[i].getVelY();
            inf->fx = forces.x;
            inf->fy = forces.y;

        }

    }

    // For the player ship, generate the trajectory
    shipArray[0].save();
    shipArray[0].setThrust(0);
    int i = 0;
    int j = 0;
    while (i < maxCoordsInTraj) {

        if (j % trajEvery == 0){

            forceInfo forces = getForces(shipArray[0], planetArray);
            shipArray[0].update(forces.x, forces.y, planetArray[forces.cloestIndex]);

            trajectory->xCoords[i] = shipArray[0].getX();
            trajectory->yCoords[i] = shipArray[0].getY();
            i++;

        }

        j++;

    }
    shipArray[0].revert();

}
