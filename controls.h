#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

//Buttons
const static uint8_t BUTTON_A    = 1;
const static uint8_t BUTTON_B    = 2;
const static uint8_t BUTTON_X    = 3;
const static uint8_t BUTTON_Y    = 4;
const static uint8_t BUTTON_LB   = 5;
const static uint8_t BUTTON_RB   = 6;
const static uint8_t BUTTON_BAK  = 7;
const static uint8_t BUTTON_SRT  = 8;
const static uint8_t BUTTON_LCLK = 9;
const static uint8_t BUTTON_RCLK = 10;
//Axes
const static uint8_t AXIS_L_X = 1;
const static uint8_t AXIS_L_Y = 2;
const static uint8_t AXIS_TRIGGERS = 3;
const static uint8_t AXIS_R_X = 4;
const static uint8_t AXIS_R_Y = 5;
const static uint8_t DPAD_X   = 6;
//Trigger State
enum trigStates {TRIG_L, TRIG_R, TRIG_NONE};

//Driving
const static uint8_t LEFT_DRIVE  = AXIS_L_Y;
const static uint8_t RIGHT_DRIVE = AXIS_R_Y;

//Shifting
const static uint8_t SHIFT_LOW  = BUTTON_LB;
const static uint8_t SHIFT_HIGH = BUTTON_RB;

//Manual shooter controls
const static uint8_t TILT         = AXIS_L_Y;
const static uint8_t CLAMP        = BUTTON_A;
const static uint8_t ROLLERS      = AXIS_R_Y;
const static uint8_t ENERGIZE     = BUTTON_B;
const static uint8_t FIRE         = BUTTON_X; // release clamp, wait, disengage clutch

#endif
