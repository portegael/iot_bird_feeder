/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Title   : foodlevel_driver.cpp
  Project : Iot Bird Feeder
  Desc    : Driver used to get the foodlevel
  History :
  | -- Date -- | -- Modification ------------------- |
  | 08/13/2018 | Creation                            |
  | -------------------------------------------------|
******************************************************************/
#include "foodlevel_driver.h"
#include "sigfox_driver.h"
#include "configuration.h"
#include <HCSR04.h>


static UltraSonicDistanceSensor distanceSensor(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN);

//_________________________________________________________________________________________________________
/**
 * @brief Read the percentage of remaining food
 * @return Level percentage
 */
void fFoodLevel_GetPercentageLevel(void)
{
    uint8_t retry = 1;
    double distanceRawValue = 0; 
    st_sigfoxData.foodLevelPercentage = 100;
    
    while(retry < HCSR04_MAX_RETRY)
    {     
      distanceRawValue = distanceSensor.measureDistanceCm();
      if((distanceRawValue < HCSR04_DISTANCE_MAX) && (distanceRawValue > 0))
      {
         st_sigfoxData.foodLevelPercentage = 100 - ( distanceRawValue * 100 /  HCSR04_DISTANCE_MAX);
         break;
      }
        
  #ifdef DEBUG_MODE
      Serial.print("Retry #");
      Serial.println(retry);
  
      Serial.print("Food level = ");
      Serial.print(distanceRawValue);
      Serial.print("cm / ");
      Serial.print(st_sigfoxData.foodLevelPercentage);
      Serial.println(" %");
  #endif

      retry++;
    }

        
  #ifdef DEBUG_MODE
      Serial.print("Retry #");
      Serial.println(retry);
  
      Serial.print("Food level = ");
      Serial.print(distanceRawValue);
      Serial.print("cm / ");
      Serial.print(st_sigfoxData.foodLevelPercentage);
      Serial.println(" %");
  #endif
}



