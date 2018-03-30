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
#include "Arduino.h"

void DHT_Init(void);
uint8_t DHT_ReadHumidity(void);
int8_t  DHT_ReadTemperature(void);
