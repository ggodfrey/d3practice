#include "Shifter.h"
#include "612.h"

Shifter::Shifter(main_robot* r, uint8_t mod,uint32_t chanF,uint32_t chanR)
{
    robot = r;
    shifter=new DoubleSolenoid(mod,chanF,chanR);
    robot -> driverJoy -> addJoyFunctions(&buttonHelper,(void*)this,SHIFT_LOW);
    robot -> driverJoy -> addJoyFunctions(&buttonHelper,(void*)this,SHIFT_HIGH);
}

Shifter::~Shifter()
{
    delete shifter;
}

void Shifter::shiftGear()
{
    if(gear == low)
        setHigh();
    else if(gear == high)
        setLow();
}

void Shifter::setHigh()
{
    gear=high;
    robot->pnum->setVectorValues(TIME, shifter, DoubleSolenoid::kForward);
}

void Shifter::setLow()
{
    gear=low;
    robot->pnum->setVectorValues(TIME, shifter, DoubleSolenoid::kReverse);
}

void Shifter::buttonHelper(void* objPtr, uint32_t button){
    Shifter* ShifterObj=(Shifter*)objPtr;
    if(button == SHIFT_LOW)
        ShifterObj->setLow();
    else if(button == SHIFT_HIGH)
        ShifterObj->setHigh();
}


