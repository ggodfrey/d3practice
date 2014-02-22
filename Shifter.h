#ifndef SHIFTER_H_INCLUDED
#define SHIFTER_H_INCLUDED
#include <DoubleSolenoid.h>
#include <Timer.h>
#include "Pneumatics.h"
#include "controls.h"
#include "main.h"
#include "612.h"

class Shifter
{
public:
    Shifter(main_robot* r, uint8_t mod,uint32_t chanF,uint32_t chanR);
    ~Shifter();
    void shiftGear();
    void setHigh();
    void setLow();
    DoubleSolenoid* shifter;
    enum Gear {high,low};
    Gear gear;
    const static double TIME= 0.1;
    static void buttonHelper(void* objPtr, uint32_t button);
    main_robot* robot;
};


#endif // SHIFTER_H_INCLUDED
