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

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>

Adafruit_BME280 bme; // I2C

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
  st_sigfoxData.pressure    = (uint16_t)(bme.readPressure() / 100.0F);
  st_sigfoxData.temperature = (int8_t)  bme.readTemperature();
  st_sigfoxData.humidity    = (uint8_t) bme.readHumidity();

#ifdef DEBUG_MODE
   Serial.print("Temp: ");
   Serial.print(st_sigfoxData.temperature);
   Serial.print(" *C");
   Serial.print("\t\tHumidity: ");
   Serial.print(st_sigfoxData.humidity);
   Serial.print("% RH");
   Serial.print("\t\tPressure: ");
   Serial.print(st_sigfoxData.pressure);
   Serial.println(" hPa");
#endif
}



