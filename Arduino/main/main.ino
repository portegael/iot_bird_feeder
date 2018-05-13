/******************************************************************
  Author  : Gaël PORTÉ (portegael.pro@gmail.com)
  Date    : Novembre 2nd, 2017
  Title   : main.ino
  Project : Iot Bird Feeder
  Desc    : Main file waiting for an IT to read the meteo and send it through sigfox
******************************************************************/

#include "ArduinoLowPower.h"
#include "configuration.h"

#include "raindrop_driver.h"
#include "sigfox_driver.h"


static bool vibrationFlag = false;
static uint8_t numberIT = 0;

weatherInfoStructure st_weatherData = {0, 0, 0, 0};

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
  delay(2000);

  Serial.println("#########################");
  Serial.println("# iot bird feeder start #");
  Serial.println("#########################");

  pinMode(VibrationPin, INPUT_PULLUP);
  // LowPower.attachInterruptWakeup(VibrationPin, fVibrationIT, FALLING);
  attachInterrupt(VibrationPin, fVibrationIT, FALLING);
}

void loop() {

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

  if (true == vibrationFlag)
  {
    numberIT++;  
    Serial.print("Vibration detected = ");
    Serial.println(numberIT);

    // First, check if it is raining  
    if(fRaindrop_isRaining())
    {
      st_weatherData.rainLevelValue = fRaindrop_GetRainLevel();
      Serial.println("Watch out ! It is raining ! Sleeping now");

      // Send a message saying it is raining
//    SFX_SendMessage(&humidityValue);
     
      LowPower.sleep(DELAY_RAINING_MS);
    }
    else
    {

      // Sending datas
      //    SFX_SendMessage(&humidityValue);

      LowPower.sleep(DELAY_IT_MS);
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
