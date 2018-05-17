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

sigfoxDataStructure st_sigfoxData = {0, 0, 0, 0, 0, 0, 0, 0};

/************************
 * Local functions
 ********************/
/*
 * @brief Method called with vibration IT happened
 */
static void fVibrationIT(void) {

  vibrationFlag = true;
}

/*
 * Read the battery voltage through ADC
 */
static void fgetBatteryLevel(void)
{

  // Read raw value
  int vnum_12bits = analogRead(BATTERY_ANALOG_PIN);

  st_sigfoxData.batteryVoltageMv = (vnum_12bits * BAT_ADC_VREF / BAT_ADC_RESOLUTION) * ((BATTERY_R1 + BATTERY_R2) / BATTERY_R2);

  st_sigfoxData.batteryPercentage = st_sigfoxData.batteryVoltageMv * 100 / BATTERY_VMAX;
    
#ifdef DEBUG_MODE
    Serial.println("## BATTERY ##");
    Serial.print("\t 12bits = ");
    Serial.println(vnum_12bits);

    Serial.print("\t Voltage = ");
    Serial.print(st_sigfoxData.batteryVoltageMv);
    Serial.println(" mV");

    Serial.print("\t Percentage = ");
    Serial.print(st_sigfoxData.batteryPercentage);
    Serial.println(" %");
#endif
}

/*******************
 * Arduino functions
 ********************/
void setup() {
  Serial.begin(9600);
  Wire.begin();

  analogReadResolution(ADC_RESOLUTION);
  analogReference(AR_DEFAULT); // 3.3V

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

  if (true == vibrationFlag)
  {
    numberIT++;  
    Serial.print("Vibration detected = ");
    Serial.println(numberIT);

    // Get battery level
    fgetBatteryLevel();

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

#ifdef DEBUG_MODE
      Serial.print("Watch out ! It is raining ! Sleeping now for (ms) : ");
      Serial.println(DELAY_RAINING_MS_DEBUG);

      delay(DELAY_RAINING_MS_DEBUG);
#else
      LowPower.sleep(DELAY_RAINING_MS_RELEASE);
#endif
    }
    else
    {
#ifdef DEBUG_MODE
      Serial.print("Sleeping now for (ms) : ");
      Serial.println(DELAY_IT_MS_DEBUG);
      delay(DELAY_IT_MS_DEBUG);
#else
      LowPower.sleep(DELAY_IT_MS_RELEASE);
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

#ifndef DEBUG_MODE
  LowPower.sleep();
#endif
}
