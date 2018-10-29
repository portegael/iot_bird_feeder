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
static uint8_t previousPercentageValue = 100; // We store the previous value to correct measurement errors
//_________________________________________________________________________________________________________
/**
 * @brief Read the percentage of remaining food
 * @return Level percentage
 */
void fFoodLevel_GetPercentageLevel(void)
{
    uint8_t retry = 1;
    double distanceRawValue = 0; 
    uint8_t newFoodLevelPercentage = previousPercentageValue;
   
    // We retry HCSR04_MAX_RETRY times the measurements in case it fails
    while(retry < HCSR04_MAX_RETRY)
    {     
      distanceRawValue = distanceSensor.measureDistanceCm();
      if((distanceRawValue < HCSR04_DISTANCE_MAX) && (distanceRawValue > 0))
      {
         newFoodLevelPercentage = 100 - ( distanceRawValue * 100 /  HCSR04_DISTANCE_MAX);
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

    // Store the new food level
    if(newFoodLevelPercentage < previousPercentageValue)
    {
      // Correct measurement issue by avoiding big steps
      if( (previousPercentageValue - newFoodLevelPercentage) < FOOD_LEVEL_STEP_MAX)
      {
        previousPercentageValue = newFoodLevelPercentage;
      }
    }

    st_sigfoxData.foodLevelPercentage = newFoodLevelPercentage;
}



