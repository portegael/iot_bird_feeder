/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Date    : Novembre 2nd, 2017
  Title   : sigfox_driver.h
  Project : Iot Bird Feeder
  Desc    : Driver used to send sigfox messages
******************************************************************/
#ifndef _SIGFOX_DRIVER_H_
#define _SIGFOX_DRIVER_H_

#include "Arduino.h"

// Data
struct __attribute__ ((packed)) sigfoxDataStructure {
  uint8_t isRaining;
  uint16_t rainLevel;
  uint8_t foodLevelPercentage;
  int8_t temperature;
  uint8_t humidity;
  uint16_t pressure;
  uint16_t batteryVoltageMv;
  uint8_t batteryPercentage;
};

extern sigfoxDataStructure st_sigfoxData;

void SFX_SendMessage(void);

#endif // _SIGFOX_DRIVER_H_


