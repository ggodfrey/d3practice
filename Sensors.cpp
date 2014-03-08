#include <AnalogChannel.h>
#include "ports.h"
#include "Sensors.h"
#include "main.h"
#include "612.h"

// everything in inches

Sensors::Sensors(main_robot* robot,
                 uint8_t usMod, uint32_t usChan, uint8_t isMod, uint32_t isChan,
                 uint8_t ilMod, uint32_t ilChan)
{
    ultrasonic = new AnalogChannel(usMod, usChan);
    infraredShooter = new AnalogChannel(isMod, isChan);
    infraredLoad = new AnalogChannel(ilMod, ilChan);

    robot -> update -> addFunctions(&updateHelper, (void*)this);
}

Sensors::~Sensors()
{
    delete ultrasonic;
    delete infraredShooter;
    delete infraredLoad;
}

//all values are in inches

float Sensors::getInfraredShooter()
{
    // 18.77cm/V = 7.38976in/V
    return (infraredShooter->GetVoltage() * 7.38976);
}

bool Sensors::getInfraredLoad()
{
    float loadDistance = infraredLoad->GetVoltage() * 7.38976;
    if(loadDistance < LOAD_THRESHOLD)
        return true;
    else
        return false;
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
