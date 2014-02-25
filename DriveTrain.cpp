#include "DriveTrain.h"
#include <Talon.h>
#include "612.h"
#include "main.h"

const double DriveTrain::SPEED=0.8;

// all in feet
const double DriveTrain::CIRCUMROBOT = 2 * PI * ROBOTRAD;

DriveTrain::DriveTrain(main_robot* robot,
                       uint8_t modFL,uint32_t chanFL,
                       uint8_t modRL,uint32_t chanRL,
                       uint8_t modFR,uint32_t chanFR,
                       uint8_t modRR,uint32_t chanRR)
           :RobotDrive(new Talon(modFL,chanFL),
                       new Talon(modRL,chanRL),
                       new Talon(modFR,chanFR),
                       new Talon(modRR,chanRR)),
            isMovingL(false),isMovingR(false),
            isTurningL(false),isTurningR(false),
            hasDriven(false), hasTurned(false)
{
    encode = new EncodeDistance(ENCODER_LMODULE_A, ENCODER_LCHANNEL_A,
                                ENCODER_LMODULE_B, ENCODER_LCHANNEL_B,
                                ENCODER_RMODULE_A, ENCODER_RCHANNEL_A,
                                ENCODER_RMODULE_B, ENCODER_RCHANNEL_B);

    robot -> update -> addFunctions(&updateHelper, (void*) this);
}

DriveTrain::~DriveTrain()
{
    delete encode;
}

void DriveTrain::autoDrive(double distance)
{
    stopAuto();
    NeededDist = distance;
    TankDrive(SPEED, SPEED);
    isMovingL = true;
    isMovingR = true;
    encode->EncoderL->Start();
    encode->EncoderR->Start();
}
void DriveTrain::autoTurn(double degrees)           // any degrees less than zero (0) will turn right; basically the unit circle
{
    stopAuto();
    double degrees2Radians = degrees * (PI/180);
    double arcLength = ROBOTRAD * degrees2Radians;  // checks the length of the arc in feet
    NeededDist = arcLength;
    if (degrees > 0){
        TankDrive(-SPEED, SPEED);
        isTurningL = true;
    }
    if (degrees < 0){
        TankDrive(SPEED, -SPEED);
        isTurningR = true;
    }
    encode->EncoderL->Start();
    encode->EncoderR->Start();
}

void DriveTrain::teleTurn(Dir direction, double power)
{
    if (isAuto())
        stopAuto();
    if (direction == RIGHT)
        TankDrive(power,-1*power);
    else if (direction == LEFT)
        TankDrive(-1*power,power);
}

void DriveTrain::update()
{
    float speedL;
    float speedR;
    if (isMovingL || isMovingR)
    {
        speedL = SPEED;
        if (encode->getLDistance() >= NeededDist)
        {
            encode->EncoderL->Stop();
            encode->EncoderL->Reset();
            isMovingL = false;
            speedL = 0.0f;
        }
        speedR = SPEED;
        if (encode->getRDistance() >= NeededDist)
        {
            encode->EncoderR->Stop();
            encode->EncoderR->Reset();
            isMovingR = false;
            speedR = 0.0f;
        }
        if (speedL == 0.0f && speedR == 0.0f)
            hasDriven = true;
        TankDrive(speedL, speedR);
    }
    if (isTurningL) // NeededDist is positive
    {
        speedL = SPEED;
        if (encode->getLDistance() <= -NeededDist)
        {
            encode->EncoderL->Stop();
            encode->EncoderL->Reset();
            speedL = 0.0f;
        }
        speedR = SPEED;
        if (encode->getRDistance() >= NeededDist)
        {
            encode->EncoderR->Stop();
            encode->EncoderR->Reset();
            speedR = 0.0f;
        }
        if(speedL < ZEROTEST && speedR < ZEROTEST)
            isTurningL = false;
        if (speedL == 0.0f && speedR == 0.0f)
            hasTurned = true;
        TankDrive(-speedL, speedR);
    }
    else if (isTurningR)
    {
        speedL = SPEED;
        if (encode->getLDistance() >= -NeededDist)
        {
            encode->EncoderL->Stop();
            encode->EncoderL->Reset();
            speedL = 0.0f;
        }
        speedR = SPEED;
        if (encode->getRDistance() <= NeededDist)
        {
            encode->EncoderR->Stop();
            encode->EncoderR->Reset();
            speedR = 0.0f;
        }
        if(speedL < ZEROTEST && speedR < ZEROTEST)
            isTurningR = false;
        if (speedL == 0.0f && speedR == 0.0f)
            hasTurned = true;
        TankDrive(-speedL, speedR);
    }
}

void DriveTrain::updateHelper(void* instName)
{
    printf("DriveTrain update\n");
    DriveTrain* driveObj = (DriveTrain*)instName;
    driveObj->update();
}

bool DriveTrain::isAuto()
{
    return ((isMovingL) || (isMovingR) || (isTurningL) || (isTurningR));
}

void DriveTrain::stopAuto()
{
    TankDrive(0.0f, 0.0f);
    encode->EncoderL->Stop();
    encode->EncoderR->Stop();
    encode->EncoderL->Reset();
    encode->EncoderR->Reset();
    isMovingL = false;
    isMovingR = false;
    isTurningL = false;
    isTurningR = false;
}
