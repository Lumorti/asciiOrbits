#ifndef CONST_H
#define CONST_H

const float PI = 3.14159265;

// Performance
const float drawCutoff = 100;
const float physicsCutoff = 100;
const int refreshDelay = 100;

// World gen
const int maxPlanets = 100;
const int maxShips = 100;
const int minDistance = 20;
const int numPlanets = 100;
const int planetMinCoord = -500;
const int planetMaxCoord = 500;
const int planetMinSize = 3;
const int planetMaxSize = 10;

// Physics
const int maxCoordsInTraj = 100;
const float forceScale = 0.03;
const float thrustScale = 0.1;
const float velLimit = 2;

// Display
const float xScale = 1.6;
const int trajEvery = 5;
const int mapScale = 10;

#endif // CONST_H
