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
#include "humidity_driver.h"
#include "DHT.h"

/*
 * This code is based on the AdaFruit example DHT Tester 
 */

#define DHTPIN 50
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

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
  
  Serial.print("Humidity : ");
  Serial.print(humidity);
  Serial.println(" %");


  return humidity;

}

//_________________________________________________________________________________________________________
/**
 * @brief Read the temperature on the DHT22 sensor
 * @return Temperature as signed integer
 */
int8_t DHT_ReadTemperature(void)
{
}


