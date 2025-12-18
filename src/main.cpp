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
    static int speakerEndState = 0;

    if (digitalRead(BTN_PIN)) {
        timerOn = false;
        ledSeqOn = true;
        startLedTimer();
        // speakerEnd = false;
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
        if (speakerEndState != 2){
            speakerEndState = playEnd(speakerEndState);
            turnOffLed();
        } else {
            timerOn = false;
            speakerEndState = 0;
        }
    //     updateTimer();  
    //     delay(100);
    }
}
