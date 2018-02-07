/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Date    : Novembre 2nd, 2017
  Title   : humidity_driver.cpp
  Project : Iot Bird Feeder
  Desc    : Driver used to read the humidity on DHT11 sensor
******************************************************************/
#include "Arduino.h"

void DHT_Init(void);
byte DHT_ReadHumidity(void);
