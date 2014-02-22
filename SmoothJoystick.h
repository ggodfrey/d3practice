#ifndef SMOOTHJOYSTICK_H
#define SMOOTHJOYSTICK_H

#include <Joystick.h>
#include "controls.h"
#include <vector>
#include <bitset>


class SmoothJoystick: public Joystick
{
private:
    static const int NUMBUTTONS = 12;
    static const double DEADZONE = 0.1;
    static const double TRIGGER_TOLERANCE = 0.1;
public:
    SmoothJoystick(main_robot robot, uint32_t port);
    ~SmoothJoystick();
    typedef void* joyfuncObjects;
    typedef void(*joyFunctions)(joyfuncObjects,uint32_t);
    typedef bool* functionBool;
    typedef void* btn_Obj;
    std::vector<joyfuncObjects> Objects;
    std::vector<joyFunctions> joystickFuncs;
    std::vector<uint32_t> joyfuncButtons;
    std::vector<bool> funcBools;
    std::vector<std::bitset<3>* > buttons;

    void addJoyFunctions(joyFunctions controlFunctions, joyfuncObjects controlObjects, uint32_t btn);
    void updateJoyFunctions();
    void addButtons();
    void buttonUpdate();
    bool GetSmoothButton(int Button_number);
    trigStates GetTriggerState();
    bool IsAxisZero(uint32_t axis);
    static void updateHelper(void* instName);
};

#endif //SMOOTHJOYSTICK_H
