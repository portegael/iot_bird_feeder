/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Date    : Novembre 2nd, 2017
  Title   : sigfox_driver.cpp
  Project : Iot Bird Feeder
  Desc    : Driver used to send sigfox messages
******************************************************************/
#include "sigfox_driver.h"
#include "SigFox.h"
#include "configuration.h"

typedef struct __attribute__ ((packed)) sfxMessage {
  byte humidity;
  int8_t temperature;
  bool birdStep = true;
} SigfoxMessageStruct;

void SFX_SendMessage(byte *currentHumidity) {

  SigfoxMessageStruct message;

  // Start the module
  SigFox.begin();

  // Wait at least 30ms after first configuration (100ms before)
  delay(100);

  // Get internal temperature
  message.temperature = (int8_t)SigFox.internalTemperature();

  message.humidity = *currentHumidity;

  SigFox.beginPacket();

  SigFox.write((uint8_t*)&message, 12);

  SigFox.endPacket();

  SigFox.end();

}

