#include "main.h"
#include "ports.h"

EncodeDistance::EncodeDistance(uint8_t modLA, uint32_t chanLA,
                               uint8_t modLB, uint32_t chanLB,
                               uint8_t modRA, uint32_t chanRA,
                               uint8_t modRB, uint32_t chanRB)
{
    EncoderL = new Encoder(modLA, chanLA,
                           modLB, chanLB);
    EncoderR = new Encoder(modRA, chanRA,
                           modRB, chanRB);
    EncoderL->SetDistancePerPulse(DISTPERPULSE);
    EncoderR->SetDistancePerPulse(DISTPERPULSE);
}

EncodeDistance::~EncodeDistance()
{
    delete EncoderL;
    delete EncoderR;
}

double EncodeDistance::getLDistance()
{
    return EncoderL->GetDistance();
}

double EncodeDistance::getRDistance()
{
    return EncoderR->GetDistance();
}

double EncodeDistance::getAvgDistance()
{
    return (getLDistance() + getRDistance()) / 2;
}
double EncodeDistance::convertTickToDist(double pulse)
{
    return (pulse*DISTPERPULSE);
}

double EncodeDistance::convertDistToTick(double distance)
{
    return (distance/DISTPERPULSE);
}



