/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Date    : Novembre 2nd, 2017
  Title   : main.ino
  Project : Iot Bird Feeder
  Desc    : Main file waiting for an IT to read the meteo and send it through sigfox
******************************************************************/

#include "ArduinoLowPower.h"
#include "humidity_driver.h"
#include "sigfox_driver.h"

bool vibrationFlag = false;
int vibrationPin = 0;

byte humidityValue = 0;

void vibrationIT(void) {

  vibrationFlag = true;
}

void setup() {
  Serial.begin(9600);

  DHT_Init();

  pinMode(vibrationPin, INPUT_PULLUP);
  LowPower.attachInterruptWakeup(vibrationPin, vibrationIT, FALLING);

}

void loop() {

  if (true == vibrationFlag)
  {
    vibrationFlag = false;

    humidityValue = DHT_ReadHumidity();

    SFX_SendMessage(&humidityValue);
  }

  LowPower.sleep();
}
