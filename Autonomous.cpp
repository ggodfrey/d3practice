#include "Autonomous.h"
#include "main.h"
#include "ports.h"
#include "612.h"

Autonomous::Autonomous(main_robot* r)
{
    robot = r;
    timer = new Timer();
    previousStage = stage = IDLE;
}

Autonomous::~Autonomous()
{
    delete timer;
}

bool Autonomous::moveForward(double dist)
{
    if (previousStage != stage)
    {
        previousStage = stage;
        robot->drive->autoDrive(dist);
    }
    return !(robot->drive->isAuto());
}

bool Autonomous::tilt()        // needs to tilt a certain degrees, probably starting from below going up
{
    if (previousStage != stage)
    {
        previousStage = stage;
        robot->shoot->pitchAngle(POSITION_TILT);
    }
    return robot->shoot->hasTilted;
}

bool Autonomous::releaseClamp()
{
    if (previousStage != stage)
    {
        previousStage = stage;
        robot->shoot->clampUp();
    }
    return false;
}
bool Autonomous::shootBall()
{
    if (previousStage != stage)
    {
        previousStage = stage;
        robot->shoot->wormPull();
    }
    return false;
}
/*
void Autonomous::vision()
{
}
*/
bool Autonomous::timePassed(float time)
{
    return (timer->HasPeriodPassed(time));
}
/*
double Autonomous::getTime()
{
}
*/
void Autonomous::updateBasic()
{
    switch (stage)
    {
        case IDLE:
            printf("AUTO switch to AIMING\n");
            stage = AIMING;
            break;
        case DRIVING:
            if(moveForward(DISTANCE))
                printf("AUTO done driving\n");
                stage = DONE;
            break;
        case AIMING:
            if(tilt())
                printf("AUTO done tilting\n");
                stage = DONE;
        case DONE:
            robot->drive->TankDrive(0.0,0.0);
            break;
        default:
            break;
    }
}
