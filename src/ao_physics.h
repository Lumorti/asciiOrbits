#include "ao_ship.h"
#include "ao_planet.h"

const int maxCoordsInTraj = 100;

struct traj {

    int xCoords[maxCoordsInTraj];
    int yCoords[maxCoordsInTraj];
    bool stable;

};

class physicsHandler {

    const float physicsCutoff = 100;
    const float forceScale = 1;

    int maxShips = 0;
    int maxPlanets = 0;

    public:

    physicsHandler(int, int);
    void runStep(planet *, ship *, traj *);

};
