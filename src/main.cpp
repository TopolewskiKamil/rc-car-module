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
    static bool falseStart = false;
    static int speakerEndState = 0;
    if (falseStart){
        ledSeqOn = false;
        timerOn = false;
        turnOffLed();
        for (int i = 0; i < 100; i++){
            displayHUJ();
            delay(20);
            turnOffLed();
            delay(10);

        }
        turnOffLed();
        falseStart = false;
    } else {

        if (digitalRead(BTN_PIN)) {
            if (!ledSeqOn){
                clearTimer();
                timerOn = false;
                ledSeqOn = true;
                startLedTimer2();
                loadingGameLED();
                turnOffLed();
                startLedTimer();
                endTimer();
            } else {
                ledSeqOn = false;
            }
        }

        if (ledSeqOn)
        {
            if (digitalRead(BREAK_BEAM_PIN) == LOW){
                falseStart = true;
            }
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

}
