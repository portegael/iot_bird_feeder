/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Title   : foodlevel_driver.cpp
  Project : Iot Bird Feeder
  Desc    : Driver used to get the pressure, temperature and humidity
  History :
  | -- Date -- | -- Modification ------------------- |
  | 08/13/2018 | Creation                            |
  | -------------------------------------------------|
******************************************************************/
#ifndef _BME280_DRIVER_H_
#define _BME280_DRIVER_H_

#include "Arduino.h"

void fBme280_Init(void);
void fBme280_ReadData(void);

#endif // _BME280_DRIVER_H_
