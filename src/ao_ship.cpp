#include "ao_ship.h"

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

void ship::setX(float newX){

    posX = newX;

}

void ship::setY(float newY){

    posY = newY;

}
