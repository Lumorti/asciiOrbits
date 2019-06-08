#ifndef PHYSICS_H
#define PHYSICS_H

#include "ao_ship.h"
#include "ao_planet.h"
#include "ao_const.h"

struct traj {

    int xCoords[maxCoordsInTraj];
    int yCoords[maxCoordsInTraj];
    bool stable;

};

struct physInfo {

    float x;
    float y;
    float vx;
    float vy;
    float fx;
    float fy;

};

class physicsHandler {

    int maxShips = 0;
    int maxPlanets = 0;

    public:

    physicsHandler(int, int);
    void runStep(planet *, ship *, traj *, physInfo *);

};

#endif
