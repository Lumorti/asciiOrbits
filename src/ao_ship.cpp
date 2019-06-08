#include "ao_ship.h"
#include <math.h>

ship::ship(){

    hide = true;
    phys = false;

}

ship::ship(int x, int y){

    posX = x;
    posY = y;

}

float ship::getX(){

    return posX;

}

int ship::getThrust(){

    return thrust;

}

bool ship::shouldHide(){

    return hide;

}

bool ship::shouldPhys(){

    return phys;

}

float ship::getY(){

    return posY;

}

int ship::getRot(){

    return rot;

}

int ship::getShape(){

    return shape;

}

float ship::getVelX(){

    return velX;

}

float ship::getVelY(){

    return velY;

}

void ship::setRot(int angle){

    rot = angle;
    if (rot > 360){rot -= 360;}
    else if (rot < 0){rot += 360;}

}

void ship::changeRot(int angle){

    rot += angle;
    if (rot > 360){rot -= 360;}
    else if (rot < 0){rot += 360;}

}

void ship::setThrust(int t){

    if (t <= maxThrust && t >= 0){

        thrust = t;

    }

}

void ship::changeThrust(int t){

    if (thrust+t <= maxThrust && thrust+t >= 0){

        thrust += t;

    }

}

void ship::changeVelX(float xVelChange){

    velX += xVelChange;

}

void ship::changeVelY(float yVelChange){

    velY += yVelChange;

}

// Update the positions based on the forces and closest planet (checking collisions)
void ship::update(float xVelChange, float yVelChange, planet p){

    velX += xVelChange;
    velY += yVelChange;

    // Limit max velocity
    float mag = sqrt(pow(velX, 2) + pow(velY, 2));
    if (mag > velLimit){

        velX -= xVelChange;
        velY -= yVelChange;

    }

    posX += velX;
    posY += velY;

    // Check if inside closest planet
    if (sqrt(pow((posX-p.getX())/xScale, 2)+pow(posY-p.getY(), 2)) <= p.getSize()){

        posX -= velX;
        posY -= velY;

        velX = 0;
        velY = 0;

    }

}
