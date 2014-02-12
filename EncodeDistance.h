#ifndef ENCODEDISTANCE_H
#define ENCODEDISTANCE_H

#include <Encoder.h>

class EncodeDistance
{
public:
    EncodeDistance::EncodeDistance(uint8_t modLA, uint32_t chanLA,
                                   uint8_t modLB, uint32_t chanLB,
                                   uint8_t modRA, uint32_t chanRA,
                                   uint8_t modRB, uint32_t chanRB);
    ~EncodeDistance();
    double getLDistance();
    double getRDistance();
    double getAvgDistance();
    double convertTickToDist(double pulse);
    double convertDistToTick(double distance);
    Encoder* EncoderL;
    Encoder* EncoderR;
private:
    static const double DISTPERPULSE = 1.0;
};

#endif // ENCODEDISTANCE_H



