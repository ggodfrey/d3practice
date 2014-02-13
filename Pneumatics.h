#ifndef PNEUMATICS_H
#define PNEUMATICS_H

#include <vector>
#include <IterativeRobot.h>
#include <DigitalInput.h>
#include <Relay.h>
#include <Timer.h>
#include <DoubleSolenoid.h>
#include "DriveTrain.h"

class Pneumatics
{
    public:
        Pneumatics(uint8_t digitalMod, uint32_t digitalChannel,
                   uint8_t compModuleNumber, uint32_t compChannel);
        void checkPressure();
        void setVectorValues(double timerValues, DoubleSolenoid* startSolenoid, DoubleSolenoid::Value value);
        void updateSolenoid();
        static void updateHelper(void* instName);
    private:
        DigitalInput* switchObject;
        Relay* compressor;
        std::vector<double> time;
        std::vector<Timer*> timerObject;
        std::vector<DoubleSolenoid*> solenoid;

};
#endif
