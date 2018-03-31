/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Date    : Novembre 2nd, 2017
  Title   : main.ino
  Project : Iot Bird Feeder
  Desc    : Main file waiting for an IT to read the meteo and send it through sigfox
******************************************************************/

//#include "ArduinoLowPower.h"
#include "configuration.h"

#include "dht22_driver.h"
#include "raindrop_driver.h"
//#include "sigfox_driver.h"


bool vibrationFlag = false;
int vibrationPin = 0;

uint8_t humidityValue = 0;
int8_t temperatureValue = 0;

void vibrationIT(void) {

  vibrationFlag = true;
}

void setup() {
  Serial.begin(9600);

 // DHT_Init();

//  pinMode(vibrationPin, INPUT_PULLUP);
//  LowPower.attachInterruptWakeup(vibrationPin, vibrationIT, FALLING);

}

void loop() {

  delay(2000);
 /* 
  humidityValue = DHT_ReadHumidity();
  Serial.print("Humidity read : ");
  Serial.print(humidityValue);
  Serial.println(" %");

  temperatureValue = DHT_ReadTemperature();
  Serial.print("Temperature read : ");
  Serial.print(temperatureValue);
  Serial.println(" °C");
*/

  Raindrop_GetRainLevel();
  if(Raindrop_isRaining())
  {
    Serial.println("Watch out ! It is raining !");
  }
  Serial.println(" ");
  
/*
  if (true == vibrationFlag)
  {
    vibrationFlag = false;

    humidityValue = DHT_ReadHumidity();

    SFX_SendMessage(&humidityValue);
  }

  LowPower.sleep();
  */
}
