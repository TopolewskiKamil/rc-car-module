#include <Arduino.h>
#include <TM1637Display.h>
#include "led.h"

// TIMER
#define CLK 17
#define DIO 16

// Button
#define BTN_PIN 19

TM1637Display display(CLK, DIO);
long startTime;

void setup()
{
  Serial.begin(9600);

  initLED();   // Now comes from led.cpp

  pinMode(BTN_PIN, INPUT);

  display.clear();
  display.setBrightness(7);
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
    startTime = millis();
  }

  if (led_finished)
  {
    unsigned long elapsed = millis() - startTime;

    int minutes = (elapsed / 60000) % 100;
    int seconds = (elapsed / 1000) % 60;
    int msHundreds = (elapsed % 1000) / 100;

    uint8_t data[] = {
        display.encodeDigit(minutes % 10),
        display.encodeDigit(seconds / 10),
        display.encodeDigit(seconds % 10),
        display.encodeDigit(msHundreds)};

    display.setSegments(data);
  }

  delay(100);
}
