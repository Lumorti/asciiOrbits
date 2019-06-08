#ifndef SHIP_H
#define SHIP_H
#include "ao_planet.h"
#include "ao_const.h"

class ship {

    float posX = 0;
    float posY = 0;
    float velX = 0;
    float velY = 0;
    int rot = 0;
    int shape = 0;
    int thrust = 0;
    int maxThrust = 3;
    bool hide = false;
    bool phys = true;
    float posXSave = 0;
    float posYSave = 0;
    float velXSave = 0;
    float velYSave = 0;

    public:

    ship();
    ship(int, int);
    bool shouldHide();
    bool shouldPhys();
    float getX();
    float getY();
    int getRot();
    int getShape();
    int getThrust();
    void setRot(int);
    void changeRot(int);
    void setThrust(int);
    void changeThrust(int);
    float getVelX();
    float getVelY();
    void changeVelX(float);
    void changeVelY(float);
    void update(float, float, planet);
    void save();
    void revert();

};

#endif // SHIP_H
