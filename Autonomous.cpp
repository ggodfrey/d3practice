#include "Autonomous.h"
#include "main.h"
#include "ports.h"
#include "612.h"


Autonomous::Autonomous()
{
    drive = new DriveTrain(TALON_FL_MODULE, TALON_FL_CHANNEL,
                           TALON_RL_MODULE, TALON_RL_CHANNEL,
                           TALON_FR_MODULE, TALON_FR_CHANNEL,
                           TALON_RR_MODULE, TALON_RR_CHANNEL);
    shoot = new Shooter(SHOOT_JAG_CAN,
                        SHOOT_TALON_MODULE, SHOOT_TALON_CHANNEL,
                        SHOOT_SLNOID_MODULE, SHOOT_SLNOID_FCHAN, SHOOT_SLNOID_RCHAN,
                        WORM_JAG_CAN, PUNCH_SLNOID_MODULE, PUNCH_SLNOID_FCHAN, PUNCH_SLNOID_RCHAN,
                        BOBMOD);
    timer = new Timer();
}
Autonomous::~Autonomous()
{
}
void Autonomous::moveForward()
{
    if (previousStage == IDLE)
    {
        robot->drive->autoDrive(DISTANCE);
        previousStage = DRIVING;
    }
}

void Autonomous::turn()
{
    if (previousStage == DRIVING)
    {
        robot->drive->autoTurn(DEGREES_TURN);
        previousStage = TURNING;
    }
}
void Autonomous::tilt()        // needs to tilt a certain degrees, probably starting from below going up
{
    if (previousStage == TURNING)
    {
        robot->shoot->pitchAngle(POSITION_TILT);
        previousStage = AIMING;
    }
}
void Autonomous::releaseClamp()
{
    if (previousStage == AIMING)
    {
        robot->shoot->clampUp();
        previousStage = SHOOTING;
    }
}
void Autonomous::shootBall()
{
    if (previousStage == SHOOTING)
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


