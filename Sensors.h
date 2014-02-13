#ifndef SENSORS_H
#define SENSORS_H

#include <AnalogChannel.h>
#include "ports.h"

class Sensors
{
public:
    AnalogChannel* ultrasonic;
    AnalogChannel* infraredShooter;
    AnalogChannel* infraredLoad;

    Sensors(uint8_t ISMODNUMBER, uint32_t USCHANNEL, uint8_t ISMODNUMBER, uint32_t ISCHANNEL,
            uint8_t ILMODNUMBER, uint32_t ILCHANNEL);
    ~Sensors();

    float getInfraredShooter();
    bool getInfraredLoad();
    float getUltrasonic();

    static const float LOAD_THRESHOLD = 10;
};

#endif
