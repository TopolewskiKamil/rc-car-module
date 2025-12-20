#ifndef LED_H
#define LED_H

#include <MD_MAX72xx.h>

// ====== Hardware configuration ======
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 3

#define CS_PIN   23
#define CLK_PIN  18
#define DIN_PIN  15

// Extern declaration (defined in led.cpp)
extern MD_MAX72XX mx;

// Function prototype
void initLED();
bool countDownLED();
void startLedTimer();
void turnOnLED(int index);
void turnOffLed();
void loadingGameLED();
void startLedTimer2();


#endif
