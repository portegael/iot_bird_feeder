/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Title   : raindrop_driver.cpp
  Project : Iot Bird Feeder
  Desc    : Driver used to detect the rain
  History :
  | -- Date -- | -- Modification ------------------- |
  | 03/30/2018 | Creation                           
  | 10/27/2018 | Set the boolean is Raising depending on an analogic rain level
  | -------------------------------------------------|
******************************************************************/
#include "raindrop_driver.h"
#include "sigfox_driver.h"
#include "configuration.h"

//_________________________________________________________________________________________________________
/**
 * @brief Read the digital pin to chekc if it is raining or not. 0 means it rains
 * Not used for now because we directly use the analogic rain level
 * @return true if it is raining
 */
/*bool fRaindrop_isRaining(void)
{
  bool isRaining = false;
  
  int data = digitalRead(RAINDROP_DIGITAL_PIN);

  if(0 == data)
  {
    isRaining = true;
  }

  st_sigfoxData.isRaining = (uint8_t)isRaining;


#ifdef DEBUG_MODE
  Serial.print("isRaining : ");
  Serial.println(isRaining);
#endif

  return isRaining;
}
*/
//_________________________________________________________________________________________________________
/**
 * @brief Read the level of rain
 * @return level of rain as integer
 */
void fRaindrop_GetRainLevel(void)
{
  st_sigfoxData.rainLevel = (uint16_t)analogRead(RAINDROP_ANALOG_PIN);

  if(st_sigfoxData.rainLevel < 800)
  {
    st_sigfoxData.isRaining = true;
  }
  else
  {
    st_sigfoxData.isRaining = false;
  }

#ifdef DEBUG_MODE
  Serial.print("Level of Rain : ");
  Serial.println(st_sigfoxData.rainLevel);
  Serial.print("Is raising ? : ");
  Serial.println(st_sigfoxData.isRaining);
#endif
}



