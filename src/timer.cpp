#include "timer.h"
#include <TM1637Display.h>

// ===== Hardware configuration =====
#define CLK 17
#define DIO 16
#define BTN_PIN 19

// ===== Internal objects & state =====
static TM1637Display display(CLK, DIO);
static unsigned long startTime = 0;
static bool running = false;

// ===== Public functions =====
void initTimer()
{
    pinMode(BTN_PIN, INPUT);

    display.clear();
    display.setBrightness(7);
}

void startTimer()
{
    startTime = millis();
    running = true;
}

void updateTimer()
{
    if (!running)
        return;

    unsigned long elapsed = millis() - startTime;

    int minutes = (elapsed / 60000) % 100;
    int seconds = (elapsed / 1000) % 60;
    int msHundreds = (elapsed % 1000) / 100;

    uint8_t data[] = {
        display.encodeDigit(minutes % 10),
        display.encodeDigit(seconds / 10),
        display.encodeDigit(seconds % 10),
        display.encodeDigit(msHundreds)
    };

    display.setSegments(data);
}
