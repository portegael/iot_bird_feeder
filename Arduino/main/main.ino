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
static uint8_t numberIT = 0;

sigfoxDataStructure st_sigfoxData = {0, 0, 0, 0, 0, 0};

/************************
 * Local functions
 ********************/
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
  // LowPower.attachInterruptWakeup(VIBRATION_PIN, fVibrationIT, FALLING);
  attachInterrupt(VIBRATION_PIN, fVibrationIT, FALLING);
}

void loop() {

  if (true == vibrationFlag)
  {
    numberIT++;  
    Serial.print("Vibration detected = ");
    Serial.println(numberIT);

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
    bool isRaining = fRaindrop_isRaining();

    // Sending datas
    SFX_SendMessage();

    if(isRaining == true)
    {     
      Serial.println("Watch out ! It is raining ! Sleeping now");

#ifdef DEBUG_MODE
      delay(DELAY_RAINING_MS);
#else
      LowPower.sleep(DELAY_RAINING_MS);
#endif
    }
    else
    {
#ifdef DEBUG_MODE
      delay(DELAY_IT_MS);
#else
      LowPower.sleep(DELAY_IT_MS);
#endif
    }

    // Now we can reactivate the IT
    Serial.println("Reactivate IT\r\n");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    
    vibrationFlag = false;
  }


  // LowPower.sleep();
}
