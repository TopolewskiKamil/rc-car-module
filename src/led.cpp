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
static int playCount = 0;

void initLED()
{
    mx.begin();
    mx.control(MD_MAX72XX::INTENSITY, 5);
    mx.clear();
}

void startLedTimer(){
    startTimeLED = millis();
}

void turnOnLED(int index){
    for (int row = 0; row < 8; row++)
        mx.setRow(index, row, 0xFF);
}

void turnOffLed(){
    for (int dev = 0; dev < 3; dev++) {
        for (int row = 0; row < 8; row++)
            mx.setRow(dev, row, 0x00);
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

    if (elapsed > 4000){
        playCount = 0;
        return true;
    }

    return false;
}
