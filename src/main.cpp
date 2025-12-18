#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <TM1637Display.h>

// ====== Hardware configuration ======
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW   // Most common MAX7219 modules
#define MAX_DEVICES 3

// LED GRID
#define CS_PIN   23
#define CLK_PIN  18
#define DIN_PIN  15

// TIMER
#define CLK 17 // The ESP32 pin GPIO22 connected to CLK
#define DIO 16 // The ESP32 pin GPIO23 connected to DIO

TM1637Display display = TM1637Display(CLK, DIO);
long startTime;

// Create display object (SPI via custom pins)
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DIN_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup()
{
  Serial.begin(9600);

  // button
  pinMode(19, INPUT);

  // led grid
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 5);  // Brightness: 0–15
  mx.clear();

  // timer
  display.clear();
  display.setBrightness(7);
}

void loop()
{
  Serial.print("g");
  static bool stat_seq = false;
  static bool led_finished = false;

  if (digitalRead(19) == 1){
    Serial.println("Clicked");
    stat_seq = true;
  }

  if (stat_seq == true){
    for (int dev = 0; dev < MAX_DEVICES; dev++)
    {
      // Turn ON all LEDs of one matrix
      for (int row = 0; row < 8; row++)
        mx.setRow(dev, row, 0xFF);

      delay(1000);
    }
    
    for (int dev = 0; dev < MAX_DEVICES; dev++){
      for (int row = 0; row < 8; row++)
        mx.setRow(dev, row, 0x00);
    }

    stat_seq = false;
    led_finished = true;
    startTime = millis();
  }

  if (led_finished == true){
    unsigned long elapsed = millis() - startTime;

    // Calculate minutes, seconds, and milliseconds (hundreds)
    int minutes = (elapsed / 60000) % 100; // 2 digits max
    int seconds = (elapsed / 1000) % 60;
    int msHundreds = (elapsed % 1000) / 100;

    // Display MMSSm (minutes, seconds, msHundreds)
    uint8_t data[] = {
        display.encodeDigit(minutes % 10),
        display.encodeDigit(seconds / 10),
        display.encodeDigit(seconds % 10),
        display.encodeDigit(msHundreds)};

    display.setSegments(data);
  }

  delay(100); // update every 100ms

}
