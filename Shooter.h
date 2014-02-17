#ifndef SHOOTER_H_INCLUDED
#define SHOOTER_H_INCLUDED

#include <CANJaguar.h>
#include <Talon.h>
#include <DoubleSolenoid.h>
#include <ADXL345_I2C.h>
#include <cmath>
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
                 uint8_t wormMod, uint32_t wormChan,
                 uint8_t punchMod,uint32_t punchFChan,uint32_t punchRChan,
                 uint8_t bobMod);
    ~Shooter();
    enum Clamp {down, up};
    Clamp clamp;
    void pitchUp();
    void pitchDown();
    void pitchStop();
    void pitchAngle(double newPitch);
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
    Talon* wormGear;
    DoubleSolenoid* puncher;
    Sensors* sensor;
    ADXL345_I2C* bobTheAccelerometer;

    bool isPickingUp;
    bool isPitchingUp;
    bool isPitchingDown;
    bool wormIsPulling;
    double currentPitch;
    double destinationPitch;
    double originPitch;

    static const float SPEED_AXISPOWER;
    static const float SPEED_ATTRACTOR = 0.5f;
    static const double TIME = 0.1;
    static const double PUNCH_TIME = 0.1;
    static const double PI = 3.14159;
    static const double CATCHING_POSITION = 85;
    static const double SHOOTING_POSITION = 45;
    static const double PICKUP_POSITION = -45;
    static const float SPEED_WORM = 1.0f;

    static void buttonHelper(void* objPtr, uint32_t button);
    void update();
    static void updateHelper(void* instName);
};

#endif // SHOOTER_H_INCLUDED
