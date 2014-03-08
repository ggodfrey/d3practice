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
    static const int VPMSHOOTER = 7.38976; //volate per meter shooter
    static const int VPMULTRA = 0.0098;

    Sensors(main_robot* robot,
            uint8_t ISMODNUMBER, uint32_t USCHANNEL, uint8_t ISMODNUMBER, uint32_t ISCHANNEL,
            uint8_t ILMODNUMBER, uint32_t ILCHANNEL);
    ~Sensors();

    float getVoltsInf();//Get volts from infered shooter
    float getVoltsUltra();//Get volts from ultra sonic
    float getInfraredShooter();
    bool getInfraredLoad();
    float getUltrasonic();
    

    static void updateHelper(void* instName);

    static const float LOAD_THRESHOLD = 10;
};

#endif
