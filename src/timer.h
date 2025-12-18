#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

// Initialize timer hardware (TM1637, button pin)
void initTimer();

// Call when the timer should start
void startTimer();

// Call repeatedly from loop() to update display
void updateTimer();

#endif
