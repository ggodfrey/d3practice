/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "ADXL345_I2C_612.h"
#include <I2C.h>
#include <ADXL345_I2C.h>
/**
 * Constructor.
 * 
 * @param moduleNumber The digital module that the sensor is plugged into (1 or 2).
 * @param range The range (+ or -) that the accelerometer will measure.
 */
ADXL345_I2C_612::ADXL345_I2C_612(uint8_t moduleNumber, ADXL345_I2C::DataFormat_Range range):
ADXL345_I2C(moduleNumber,range)
{
    RANGE=range;
}

/**
 * Get the acceleration of one axis in Gs.
 * 
 * @param axis The axis to read from.
 * @return Acceleration of the ADXL345 in Gs.
 */
double ADXL345_I2C_612::GetAcceleration(ADXL345_I2C::Axes axis)
{
        // Turn on the measurements
        m_i2c->Write(kPowerCtlRegister, kPowerCtl_Measure);
        // Specify the data format to read
        m_i2c->Write(kDataFormatRegister, kDataFormat_FullRes | (uint8_t)RANGE);
        return ADXL345_I2C::GetAcceleration(axis);
}

/**
 * Get the acceleration of all axes in Gs.
 * 
 * @return Acceleration measured on all axes of the ADXL345 in Gs.
 */
ADXL345_I2C::AllAxes ADXL345_I2C_612::GetAccelerations()
{
        // Turn on the measurements
        m_i2c->Write(kPowerCtlRegister, kPowerCtl_Measure);
        // Specify the data format to read
        m_i2c->Write(kDataFormatRegister, kDataFormat_FullRes | (uint8_t)RANGE);
        return ADXL345_I2C::GetAccelerations();
}
bool ADXL345_I2C_612::isConnected()
{
    ADXL345_I2C::AllAxes myAxes = GetAccelerations();
    return !(myAxes.XAxis==myAxes.YAxis==myAxes.ZAxis==0.0);
}

