#ifndef SHOOTER_H_INCLUDED
#define SHOOTER_H_INCLUDED

#include <CANJaguar.h>
#include <Talon.h>
#include <DoubleSolenoid.h>
#include <Encoder.h>
#include "controls.h"
#include "Pneumatics.h"
#include "SmoothJoystick.h"
#include "Sensors.h"

class Shooter
{
public:
    Shooter(uint8_t axisMod,
                 uint8_t attractMod, uint32_t attractChan,
                 uint8_t clampMod, uint32_t clampFChan, uint32_t clampRChan,
                 uint8_t bobModA, uint32_t bobChanA, uint8_t bobModB, uint32_t bobChanB,
                 uint8_t wormMod, uint32_t wormChan,
                 uint8_t punchMod,uint32_t punchFChan,uint32_t punchRChan);
    ~Shooter();
    enum Clamp {down, up};
    Clamp clamp;
    void pitchUp();
    void pitchDown();
    void pitchStop();
    void pitchAngle(double newPosition);
    void pull();//Wheel pulls ball
    void pullStop();
    void autoClamp();
    void clampDown();//Clamps down on ball & pulls
    void clampUp();//opens clamp
    void wormPull();
    void wormStop();
    void punch();
    
    CANJaguar* axis;
    Talon* attractor;
    DoubleSolenoid* clamper;
    Pneumatics* pneumatics;
    SmoothJoystick* shooterJoy;
    Encoder* bobTheEncoder;
    Talon* wormGear;
    DoubleSolenoid* puncher;
   
    const static float SPEED_AXISPOWER;
    const static float SPEED_ATTRACTOR = 0.5f;
    const static double TIME = 0.1;
    const static double PUNCH_TIME = 0.1;
    
    bool isPickingUp;
    bool isPitchingUp;
    bool isPitchingDown;
    bool wormIsPulling;
    bool isLoaded;
    double currentPos;
    double destinationPos;
    double originPos;
    static const double SHOOTING_POSITION = 45;
    static const double PICKUP_POSITION = 135;
    static const float SPEED_WORM = 1.0f;
    static void buttonHelper(void* objPtr, uint32_t button);
    void update();
    static void updateHelper(void* instName);
};

#endif // SHOOTER_H_INCLUDED
