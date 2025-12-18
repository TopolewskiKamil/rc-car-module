#include <Arduino.h>
#include "led.h"
#include "timer.h"
#include "speaker.h"

#define BTN_PIN 19

void setup()
{
    Serial.begin(9600);
    initLED();      // from led.cpp
    initTimer();    // from timer.cpp
    initSPIFFS();
    initSpeaker();
    delay(500);
}

void loop()
{
  playStart();
  playEnd();

  
    static bool ledSeqOn = false;
    static bool timerOn = false;

    if (digitalRead(BTN_PIN)) ledSeqOn = true;

    if (ledSeqOn)
    {
        countDownLED();
        ledSeqOn = false;
        timerOn = true;
        startTimer();     
    }

    if (timerOn)
    {
        updateTimer();  
    }

    // delay(100);
}
