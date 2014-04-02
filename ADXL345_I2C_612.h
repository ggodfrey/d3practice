#ifndef ADXL345_I2C_612_h
#define ADXL345_I2C_612_h

#include <SensorBase.h>
#include <ADXL345_I2C.h>

//Todo: Determine if setting of data format is necessary after initialization

/**
 *      Improved ADXL345 Accelerometer Class
 * This class is an extension of the default ADXL345 class. It sends the start signal 
 * before each reading so if the wire becomes loose it doesn't turn off until reinitialized
 */

class ADXL345_I2C_612 : public ADXL345_I2C
{
public:
    ADXL345_I2C_612(uint8_t, ADXL345_I2C::DataFormat_Range=kRange_2G);
    double GetAcceleration(ADXL345_I2C::Axes);
    ADXL345_I2C::AllAxes GetAccelerations();
    bool isConnected();
private:
    DataFormat_Range RANGE;
};

#endif

