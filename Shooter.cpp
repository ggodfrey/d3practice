#include "Shooter.h"
#include "612.h"
#include "main.h"
#include "SmoothJoystick.h"

const float Shooter::SPEED_AXISPOWER = 0.5f;

Shooter::Shooter(uint8_t axisMod,
                 uint8_t attractMod, uint32_t attractChan,
                 uint8_t clampMod, uint32_t clampFChan, uint32_t clampRChan,
                 uint8_t bobModA, uint32_t bobChanA, uint8_t bobModB, uint32_t bobChanB,
                 uint8_t wormMod, uint32_t wormChan,
                 unit8_t punchMod,unit32_t punchFChan,unit32_t punchRChan)
{
    axis = new CANJaguar(axisMod);
    attractor = new Talon(attractMod, attractChan);
    clamper = new DoubleSolenoid(clampMod, clampFChan, clampRChan);
    shooterJoy = robot -> gunnerJoy;
    shooterJoy -> addJoyFunctions(&buttonHelper,(void*)this,PICKUP);
    //shooterJoy -> addJoyFunctions(&buttonHelper,(void*)this,CLAMP_DOWN);
    bobTheEncoder = new Encoder(bobModA, bobChanA, bobModB, bobChanB);
    bobTheEncoder->Start();
    wormDrive = new Talon(wormMod,wormChan);
    puncher = new DoubleSolenoid(punchMod,punchFChan,punchRChan);
    isPickingUp = false;
    robot -> update -> addFunctions(&updateHelper, (void*)this);
}

Shooter::~Shooter()
{
    delete axis;
    delete attractor;
    delete clamper;
    delete bobTheEncoder;
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

void Shooter::pitchAngle(double newPosition)
{
    originPos = currentPos;
    destinationPos = newPosition;
    if (newPosition < originPos)
    {
        pitchUp();
        isPitchingUp = true;
    }
    if (newPosition > originPos)
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

void Shooter::wormPull()
{
    wormGear -> Set(-SPEED_WORM);
    wormIsPulling = true;
}

void Shooter::wormStop()
{
    wormGear -> Set(0);	
    wormIsPulling = false;
}

void Shooter::punch()
{
	if(isLoaded){
		pneumatics -> setVectorValues(PUNCH_TIME, puncher, DoubleSolenoid::kForward);
		isLoaded = false;
	}
}

//X to fire
void Shooter::buttonHelper(void* objPtr, uint32_t button){
    Shooter* shooterObj=(Shooter*)objPtr;
}

void Shooter::update()
{
    currentPos = bobTheEncoder->Get();
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
        if (currentPos <= destinationPos)
        {
            pitchStop();
            isPitchingUp = false;
        }
    }
    if (isPitchingDown)
    {
        if (currentPos >= destinationPos)
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
    if (wormIsPulling){
        if (Sensors::getInfraredLoad())
        {
           	wormStop();
           	isLoaded = true;
        }
    }
}


void Shooter::updateHelper(void* instName)
{
    Shooter* shooterObj = (Shooter*)instName;
    shooterObj -> update();
}
