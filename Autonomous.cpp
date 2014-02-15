#include "Autonomous.h"
#include "main.h"
#include "ports.h"
#include "612.h"


Autonomous::Autonomous()
{
}
Autonomous::~Autonomous()
{
}
void Autonomous::moveForward()
{
    robot->drive->autoDrive(DISTANCE);
    if (stage == DRIVING)
        {
            drive();
        }
    else
    {
        set previousStage = DRIVING
    }
}
void Autonomous::turn()
{
    robot->drive->autoTurn(DEGREES_TURN);
}
void Autonomous::tilt()        // needs to tilt a certain degrees, probably starting from below going up
{
    robot->shoot->pitchAngle(POSITION_TILT);
}
void Autonomous::releaseClamp()
{
    robot->shoot->clampUp();
}
void Autonomous::shootBall()
{
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
void Autonomous::update()
{
    switch (stage)
    {
        case DRIVING:
            moveForward();
            break;
        case TURNING:
            turn();
            break;
        case AIMING:
            tilt();
            break;
        case SHOOTING:
            shootBall();
            break;
        case IDLE:
            break;
        default:
            break;
    }
}


