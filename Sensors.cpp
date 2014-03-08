#include <AnalogChannel.h>
#include "ports.h"
#include "Sensors.h"
#include "main.h"
#include "612.h"

// everything in inches

Sensors::Sensors(main_robot* robot,
                 uint8_t USMODNUMBER, uint32_t USCHANNEL, uint8_t ISMODNUMBER, uint32_t ISCHANNEL,
                 uint8_t ILMODNUMBER, uint32_t ILCHANNEL)
{
    ultrasonic = new AnalogChannel(USMODNUMBER, USCHANNEL);
    infraredShooter = new AnalogChannel(ISMODNUMBER, ISCHANNEL);
    infraredLoad = new AnalogChannel(ILMODNUMBER, ILCHANNEL);

    robot -> update -> addFunctions(&updateHelper, (void*)this);
}

Sensors::~Sensors()
{
	delete ultrasonic;
	delete infraredShooter;
	delete infraredLoad;
}

float Sensors::getVoltsInfShooter()
{
	return infraredShooter->GetVoltage();
}

float Sensors::getVoltsInfLoad()
{
	return infraredLoad->GetVoltage();
}

float Sensors::getVoltsUltra()
{
	 return ((ultrasonic->GetVoltage()));
}
//all values are in centemeters

float Sensors::getInfraredShooter()
{
    // 18.77cm/V = 7.38976in/V
    return (getVoltsInfShooter() * VPMINF );
}

bool Sensors::getInfraredLoad()
{
    float loadDistance = getVoltsInfLoad() * VPMINF ;
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
    return (getVoltsUltra() / VPIULTRA);
}


void Sensors::updateHelper(void* instName)
{
    Sensors* sensorsObj = (Sensors*)instName;
    robot -> netcom -> primeLocation(sensorsObj -> getUltrasonic());
}
