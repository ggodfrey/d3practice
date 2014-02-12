#include <vector>
#include <IterativeRobot.h>
#include <DigitalInput.h>
#include <Relay.h>
#include <Timer.h>
#include <DoubleSolenoid.h>
#include "Pneumatics.h"
#include "DriveTrain.h"
#include "612.h"
#include "main.h"


Pneumatics::Pneumatics(uint8_t digitalMod, uint32_t digitalChannel,
                        uint8_t compModuleNumber, uint32_t compChannel)
{
    switchObject = new DigitalInput(digitalMod, digitalChannel);
    compressor = new Relay(compModuleNumber, compChannel, Relay::kForwardOnly);
    robot -> update -> addFunctions(&updateHelper, (void*) this);
}

void Pneumatics::checkPressure()
{
    if(switchObject->Get() == 1)
    {
        compressor->Set(Relay::kOff);
    }
    else
    {
        compressor->Set(Relay::kForward);
    }
}

void Pneumatics::updateSolenoid()
{
    //This function checks if the solenoid has expired
    for(unsigned int i = 0; i < time.size();)
    {
        Timer* timerObj = timerObject[i];
        if(timerObj->Get() >= time[i])
        {
            delete timerObj;
            solenoid[i]->Set(DoubleSolenoid::kOff);
            solenoid.erase(solenoid.begin()+i);
            time.erase(time.begin()+i);
            timerObject.erase(timerObject.begin()+i);
        }
        else
        {
            i++;
        }
    }
}

void Pneumatics::setVectorValues(double timerValue, DoubleSolenoid* startSolenoid, DoubleSolenoid::Value value)
{
    Timer* solenoidTimer = new Timer();
    time.push_back(timerValue);
    timerObject.push_back(solenoidTimer);
    solenoid.push_back(startSolenoid);
    startSolenoid->Set(value);
    solenoidTimer->Start();
}

void Pneumatics::updateHelper(void* instName)
{
    printf("Pneumatics update\n");
    Pneumatics* pnumObj = (Pneumatics*)instName;
    pnumObj -> checkPressure();
    pnumObj -> updateSolenoid();
}
