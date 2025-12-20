#include "led.h"
#include "speaker.h" 
#include <SPI.h>

// Define the global MAX7219 object here (ONLY once)
MD_MAX72XX mx = MD_MAX72XX(
    HARDWARE_TYPE,
    DIN_PIN,
    CLK_PIN,
    CS_PIN,
    MAX_DEVICES
);

static unsigned long startTimeLED = 0;
static unsigned long startTimeLED2 = 0;
static int playCount = 0;

void initLED()
{
    mx.begin();
    mx.control(MD_MAX72XX::INTENSITY, 5);
    mx.clear();

    // Seed random generator for random LED patterns
    randomSeed(micros());
}

void turnOnRandom(){
    // Fill each device and row with a random pixel mask
    for (int dev = 0; dev < 3; dev++){
        for (int row = 0; row < 8; row++){
            uint8_t mask = (uint8_t)random(0, 256);
            // Ensure at least one pixel is on
            if (mask == 0) mask = 1 << random(0, 8);
            mx.setRow(dev, row, mask);
        }
    }
}

void startLedTimer(){
    startTimeLED = millis();
}

void startLedTimer2(){
    startTimeLED2 = millis();
}

void turnOnLED(int index){
    for (int row = 0; row < 8; row++)
        mx.setRow(index, row, 0xFF);
}

void turnOnLEDsSlowly(int index){
    for (int row = 0; row < 8; row++){
        mx.setRow(index, row, 0xFF);
        delay(200);
    }
}

void turnOffLed(){
    for (int dev = 0; dev < 3; dev++) {
        for (int row = 0; row < 8; row++)
            mx.setRow(dev, row, 0x00);
    }
}

void displayHUJ()
{
    // Pre-defined 8x8 bitmaps for H, U and J (one per device)
    static const uint8_t H[8] = { 0x81, 0x81, 0x81, 0xFF, 0x81, 0x81, 0x81, 0x81 };
    static const uint8_t U[8] = { 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E };
    static const uint8_t J[8] = { 0x3C, 0x18, 0x18, 0x18, 0x18, 0x98, 0x70, 0x00 };

    // Clear display then set each row on the three devices
    turnOffLed();
    for (int row = 0; row < 8; row++) {
        mx.setRow(0, row, H[row]);
        mx.setRow(1, row, U[row]);
        mx.setRow(2, row, J[row]);
    }
}

bool countDownLED()
{ 
    
    unsigned long elapsed = millis() - startTimeLED;
    playCount = playStart(playCount);
    if (playCount == 1){
        turnOnLED(0);
    }
    if (playCount == 2){
        turnOnLED(1);
    }
    if (playCount == 3){
        turnOnLED(2);
    }

    if (elapsed > 5000){
        playCount = 0;
        return true;
    }

    return false;
}


void loadingGameLED()
{ 
    turnOnLEDsSlowly(0);
    turnOnLEDsSlowly(1);        
    turnOnLEDsSlowly(2);
}
