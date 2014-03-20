#ifndef AUTONOMOUS_H   // collabedit.com/rg9ek
#define AUTONOMOUS_H
#include "DriveTrain.h"
#include "Shooter.h"
#include <Timer.h>

// the auto methods return true when completed

class Autonomous
{
public:
    Autonomous(main_robot* robot);
    ~Autonomous();
    bool moveForward(double dist);
    bool turn();
    bool tilt(double);
    bool releaseClamp();
    bool wormPull();
    bool fire();

    bool timePassed(float time);        //time measured in seconds
    Timer* timer;
    enum State {DRIVE_AIM_WINCH, CLAMP, FIRE, IDLE, DONE};
    State stage;
    State previousStage;

    void updateBasic();

    static const double DISTANCE = 30;
    static const double DEGREES_TURN = 25;
    static const double POSITION_TILT = 45;

};
#endif //AUTONOMOUS_H


