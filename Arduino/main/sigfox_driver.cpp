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

//_________________________________________________________________________________________________________
/**
 * @brief Display the content of the structure
 * @return None
 */
static void SFX_DisplayStructContent(void)
{
  Serial.println("****************************");
  Serial.println("*\t Sigfox message to be sent : ");
  
  Serial.print("*\t isRaining = ");
  Serial.println(st_sigfoxData.isRaining);

  Serial.print("*\t Rain level = ");
  Serial.println(st_sigfoxData.rainLevel);

  Serial.print("*\t Food level Percentage = ");
  Serial.println(st_sigfoxData.foodLevelPercentage);

  Serial.print("*\t Temperature = ");
  Serial.print(st_sigfoxData.temperature);
  Serial.println(" C");

  Serial.print("*\t Humidity = ");
  Serial.print(st_sigfoxData.humidity);
  Serial.println(" %");

  Serial.print("*\t Pressure = ");
  Serial.print(st_sigfoxData.pressure);
  Serial.println(" hPa");

  Serial.print("*\t Battery = ");
  Serial.print(st_sigfoxData.batteryVoltageMv);
  Serial.print(" mV / ");
  Serial.print(st_sigfoxData.batteryPercentage);
  Serial.println(" %");
  
  Serial.println("****************************\r\n");

}

//_________________________________________________________________________________________________________
/**
 * @brief Send the data structure
 * @return None
 */
void SFX_SendMessage(void)
{

#ifdef DEBUG_MODE
  SFX_DisplayStructContent();
#endif

  // Start the module
  SigFox.begin();

  // Wait at least 30ms after first configuration (100ms before)
  delay(100);

  SigFox.beginPacket();

  SigFox.write((uint8_t*)&st_sigfoxData, sizeof(st_sigfoxData));
 // SigFox.write((byte)st_sigfoxData.isRaining);

  SigFox.endPacket();

  SigFox.end();

}

