#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

// Comment to disable printf
#define DEBUG_MODE

// Delay
#define DELAY_RAINING_MS  10000
#define DELAY_IT_MS       3000

// Devices config
#define VIBRATION_PIN 0

#define RAINDROP_ANALOG_PIN  A0
#define RAINDROP_DIGITAL_PIN 3

#define HCSR04_ECHO_PIN     1
#define HCSR04_TRIGGER_PIN  2
#define HCSR04_DISTANCE_MAX 15  // No food is 15 cm
#define HCSR04_MAX_RETRY    3   // Number of retries to get the food level

#endif // _CONFIGURATION_H_

