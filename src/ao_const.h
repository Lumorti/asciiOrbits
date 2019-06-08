#ifndef CONST_H
#define CONST_H

const float PI = 3.14159265;

// Performance
const float drawCutoff = 100;
const float physicsCutoff = 100;
const int refreshDelay = 100;
const int maxShips = 100;
const int maxPlanets = 100;

// World gen
const int minDistance = 20;
const int numPlanets = 50;
const int planetMinCoord = -500;
const int planetMaxCoord = 500;
const int planetMinSize = 3;
const int planetMaxSize = 10;

// Physics
const int maxCoordsInTraj = 100;
const float forceScale = 0.01;
const float thrustScale = 0.1;
const float velLimit = 2;

// Display
const float xScale = 1.6;

#endif // CONST_H
