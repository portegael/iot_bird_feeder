/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Title   : bme280_driver.cpp
  Project : Iot Bird Feeder
  Desc    : Driver used to get the pressure, temperature and humidity
  History :
  | -- Date -- | -- Modification ------------------- |
  | 08/13/2018 | Creation                            |
  | -------------------------------------------------|
******************************************************************/
#include "bme280_driver.h"
#include "sigfox_driver.h"
#include "configuration.h"

#include <BME280I2C.h>
#include <Wire.h>

static BME280I2C bme;    // Default : forced mode, standby time = 1000 ms
                  // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

//_________________________________________________________________________________________________________
/**
 * @brief Initialize the BME device
 * @return None
 */
void fBme280_Init(void)
{
  bme.begin();
}

//_________________________________________________________________________________________________________
/**
 * @brief Read the current weather information
 * @return None
 */
void fBme280_ReadData(void)
{
  float temp(NAN), hum(NAN), pres(NAN);

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
  BME280::PresUnit presUnit(BME280::PresUnit_hPa);
  
  bme.read(pres, temp, hum, tempUnit, presUnit);

  st_sigfoxData.pressure    = (uint16_t)pres;
  st_sigfoxData.temperature = (int8_t)  temp;
  st_sigfoxData.humidity    = (uint8_t) hum;

#ifdef DEBUG_MODE
   Serial.print("Temp: ");
   Serial.print(st_sigfoxData.temperature);
   Serial.print(" "+ String(tempUnit == BME280::TempUnit_Celsius ? 'C' :'F'));
   Serial.print("\t\tHumidity: ");
   Serial.print(st_sigfoxData.humidity);
   Serial.print("% RH");
   Serial.print("\t\tPressure: ");
   Serial.print(st_sigfoxData.pressure);
   Serial.println(" hPa");
#endif
}



