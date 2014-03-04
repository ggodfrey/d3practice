#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableProvider.h>
#include "Netcom.h"

const std::string Netcom::PATH = "612NetworkVariables";
const std::string Netcom::PRIMEKEY = "PrimeLocation";
const std::string Netcom::RUMBLEKEY = "ShouldRumble";
const std::string Netcom::HOTKEY = "HotGoalOn";
const std::string Netcom::DISTKEY = "Distance";

Netcom::Netcom()
{
    nwt612 = NetworkTable::GetTable(PATH);
}

Netcom::~Netcom()
{

}

void Netcom::primeLocation(double distance)
{
    if(distance >= ((PRIMEDISTANCE - BUFFER)) && distance <= (PRIMEDISTANCE + BUFFER))
    {
        bool idealDistance = true;
        nwt612 -> PutBoolean(PRIMEKEY, idealDistance);
    }
    else
    {
        bool idealDistance = false;
        nwt612 -> PutBoolean(PRIMEKEY, idealDistance);
    }
    nwt612 -> PutNumber(DISTKEY, distance);
}

void Netcom::joyRumble(bool rumble)
{
    nwt612 -> PutBoolean(RUMBLEKEY, rumble);
}

bool Netcom::getHotGoal()
{
    return (nwt612 -> GetBoolean(HOTKEY, false));
}

//don't even know what' wrong!!!
