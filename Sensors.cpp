#include <AnalogChannel.h>
#include "ports.h"
#include "Sensors.h"
#include "main.h"
#include "612.h"

// everything in inches

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
    // 18.77cm/V = 7.38976in/V
    return (infraredShooter->GetVoltage() * 7.38976);
}

bool Sensors::getInfraredLoad()
{
    float loadDistance = infraredLoad->GetVoltage() * 7.38976;
    if(loadDistance < LOAD_THRESHOLD)
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
    // 9.8mV/in = 0.0098V/in
    return ((ultrasonic->GetVoltage()) / 0.0098);
}

void Sensors::updateHelper(void* instName)
{
    Sensors* sensorsObj = (Sensors*)instName;
    robot -> netcom -> primeLocation(sensorsObj -> getUltrasonic());
}
