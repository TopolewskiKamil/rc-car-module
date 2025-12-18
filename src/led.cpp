#include "led.h"
#include <SPI.h>

// Define the global MAX7219 object here (ONLY once)
MD_MAX72XX mx = MD_MAX72XX(
    HARDWARE_TYPE,
    DIN_PIN,
    CLK_PIN,
    CS_PIN,
    MAX_DEVICES
);

void initLED()
{
    mx.begin();
    mx.control(MD_MAX72XX::INTENSITY, 5); // Brightness 0–15
    mx.clear();
}

void countDownLED()
{
    for (int dev = 0; dev < 3; dev++){
      for (int row = 0; row < 8; row++)
        mx.setRow(dev, row, 0xFF);
        delay(1000);
    }

    for (int dev = 0; dev < 3; dev++) {
      for (int row = 0; row < 8; row++)
        mx.setRow(dev, row, 0x00);
    }
}
