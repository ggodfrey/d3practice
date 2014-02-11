#include "Shooter.h"
#include "612.h"
#include "main.h"
#include "SmoothJoystick.h"

const float Shooter::SPEED_AXISPOWER = 0.5f;

Shooter::Shooter(uint8_t axisMod,
                 uint8_t attractMod, uint32_t attractChan,
                 uint8_t clampMod, uint32_t clampFChan, uint32_t clampRChan,
                 uint8_t bobMod)
{
    axis = new CANJaguar(axisMod);
    attractor = new Talon(attractMod, attractChan);
    clamper = new DoubleSolenoid(clampMod, clampFChan, clampRChan);
    shooterJoy = robot -> gunnerJoy;
    shooterJoy -> addJoyFunctions(&buttonHelper,(void*)this,PICKUP);
    //shooterJoy -> addJoyFunctions(&buttonHelper,(void*)this,CLAMP_DOWN);
    bobTheAccelerometer = new ADXL345_I2C(bobMod);
    isPickingUp = false;
    robot -> update -> addFunctions(&updateHelper, (void*)this);
}

Shooter::~Shooter()
{
    delete axis;
    delete attractor;
    delete clamper;
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

//@param goClamp moves clamper, off says to stop clamper
void Shooter::autoClamp()
{
    if(clamp == up)
    {
        clampDown();
    }
    else
    {
        clampUp();
    }
}

void Shooter::clampDown()
{
    pneumatics->setVectorValues(TIME, clamper, DoubleSolenoid::kForward);
    pull();
    clamp = down;
}

void Shooter::clampUp()
{
    pneumatics->setVectorValues(TIME, clamper, DoubleSolenoid::kReverse);
    pullStop();
    clamp = up;
}

//X to fire
void Shooter::buttonHelper(void* objPtr, uint32_t button)
{
    //Shooter* shooterObj=(Shooter*)objPtr;
}

void Shooter::update()
{
    double bobX = bobTheAccelerometer->GetAcceleration(ADXL345_I2C::kAxis_X);
    double bobY = bobTheAccelerometer->GetAcceleration(ADXL345_I2C::kAxis_Y);
    double bobZ = bobTheAccelerometer->GetAcceleration(ADXL345_I2C::kAxis_Z);
    currentPitch = (atan2(bobX, sqrt(bobY*bobY + bobZ*bobZ))*180.0)/PI;
    if(shooterJoy -> GetTriggerState() == TRIG_L)
    {
        pitchUp();
    }
    else if(shooterJoy -> GetTriggerState() == TRIG_R)
    {
        pitchDown();
    }
    else
    {
        pitchStop();
    }

    if (isPitchingUp)
    {
        if (currentPitch <= destinationPitch)
        {
            pitchStop();
            isPitchingUp = false;
        }
    }
    if (isPitchingDown)
    {
        if (currentPitch >= destinationPitch)
        {
            pitchStop();
            isPitchingDown = false;
        }
    }
    if(shooterJoy -> GetSmoothButton(PICKUP))
    {
        if (!isPickingUp)
        {
            isPickingUp = true;
            pitchAngle(PICKUP_POSITION);
            clampDown();
        }
    }
    else
    {
        if(isPickingUp){
        	pitchAngle(SHOOTING_POSITION);
        	isPickingUp = false;
        }
    	if (!isPitchingUp){
    	    clampUp();
    	}
    }
}

void Shooter::updateHelper(void* instName)
{
    Shooter* shooterObj = (Shooter*)instName;
    shooterObj -> update();
}
