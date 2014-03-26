#ifndef MAIN_H
#define MAIN_H

#include <IterativeRobot.h>
#include <Joystick.h>
#include <DigitalInput.h>
#include <Relay.h>
#include "DriveTrain.h"
#include "Pneumatics.h"
#include "Shifter.h"
#include "Shooter.h"
#include "FunctionRegistry.h"
#include "Sensors.h"
//#include "Netcom.h"
#include "Autonomous.h"
#include "vision/vision.h"

class main_robot: public IterativeRobot
{
public:
    static const int GLIDE_THRESHOLD=30;
    static const int GLIDE_INCREMENT=20;
    static const int GLIDE_ITERATIONS=2;

    main_robot();
    ~main_robot();
    void RobotInit();
    void TeleopInit();
    void AutonomousInit();
    void TestInit();
    void DisabledInit();
    void TeleopPeriodic();
    void AutonomousPeriodic();
    void DisabledPeriodic();
    void TestPeriodic();
    SmoothJoystick* driverJoy;
    SmoothJoystick* gunnerJoy;
    Pneumatics* pnum;
    Shifter* shift;
    DriveTrain* drive;
    Shooter* shoot;
    FunctionRegistry* update;
    Sensors* sensors;
//    Netcom* netcom;
    Autonomous* autoBot;
    
    vision* engine;
    void init_vision();
    void stop_vision();
    
};


#endif // MAIN_H
