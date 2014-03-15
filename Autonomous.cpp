#include "Autonomous.h"
#include "main.h"
#include "ports.h"
#include "612.h"


Autonomous::Autonomous(main_robot* r)
{
	robot = r;
    timer = new Timer();
    previousStage = IDLE;
}

Autonomous::~Autonomous()
{
    delete timer;
}

void Autonomous::moveForward(double dist)
{
    if (previousStage != DRIVING)
    {
    	previousStage = DRIVING;
        robot->drive->autoDrive(dist);
    }
    if(stage == DRIVING){
    	if(!(robot->drive->isMovingL) && !(robot->drive->isMovingR))
    	{
    		stage = AIMING;
    	}
    }
}

void Autonomous::tilt()        // needs to tilt a certain degrees, probably starting from below going up
{
    if (previousStage != AIMING)
    {
        robot->shoot->pitchAngle(POSITION_TILT);
        previousStage = AIMING;
    }
}

void Autonomous::releaseClamp()
{
    if (previousStage != SHOOTING)
    {
        robot->shoot->clampUp();
        previousStage = SHOOTING;
    }
}
void Autonomous::shootBall()
{
    if (previousStage != IDLE)
    {
        robot->shoot->wormPull();
        previousStage = IDLE;
    }
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
        //to be backup
            break;
        case DRIVING:
            moveForward(DISTANCE);
            break;
        case SHOOTING://nope.avi
            break;
        default:
            break;
    }
}



