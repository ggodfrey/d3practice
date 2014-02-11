#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableProvider.h>
#include "Netcom.h"
#include "Sensors.h"

Netcom::Netcom(path, NetworkTableProvider &provider)
{
    nwt612 = new NetworkTable(path, &provider);
    path = "DriveToRio";

}

Netcom::Netcom()
{

}

bool Netcom::primeLocation(double distance)
{
    distance = nwt612->GetNumbher(path, double value);
    if(distance >= (-1 * (buffer + primeDistance)) && distance <= (buffer + primeDistance))
    {
        bool idealDistance = true;
        return (nwt612 -> GetBoolean(path, idealDistance));
    }
    else
    {
        bool idealDistance = false;
        return (nwt612 -> GetBoolean(path, idealDistance));
    }
}

void Netcom::joyRumble(bool rumble)
{
    if(nwt612 -> GetBoolean(Netcom::path, bool closeToGoal))
    {
        nwt612 -> PutBoolean(std::string key, rumble = true);
    }
    else
    {
        nwt612 -> PutBoolean(std::string key, rumble = false);
    }
}

void Netcom::sendSweetSpot()
{
    nwt612 -> PutNumber(std::string key, double SWEETSPOT);
}

bool Netcom::getHotGoal(bool goalHot)
{
    nwt612 -> GetBoolean(std::string key, goalHot);
}
