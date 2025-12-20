#include <Arduino.h>
#include "led.h"
#include "timer.h"
#include "speaker.h"

#define BTN_PIN 19
#define BREAK_BEAM_PIN 25 

void setup()
{
    Serial.begin(9600);
    initLED();      // from led.cpp
    initTimer();    // from timer.cpp
    initSPIFFS();
    initSpeaker();
    pinMode(BREAK_BEAM_PIN, INPUT_PULLUP);
    delay(500);
}

void loop()
{

    static bool ledSeqOn = false;
    static bool timerOn = false;
    static int speakerEndState = 0;

    if (digitalRead(BTN_PIN)) {
        timerOn = false;
        ledSeqOn = true;
        startLedTimer();
        endTimer();
    }

    if (ledSeqOn)
    {
        bool ledFinished = countDownLED();
        ledSeqOn = !ledFinished;
        timerOn = ledFinished;
        startTimer();     
    }

    if (timerOn)
    {
        if (getTimeMillis() >= 10000){
            bool broken = (digitalRead(BREAK_BEAM_PIN) == LOW);

            if (broken == HIGH){
                timerOn = false;
            }
        }

        turnOffLed();
        updateTimer();  

    }
}
