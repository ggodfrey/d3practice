#ifndef PORTS_H
#define PORTS_H


// DriveTrain Channels
const static uint32_t TALON_FL_CHANNEL = 3;
const static uint32_t TALON_FR_CHANNEL = 1;
const static uint32_t TALON_RL_CHANNEL = 4;
const static uint32_t TALON_RR_CHANNEL = 2;
// DriveTrain Modules
const static uint8_t  TALON_FL_MODULE  = 1;
const static uint8_t  TALON_FR_MODULE  = 1;
const static uint8_t  TALON_RL_MODULE  = 1;
const static uint8_t  TALON_RR_MODULE  = 1;
// Pneumatics Channels
const static uint32_t PNUM_DIGIN_CHANNEL = 8;
const static uint32_t PNUM_RELAY_CHANNEL = 8;
// Pneumatics Modules
const static uint8_t  PNUM_DIGIN_MODULE  = 1;
const static uint8_t  PNUM_RELAY_MODULE  = 1;

// Shifter
const static uint32_t SHIFT_FCHAN = 7;
const static uint32_t SHIFT_RCHAN = 8;
const static uint8_t  SHIFT_MOD   = 1;

// Shooter
const static uint8_t  SHOOT_JAG_CAN       = 1; // tilt

const static uint8_t  SHOOT_TALON_MODULE  = 1; // grabber/rollers/attractor
const static uint32_t SHOOT_TALON_CHANNEL = 5;

const static uint8_t  SHOOT_SLNOID_MODULE = 1; // clamp
const static uint32_t SHOOT_SLNOID_FCHAN  = 5;
const static uint32_t SHOOT_SLNOID_RCHAN  = 6;

const static uint32_t WORM_JAG_CAN        = 2; // worm drive

const static uint8_t  PUNCH_SLNOID_MODULE = 1; // dog clutch piston
const static uint32_t PUNCH_SLNOID_FCHAN  = 3;
const static uint32_t PUNCH_SLNOID_RCHAN  = 4;

const static uint8_t  BOBMOD              = 6;

const static uint8_t  SHOOT_ACCEL_MODULE  = 1; // accelerometer I2C sidecar module

// Encoder Modules
const uint8_t  ENCODER_LMODULE_A  = 1;
const uint8_t  ENCODER_RMODULE_A  = 1;
const uint8_t  ENCODER_LMODULE_B  = 1;
const uint8_t  ENCODER_RMODULE_B  = 1;
// Drive Train Encoder Channels
const uint32_t ENCODER_RCHANNEL_A = 1;
const uint32_t ENCODER_RCHANNEL_B = 2;
const uint32_t ENCODER_LCHANNEL_A = 3;
const uint32_t ENCODER_LCHANNEL_B = 4;

// Joystick
const uint32_t DRIVER_JOY_PORT = 1;
const uint32_t GUNNER_JOY_PORT = 2;

// Sensors
const static uint8_t USMODNUMBER = 1; //ultrasonic modual number
const static uint32_t USCHANNEL  = 3; //ultrasonic Channel
const static uint8_t ISMODNUMBER = 1; //infrared Shooter Modual Number
const static uint32_t ISCHANNEL  = 4; //Infrared Shooter Channel
const static uint8_t ILMODNUMBER = 1; //Infrared Load Modual Number
const static uint32_t ILCHANNEL  = 5; //Infrared Load Channel
//have no idea how this is supposed to work...

#endif
