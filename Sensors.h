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
    static const int VPMINF = 7.38976; //volate per meter shooter
    static const int VPIULTRA = 0.0098;

    Sensors(main_robot* robot,
            uint8_t usMod, uint32_t usChan, uint8_t isMod, uint32_t isChan,
            uint8_t ilMod, uint32_t ilChan);
    ~Sensors();

    float getVoltsInfShooter();//Get volts from infered shooter
    float getVoltsInfLoad();//get volts inf load
    float getVoltsUltra();//Get volts from ultra sonic
    float getInfraredShooter();
    bool getInfraredLoad();
    float getUltrasonic();
    

    static void updateHelper(void* instName);

    static const float LOAD_THRESHOLD = 10;
};

#endif
