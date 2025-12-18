#include <Arduino.h>
#include "led.h"
#include "timer.h"

// Button
#define BTN_PIN 19

void setup()
{
    Serial.begin(9600);

    initLED();      // from led.cpp
    initTimer();    // from timer.cpp
}

void loop()
{
    static bool start_seq = false;
    static bool led_finished = false;

    if (digitalRead(BTN_PIN))
    {
        Serial.println("Clicked");
        start_seq = true;
    }

    if (start_seq)
    {
        countDownLED();
        start_seq = false;
        led_finished = true;
        startTimer();     
    }

    if (led_finished)
    {
        updateTimer();  
    }

    delay(100);
}
