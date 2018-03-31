/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Title   : humidity_driver.cpp
  Project : Iot Bird Feeder
  Desc    : Driver used to read the humidity on DHT22 sensor
  History :
  | -- Date -- | -- Modification ------------------- |
  | 11/02/2017 | Creation                            |
  | 03/30/2018 | Change device from DHT11 to DHT22   |
  | -------------------------------------------------|
******************************************************************/
#include "dht22_driver.h"
#include "DHT.h"
#include "configuration.h"

/*
 * This code is based on the AdaFruit example DHT Tester 
 */

DHT dht(Dht22Pin, DHTTYPE);

//_________________________________________________________________________________________________________
/**
 * @brief Used to initialized the DHT22 sensor
 */
void DHT_Init(void) {
  dht.begin();
}

//_________________________________________________________________________________________________________
/**
 * @brief Read the humidity on the DHT22 sensor
 * @return Humidity as unsigned integer
 */
uint8_t DHT_ReadHumidity(void) {

  uint8_t humidity = (uint8_t)dht.readHumidity();

  if (isnan(humidity))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

#ifdef DEBUG_MODE
  Serial.print("Humidity : ");
  Serial.print(humidity);
  Serial.println(" %");
#endif

  return humidity;

}

//_________________________________________________________________________________________________________
/**
 * @brief Read the temperature on the DHT22 sensor
 * @return Temperature as signed integer
 */
int8_t DHT_ReadTemperature(void)
{
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature)){
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
#ifdef DEBUG_MODE
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.println(" °C");
#endif
  
  return (int8_t)temperature;
}


