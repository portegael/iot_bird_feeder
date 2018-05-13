#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

// Comment to disable printf
#define DEBUG_MODE

// Delay
#define DELAY_RAINING_MS  10000
#define DELAY_IT_MS       3000

// Pins config
#define VibrationPin 0

#define RainDropAnalogPin  A0
#define RainDropDigitalPin 3

// Data
struct weatherInfoStructure {
  uint8_t humidityValue;
  uint16_t pressureValue;
  int8_t temperatureValue;
  uint16_t rainLevelValue;
};

#endif // _CONFIGURATION_H_

