#ifndef NETCOM_H
#define NETCOM_H

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableProvider.h>
#include <string>

class Netcom
{
public:
    const static double PRIMEDISTANCE = 1.0;
    const static double BUFFER = 0.1;
    const static std::string PATH;
    const static std::string PRIMEKEY;
    const static std::string RUMBLEKEY;
    const static std::string HOTKEY;
    const static std::string DISTKEY;

    Netcom();
    ~Netcom();

    void primeLocation(double distance);
    void joyRumble(bool rumble);
    NetworkTable* nwt612;
    bool getHotGoal();
};

#endif
