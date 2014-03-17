#include "main.h"
#include "612.h"
#include <DigitalInput.h>
#include <Relay.h>
#include <Joystick.h>
#include "ports.h"
#include "Netcom.h"
#include "Sensors.h"

main_robot* robot=NULL;

main_robot::main_robot()
{
    printf("Hello\n");
    printf("World\n");
    robot=this;
}

main_robot::~main_robot()
{
}

void main_robot::RobotInit()
{
    update = new FunctionRegistry();
    driverJoy = new SmoothJoystick(this, DRIVER_JOY_PORT);
    gunnerJoy = new SmoothJoystick(this, GUNNER_JOY_PORT);
    pnum = new Pneumatics(this, PNUM_DIGIN_MODULE, PNUM_DIGIN_CHANNEL, PNUM_RELAY_MODULE, PNUM_RELAY_CHANNEL);
    shift = new Shifter(this, SHIFT_MOD, SHIFT_FCHAN, SHIFT_RCHAN);
    shift->setHigh();
    drive = new DriveTrain(this, TALON_FL_MODULE, TALON_FL_CHANNEL,
                           TALON_RL_MODULE, TALON_RL_CHANNEL,
                           TALON_FR_MODULE, TALON_FR_CHANNEL,
                           TALON_RR_MODULE, TALON_RR_CHANNEL);
    shoot = new Shooter(this, SHOOT_JAG_CAN,
                        SHOOT_TALON_MODULE, SHOOT_TALON_CHANNEL,
                        SHOOT_SLNOID_MODULE, SHOOT_SLNOID_FCHAN, SHOOT_SLNOID_RCHAN,
                        WORM_JAG_CAN,
                        PUNCH_SLNOID_MODULE, PUNCH_SLNOID_FCHAN, PUNCH_SLNOID_RCHAN,
                        SHOOT_ACCEL_MODULE);
    sensors = new Sensors(this, USMODNUMBER, USCHANNEL, ISMODNUMBER, ISCHANNEL, ILMODNUMBER, ILCHANNEL, GYMOD, GYCHAN);
    sensors->setGyroSens(1.0f); //default sensitivity
    printf("Welcome to 612-2014 AERIAL ASSIST\n");
    netcom = new Netcom();
    autoBot = new Autonomous(this);
}
void main_robot::TeleopInit()
{
    drive->stopAuto();
    shoot->pitchStop();
    shoot->rollerStop();
    shoot->wormStop();
}
void main_robot::AutonomousInit()
{
    drive->stopAuto();
    shoot->pitchStop();
    shoot->rollerStop();
    shoot->wormStop();
}
void main_robot::TestInit()
{
    init_vision();
}
void main_robot::DisabledInit()
{
    stop_vision();
}
void main_robot::TeleopPeriodic()
{
    update->updateFunctions();
    float left = driverJoy->GetRawAxis(2);
    float right = driverJoy->GetRawAxis(5);
    // up is negative, down is positive
    drive->TankDrive(-left, -right);
}

void main_robot::AutonomousPeriodic()
{
    update -> updateFunctions();
    drive -> update();
    autoBot -> updateBasic();
}

void main_robot::DisabledPeriodic()
{
}
void main_robot::TestPeriodic()
{
//    printf("%d", engine->getHotGoal());
    pnum->checkPressure();
    pnum->updateSolenoid();
}

void main_robot::init_vision() {
    std::printf("init vision\n");
    engine = new vision();
}

void main_robot::stop_vision() {
    std::printf("stop vision\n");
    if(engine!=NULL) {
        if(engine->isContinuousRunning()) {
            engine->stopContinuous();
        }
        delete engine;
        engine=NULL;
    }
}

START_ROBOT_CLASS(main_robot)
