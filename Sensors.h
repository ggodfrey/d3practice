#ifndef SENSORS_H
#define SENSORS_H

#include <AnalogChannel.h>
#include "ports.h"

class main_robot;

class Sensors
{
public:
    AnalogChannel* ultrasonic;
    AnalogChannel* infraredShooter;
    AnalogChannel* infraredLoad;

    Sensors(main_robot* robot,
            uint8_t ISMODNUMBER, uint32_t USCHANNEL, uint8_t ISMODNUMBER, uint32_t ISCHANNEL,
            uint8_t ILMODNUMBER, uint32_t ILCHANNEL);
    ~Sensors();

    float getInfraredShooter();
    bool getInfraredLoad();
    float getUltrasonic();

    static void updateHelper(void* instName);

    static const float LOAD_THRESHOLD = 10;
};

#endif
