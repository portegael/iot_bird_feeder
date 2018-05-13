/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Title   : raindrop_driver.cpp
  Project : Iot Bird Feeder
  Desc    : Driver used to detect the rain
  History :
  | -- Date -- | -- Modification ------------------- |
  | 03/30/2018 | Creation                            |
  | -------------------------------------------------|
******************************************************************/
#include "raindrop_driver.h"
#include "configuration.h"

//_________________________________________________________________________________________________________
/**
 * @brief Read the digital pin to chekc if it is raining or not. 0 means it rains
 * @return true if it is raining
 */
bool fRaindrop_isRaining(void)
{
  bool isRaining = false;
  
  int data = digitalRead(RAINDROP_DIGITAL_PIN);

  if(0 == data)
  {
    isRaining = true;
  }

#ifdef DEBUG_MODE
  Serial.print("isRaining : ");
  Serial.println(isRaining);
#endif

  return isRaining;
}

//_________________________________________________________________________________________________________
/**
 * @brief Read the level of rain
 * @return level of rain as integer
 */
uint16_t fRaindrop_GetRainLevel(void)
{
  uint16_t level = (uint16_t)analogRead(RAINDROP_ANALOG_PIN);

#ifdef DEBUG_MODE
  Serial.print("Level of Rain : ");
  Serial.println(level);
#endif

  return level;
}



