#ifndef SHIP_H
#define SHIP_H

class ship {

    float posX = 0;
    float posY = 0;
    int rot = 0;
    int shape = 0;
    int thrust = 0;
    int maxThrust = 2;
    bool hide = false;
    bool phys = true;

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
    void setX(float);
    void setY(float);

};

#endif // SHIP_H
