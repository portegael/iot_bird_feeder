/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Date    : Novembre 2nd, 2017
  Title   : main.ino
  Project : Iot Bird Feeder
  Desc    : Main file waiting for an IT to read the meteo and send it through sigfox
******************************************************************/
#include <Wire.h>
#include "ArduinoLowPower.h"
#include "configuration.h"

#include "raindrop_driver.h"
#include "foodlevel_driver.h"
#include "bme280_driver.h"
#include "sigfox_driver.h"


static bool vibrationFlag = false;

/*
  uint8_t isRaining;
  uint16_t rainLevel;
  uint8_t foodLevelPercentage;
  int8_t temperature;
  uint8_t humidity;
  uint16_t pressure;
 */

sigfoxDataStructure st_sigfoxData = {0, 0, 0, 0, 0, 0};

/************************
 * Local functions
 ********************/
/*
 * @brief Method called with vibration IT happened
 */
static void fVibrationIT(void) {

  vibrationFlag = true;
}

/*******************
 * Arduino functions
 ********************/
void setup() {
  Serial.begin(9600);
  Wire.begin();

  delay(2000);

  Serial.println("#########################");
  Serial.println("# iot bird feeder start #");
  Serial.println("#########################");

  /********************************
  ***** Devices configuration *****
  *********************************/
  // BME device
  fBme280_Init();
  
  // Vibration device
  pinMode(VIBRATION_PIN, INPUT_PULLUP);

#ifdef DEBUG_MODE
  attachInterrupt(VIBRATION_PIN, fVibrationIT, FALLING);
#else
  LowPower.attachInterruptWakeup(VIBRATION_PIN, fVibrationIT, FALLING);
 #endif
}

void loop() {

  delay(5000); // Delay 5 seconds so we can reprogram easily

  if (true == vibrationFlag)
  {
    detachInterrupt(VIBRATION_PIN);
    
    // Get food level
    fFoodLevel_GetPercentageLevel();

    // Get weather information
    fBme280_ReadData();

#ifdef DEBUG_MODE
   Serial.print("Temp: ");
   Serial.print(st_sigfoxData.temperature);
   Serial.print("C");
   Serial.print("\t\tHumidity: ");
   Serial.print(st_sigfoxData.humidity);
   Serial.print("% RH");
   Serial.print("\t\tPressure: ");
   Serial.print(st_sigfoxData.pressure);
   Serial.println(" hPa");
#endif

    // Check if it is raining
    // This value is never null
    fRaindrop_GetRainLevel();
    // bool isRaining = fRaindrop_isRaining();

    // Sending datas
    SFX_SendMessage();

    if(st_sigfoxData.isRaining == true)
    {     

#ifdef DEBUG_MODE
      Serial.print("Watch out ! It is raining ! Sleeping now for (ms) : ");
      Serial.println(DELAY_RAINING_MS_DEBUG);

      delay(DELAY_RAINING_MS_DEBUG);
#else
      LowPower.deepSleep(DELAY_RAINING_MS_RELEASE);
#endif
    }
    else // if it is not raining
    {
#ifdef DEBUG_MODE
      Serial.print("Sleeping now for (ms) : ");
      Serial.println(DELAY_IT_MS_DEBUG);
      delay(DELAY_IT_MS_DEBUG);
#else
      LowPower.deepSleep(DELAY_IT_MS_RELEASE);
#endif
    }

    // Now we can reactivate the IT
    Serial.println("Reactivate IT\r\n");

    LowPower.attachInterruptWakeup(VIBRATION_PIN, fVibrationIT, FALLING);

    vibrationFlag = false;
  }

#ifndef DEBUG_MODE
  LowPower.deepSleep();
#else
  LowPower.deepSleep(); // Deep sleep until IT wakes us up
#endif
}
