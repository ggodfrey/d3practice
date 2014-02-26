#ifndef AUTONOMOUS_H   // collabedit.com/rg9ek
#define AUTONOMOUS_H
#include "DriveTrain.h"
#include "Shooter.h"
#include <Timer.h>
class Autonomous
{
public:
    Autonomous(main_robot* robot);
    ~Autonomous();
    void moveForward();
    void turn();
    void tilt();
    void releaseClamp();
    void shootBall();

    bool timePassed(float time);        //time measured in seconds
//  void vision();                      //probably connected to tilt
//  double getTime();                   // might not be needed at the moment
//    DriveTrain* drive;
//    Shooter* shoot;
    Timer* timer;
    enum State {DRIVING, TURNING, AIMING, SHOOTING, IDLE};
    State stage;
    State previousStage;

    void update();

    static const double DISTANCE = 10;
    static const double DEGREES_TURN = 25;
    static const double POSITION_TILT = 25;

};
#endif //AUTONOMOUS_H


