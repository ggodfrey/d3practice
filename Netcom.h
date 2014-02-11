#ifndef NETCOM_H
#define NETCOM_H

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableProvider.h>
#include <String>

class Netcom
{
public:
    Netcom(path, NetworkTableProvider &provider);
    ~Netcom();
    const static std::string path;
    const static double primeDistance = 1.0;
    const static double buffer = 0.1;
    bool primeLocation(double distance);
    void joyRumble(bool rumble);
    NetworkTable* nwt612;
    bool getHotGoal(bool goalHot);
};


#endif
