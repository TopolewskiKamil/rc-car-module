#include "timer.h"
#include <TM1637Display.h>

// ===== Hardware configuration =====
#define CLK 17
#define DIO 16
#define BTN_PIN 19

// ===== Internal objects & state =====
static TM1637Display display(CLK, DIO);
static unsigned long startTime = 0;
static unsigned long lastUpdateTime = 0;
static const unsigned long UPDATE_INTERVAL_MS = 100UL;
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
    lastUpdateTime = 0; // allow immediate display update after starting
    running = true;
} 

long getTimeMillis()
{
    return millis() - startTime;
}

void endTimer()
{
    running = false;
} 

void updateTimer()
{
    if (!running)
        return;

    unsigned long now = millis();
    // Only update display every UPDATE_INTERVAL_MS milliseconds
    if (now - lastUpdateTime < UPDATE_INTERVAL_MS)
        return;
    lastUpdateTime = now;

    unsigned long elapsed = now - startTime;

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

void clearTimer()
{
    uint8_t data[] = {
        display.encodeDigit(0),
        display.encodeDigit(0),
        display.encodeDigit(0),
        display.encodeDigit(0)
    };

    display.setSegments(data);
}
