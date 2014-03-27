#ifndef SHOOTER_H_INCLUDED
#define SHOOTER_H_INCLUDED

#include <CANJaguar.h>
#include <Talon.h>
#include <DoubleSolenoid.h>
#include "ADXL345_I2C_612.h"
#include <cmath>
#include "controls.h"
#include "Pneumatics.h"
#include "SmoothJoystick.h"
//#include "main.h"

#include <networktables/NetworkTable.h>


class Shooter
{
public:
    Shooter(main_robot* robot, uint8_t axisCan,
            uint8_t attractMod, uint32_t attractChan,
            uint8_t clampMod, uint32_t clampFChan, uint32_t clampRChan,
            uint8_t wormCan,
            uint8_t punchMod,uint32_t punchFChan,uint32_t punchRChan,
            uint8_t bobMod);
    ~Shooter();
    enum Clamp {down, up};
    Clamp clamp;
    void pitchUp();
    void pitchDown();
    void pitchStop();
    void pitchAngle(double newPitch);
    double getPitchSpeed();
    void rollerPull();//Wheel pulls ball
    void rollerStop();
    void rollerRepel();
    void autoClamp();
    void clampDown();//Clamps down on ball & pulls
    void clampUp();//opens clamp
    void wormPull();
    void wormStop();
    bool wormDone();
    void punch();
    void smartFire();
    bool doubleEqual(double a,double b);

    CANJaguar* axis;
    Talon* attractor;
    DoubleSolenoid* clamper;
    SmoothJoystick* shooterJoy;
    CANJaguar* wormGear;
    DoubleSolenoid* puncher;
    ADXL345_I2C_612* bobTheAccelerometer;
    main_robot* robot;

    bool isPickingUp;
    bool isPitchingUp;
    bool isPitchingDown;
    bool wormIsPulling;
    bool winching;
    bool hasTilted;
    bool isPickingUpStopping;
    bool autoPulling;
    bool smartFiring;
    bool accelWorking;
    double currentPitch;
    double destinationPitch;
    double originPitch;
    Timer* smartFireTimer;
    //double currentSpeed;

    static const double SPEED_AXISPOWER_TELEOP;
    static const double SPEED_AXISPOWER_AUTO_SLOW;
    static const double SPEED_AXISPOWER_AUTO_VERY_SLOW;
    static const double SPEED_AXISPOWER_AUTO_FAST;
    static const double AXIS_SPEED_FAR_THRESH = 70.0;
    static const double AXIS_SPEED_CLOSE_THRESH = 20.0;
    static const double SPEED_ATTRACTOR;
    static const double TIME = 0.1;
    static const double PUNCH_TIME = 0.1;
    static const double SMARTFIRE_TIME = 0.25;
    static const double PI = 3.14159;
    static const double VERTICAL_POSITION = 81.89;
    static const double HIGHGOAL_POSITION = 36; // suppoed to be 43, 82 inches
    static const double PICKUP_POSITION   = -25;
    static const double LOWGOAL_POSITION  = 49;
    static const double SPEED_WORM; //What we start at
    static const double INCREMENT  = 0.0000001;
    static const double WORM_LIMIT = 1.0;
    static const double FLOAT_THRESH = 0.001;

    static void buttonHelper(void* objPtr, uint32_t button);
    void update();
    static void updateHelper(void* instName);
};

#endif // SHOOTER_H_INCLUDED
