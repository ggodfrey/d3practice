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
    bool wormPull();
    bool smartFire();

    bool timePassed(float time);        //time measured in seconds
    Timer* timer;
    enum State {DRIVE_AIM_WINCH, SMART_FIRE, BASIC_DRIVE, IDLE, DONE};
    State stage;
    State previousStage;
    main_robot* robot;

    void updateHighGoal();
    void updateBasicDrive();

    static const double DISTANCE = 151;
    static const double DEGREES_TURN = 25;
    static const double HIGHGOAL_AUTOANGLE = 53;

};
#endif //AUTONOMOUS_H


