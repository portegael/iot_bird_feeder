#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

// Comment to disable printf
#define DEBUG_MODE

// Delay
#define DELAY_RAINING_MS_DEBUG  10000
#define DELAY_IT_MS_DEBUG       3000

#define DELAY_RAINING_MS_RELEASE  (20 * 60 * 1000)   // 20 mins
#define DELAY_IT_MS_RELEASE       3000  // 3 s

// Devices config
#define VIBRATION_PIN 0

#define RAINDROP_ANALOG_PIN  A0
#define RAINDROP_DIGITAL_PIN 3

#define HCSR04_ECHO_PIN     1
#define HCSR04_TRIGGER_PIN  2
#define HCSR04_DISTANCE_MAX 15  // No food is 15 cm
#define HCSR04_MAX_RETRY    3   // Number of retries to get the food level

// Battery
#define BATTERY_ANALOG_PIN  A2
#define BATTERY_R1          47.0
#define BATTERY_R2          122.0
#define BATTERY_VMAX        4200.0 // 4.2 mV

#define BAT_ADC_VREF            3300.0 // 3.3 V
#define BAT_ADC_RESOLUTION      4095.0 // 12 bits

#endif // _CONFIGURATION_H_

