#include "Shooter.h"
#include "612.h"
#include "SmoothJoystick.h"
#include "main.h"

const double Shooter::SPEED_AXISPOWER = 0.5;
const double Shooter::SPEED_ATTRACTOR = 1.0;

Shooter::Shooter(main_robot* robot,uint8_t axisCan,
                 uint8_t attractMod, uint32_t attractChan,
                 uint8_t clampMod, uint32_t clampFChan, uint32_t clampRChan,
                 uint8_t wormCan,
                 uint8_t punchMod,uint32_t punchFChan,uint32_t punchRChan,
                 uint8_t bobMod)
{
    axis = new CANJaguar(axisCan);
    attractor = new Talon(attractMod, attractChan);
    clamper = new DoubleSolenoid(clampMod, clampFChan, clampRChan);
    wormGear = new CANJaguar(wormCan);
    puncher = new DoubleSolenoid(punchMod,punchFChan,punchRChan);
    bobTheAccelerometer = new ADXL345_I2C(bobMod);
    isPickingUp = false;
    shooterJoy = robot -> gunnerJoy;
    shooterJoy -> addJoyFunctions(&buttonHelper,(void*)this,CLAMP);
    robot -> update -> addFunctions(&updateHelper, (void*)this);
}

Shooter::~Shooter()
{
    delete axis;
    delete attractor;
    delete clamper;
    delete bobTheAccelerometer;
    delete wormGear;
    delete puncher;
}

void Shooter::pitchUp()
{
    axis->Set(SPEED_AXISPOWER);
}

void Shooter::pitchDown()
{
    axis->Set(-SPEED_AXISPOWER);
}

void Shooter::pitchStop()
{
    axis->Set(0);
}

void Shooter::pitchAngle(double newPitch)
{
    originPitch = currentPitch;
    destinationPitch = newPitch;
    isPickingUp = false;
    isPitchingDown = false;
    hasTilted = false;
    if (newPitch < originPitch)
    {
        pitchUp();
        isPitchingUp = true;
    }
    if (newPitch > originPitch)
    {
        pitchDown();
        isPitchingDown = true;
    }
}

void Shooter::pull()
{
    attractor->Set(SPEED_ATTRACTOR);
}

void Shooter::pullStop()
{
    attractor->Set(0);
}

void Shooter::repel()
{
    attractor->Set(-SPEED_ATTRACTOR);
}

//@param goClamp moves clamper, off says to stop clamper
void Shooter::autoClamp()
{
    if(clamp == up)
        clampDown();
    else
        clampUp();
}

void Shooter::clampDown()
{
    robot -> pnum->setVectorValues(TIME, clamper, DoubleSolenoid::kForward);
    clamp = down;
}

void Shooter::clampUp()
{
    robot -> pnum->setVectorValues(TIME, clamper, DoubleSolenoid::kReverse);
    clamp = up;
}

void Shooter::wormPull()
{
    if(!wormIsPulling)
    {
        robot -> pnum -> setVectorValues(PUNCH_TIME, puncher, DoubleSolenoid::kReverse);
    }
    wormIsPulling = true;
}

void Shooter::wormStop()
{
    wormGear -> Set(0);
    wormIsPulling = false;
    //currentSpeed = SPEED_WORM;
}

void Shooter::punch()
{
    robot -> pnum -> setVectorValues(PUNCH_TIME, puncher, DoubleSolenoid::kForward);
}

void Shooter::buttonHelper(void* objPtr, uint32_t button)
{
    Shooter* shooterObj=(Shooter*)objPtr;
    if(button==CLAMP)
        shooterObj->autoClamp();
}

// TODO IMPORTANT: What if we are pitching down to pickup angle, but we never reach
//                 there because we hit the frame? Somehow we need to detect that
//                 and set isPitchingDown to false if it hard stops

void Shooter::update()
{
    double bobX = bobTheAccelerometer->GetAcceleration(ADXL345_I2C::kAxis_X);
    double bobY = bobTheAccelerometer->GetAcceleration(ADXL345_I2C::kAxis_Y);
    double bobZ = bobTheAccelerometer->GetAcceleration(ADXL345_I2C::kAxis_Z);
    currentPitch = (atan2(bobX, sqrt(bobY*bobY + bobZ*bobZ))*180.0)/PI;

    // manual controls
    if(shooterJoy -> IsAxisZero(TILT))
        pitchStop();
    else if(shooterJoy -> GetRawAxis(TILT) < 0) // push up = negative values = tilt down
        pitchDown();
    else
        pitchUp();

    if(shooterJoy -> GetSmoothButton(ROLLERS))
        pull();
    else
        pullStop();
    if(shooterJoy -> GetTriggerState() == LOCKANDLOAD)
    {
        autoPulling = true;
        wormPull();
    }
    else if(autoPulling)
    {
        autoPulling = false;
        wormStop();
        punch();
    }

    // auto pitch angle
    if (isPitchingUp)
    {
        if (currentPitch <= destinationPitch || !(axis->GetForwardLimitOK()))
        {
            pitchStop();
            isPitchingUp = false;
        }
    }
    if (isPitchingDown)
    {
        if (currentPitch >= destinationPitch || !(axis->GetReverseLimitOK()))
        {
            pitchStop();
            isPitchingDown = false;
        }
    }
    if (!isPitchingDown && !isPitchingUp)
        hasTilted = true;

    // smart pickup control
    // sequence:
    // clamp up, tilt down
    // when tilt at pickup position, clamp down, rollers pull
    // when let go, tilt up
    // when tilt at shoot position, clamp up, rollers stop
    if(shooterJoy -> GetSmoothButton(PICKUP)) // holding down button
    {
        if (!isPickingUp) // hasn't started sequence yet
        {
            isPickingUp = true;
            pitchAngle(PICKUP_POSITION);
            clampUp();
        }
        if(!isPitchingDown) // tilt at pickup position
        {
            clampDown();
            pull();
        }
    }
    else // let go of button
    {
        if(isPickingUp) // was picking up, so now should stop picking up
        {
            pitchAngle(SHOOTING_POSITION);
            isPickingUp = false;
            isPickingUpStopping = true;
        }
        if (!isPitchingUp && isPickingUpStopping) // tilt at shooting position
        {
            clampUp();
            pullStop();
            isPickingUpStopping = false;
        }
    }

    if(wormIsPulling)
    {
        // increasing worm drive speed
        /*if(currentSpeed <= WORM_LIMIT)
        {
            currentSpeed += INCREMENT;
            wormGear->Set(currentSpeed);
        }
        else if(currentSpeed > WORM_LIMIT || !(wormGear->GetForwardLimitOK()))
            wormStop();*/
        wormGear->Set(SPEED_WORM);
        if (!(wormGear -> GetForwardLimitOK())) //checks if loader has reached farthest position
            wormStop();
    }
}

void Shooter::updateHelper(void* instName)
{
    Shooter* shooterObj = (Shooter*)instName;
    shooterObj -> update();
}
