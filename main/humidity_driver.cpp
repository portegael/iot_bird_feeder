/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Date    : Novembre 2nd, 2017
  Title   : humidity_driver.cpp
  Project : Iot Bird Feeder
  Desc    : Driver used to read the humidity on DHT11 sensor
******************************************************************/
#include "humidity_driver.h"

#define dhtPin A0
byte errorByte;
byte dhtData[5];

void ReadDHT();
byte read_dht_dat();


void DHT_Init(void) {
  pinMode(dhtPin, OUTPUT);
  digitalWrite(dhtPin, HIGH);
}

byte DHT_ReadHumidity(void) {

  for(int i = 0; i < 3; i++) {
    ReadDHT();
  }

  return dhtData[0];

}


void ReadDHT() {
  errorByte = 0;
  byte dht_in;
  byte i;
  digitalWrite(dhtPin, LOW);
  delay(20);
  digitalWrite(dhtPin, HIGH);
  delayMicroseconds(40);
  pinMode(dhtPin, INPUT);
  //delayMicroseconds(40);
  dht_in = digitalRead(dhtPin);
  if (dht_in) {
    errorByte = 1;
    return;
  }
  delayMicroseconds(80);
  dht_in = digitalRead(dhtPin);
  if (!dht_in) {
    errorByte = 2;
    return;
  }
  delayMicroseconds(80);
  for (i = 0; i < 5; i++)
    dhtData[i] = read_dht_dat();
  pinMode(dhtPin, OUTPUT);
  digitalWrite(dhtPin, HIGH);
  byte dht_check_sum =
    dhtData[0] + dhtData[1] + dhtData[2] + dhtData[3];
  if (dhtData[4] != dht_check_sum)
  {
    errorByte = 3;
  }
};

byte read_dht_dat() {
  byte i = 0;
  byte result = 0;
  for (i = 0; i < 8; i++) {
    while (digitalRead(dhtPin) == LOW);
    delayMicroseconds(30);
    if (digitalRead(dhtPin) == HIGH)
      result |= (1 << (7 - i));
    while (digitalRead(dhtPin) == HIGH);
  }
  return result;
}

