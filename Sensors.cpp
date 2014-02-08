#include <AnalogChannel.h>
#include "ports.h"
#include "Sensors.h"
#include "main.h"
#include "612.h"

Sensors::Sensors(uint8_t USMODNUMBER, uint32_t USCHANNEL, uint8_t ISMODNUMBER, uint32_t ISCHANNEL,
                 uint8_t ILMODNUMBER, uint32_t ILCHANNEL)
{
    ultrasonic = new AnalogChannel(USMODNUMBER, USCHANNEL);
    infraredShooter = new AnalogChannel(ISMODNUMBER, ISCHANNEL);
    infraredLoad = new AnalogChannel(ILMODNUMBER, ILCHANNEL);
     robot -> update -> addFunctions(&updateHelper, (void*)this);
}

Sensors::~Sensors()
{

}

//all values are in centemeters

float Sensors::getInfraredShooter()
{
    return (infraredShooter->GetVoltage() * 18.777);
}

bool Sensors::getInfraredLoad()
{
    float loadDistance = infraredLoad->GetVoltage() * 18.777;
    if(loadDistance < 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

float Sensors::getUltrasonic()
{
    return (((ultrasonic->GetVoltage()) / 9.8) * 2.54);
}

void updateHelper(void* instName)
{
    Sensors* sensorObj = (Sensors*)instName;
    sensorObj->getInfraredShooter();
    sensorObj->getInfraredLoad();
    sensorObj->getUltrasonic();
}

