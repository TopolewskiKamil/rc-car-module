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
    static bool ledSeqOn = false;
    static bool timerOn = false;

    if (digitalRead(BTN_PIN)) {
        timerOn = false;
        ledSeqOn = true;
        startLedTimer();
    }

    if (ledSeqOn)
    {
        ledSeqOn = !countDownLED();
        timerOn = true;
        startTimer();     
    }

    // if (timerOn)
    // {
    //     updateTimer();  
    //     delay(100);
    // }
}
