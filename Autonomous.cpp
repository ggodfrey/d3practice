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
        robot->drive->autoDrive(dist);
    }
    return !(robot->drive->isAuto());
}

bool Autonomous::tilt(double angle)        // needs to tilt a certain degrees, probably starting from below going up
{
    if (previousStage != stage)
    {
        robot->shoot->pitchAngle(angle);
    }
    return robot->shoot->hasTilted;
}

bool Autonomous::releaseClamp()
{
    if (previousStage != stage)
    {
        robot->shoot->clampUp();
        timer->Reset();
        timer->Start();
    }
    return timePassed(Shooter::TIME);
}
bool Autonomous::wormPull()
{
    if (previousStage != stage)
    {
        robot->shoot->wormPull();
    }
    return robot->shoot->wormDone();
}
/*
void Autonomous::vision()
{moveForward(DISTANCE)
}
*/
bool Autonomous::timePassed(float time)
{
    return (timer->HasPeriodPassed(time));
}

bool Autonomous::fire()
{
    if (previousStage != stage)
    {
        robot->shoot->punch();
    }
    return true;
}
/*
double Autonomous::getTime()
{
}
*/
void Autonomous::updateHighGoal()
{
    static int output=0;
    switch (stage)
    {
        case IDLE:
            printf("AUTO switch to DRIVE_AIM_WINCH\n");
            stage = DRIVE_AIM_WINCH;
            break;
        case DRIVE_AIM_WINCH:
            bool driveDone=moveForward(DISTANCE);
            bool aimDone=tilt(POSITION_TILT);
            bool winchDone=wormPull();
            if(output%20==0)
            {
                printf("drive: %i, aim: %i, winch: %i\n",driveDone,aimDone,winchDone);
            }
            if(driveDone && aimDone && winchDone)
            {
                printf("AUTO switch to CLAMP\n");
                stage = CLAMP;
            }
            break;
        case CLAMP:
            if(releaseClamp())
            {
                printf("AUTO switch to FIRE\n");
                stage = FIRE;
            }
            break;
        case FIRE:
            if(fire())
            {
                printf("AUTO done\n");
                stage = DONE;
            }
            break;
        case DONE:
            robot->drive->TankDrive(0.0,0.0);
            break;
        default:
            break;
    }
    previousStage = stage;
    output++;
}

void Autonomous::updateBasicDrive()
{
    switch (stage)
    {
        case IDLE:
            printf("AUTO switch to BASIC_DRIVE\n");
            stage = BASIC_DRIVE;
            break;
        case BASIC_DRIVE:
            if(moveForward(DISTANCE))
            {
                printf("AUTO done\n");
                stage = DONE;
            }
            break;
        case DONE:
            robot->drive->TankDrive(0.0,0.0);
            break;
        default:
            break;
    }
}
