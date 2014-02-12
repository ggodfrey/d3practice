#ifndef MAIN_H
#define MAIN_H

#include <IterativeRobot.h>
#include <Joystick.h>
#include "DriveTrain.h"
#include <DigitalInput.h>
#include <Relay.h>
#include "Pneumatics.h"
#include "Shifter.h"
#include "Shooter.h"
#include "FunctionRegistry.h"
#include "Sensors.h"

class main_robot: public IterativeRobot
{
public:
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
};


#endif // MAIN_H
