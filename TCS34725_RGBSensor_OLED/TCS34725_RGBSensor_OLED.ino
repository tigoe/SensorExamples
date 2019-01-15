/*
  TCS34725 sensor example

  Reads lux, color temperature, red, green, blue
  Uses more accurate dn40 algorithm in Kevin Townsend's library

  Circuit:
   Sensor SCL: Arduino SCL (MKR: SCL UNo: SCL or analog 5)
   Sensor SDA:  Arduino SDA (MKR: SDA UNo: SDA or analog 4)
*/

#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);
  // start sensor:
  while (!tcs.begin()) {
    Serial.println("Looking for sensor...");
    delay(100);
  }

  // initialize the display library:
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 setup failed"));
    while (true);
  }
}

void loop(void) {
  // every 2 seconds, read sensor:
  if (millis() % 2000 < 2) {
    uint16_t r, g, b, c, colorTemp, lux;
    tcs.getRawData(&r, &g, &b, &c);
    colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
    lux = tcs.calculateLux(r, g, b);
    String reading = "CT: ";
    reading += String(colorTemp);
    reading += "\nLux: ";
    reading += lux;
    displayWrite(reading);
  }
}

void displayWrite(String message) {
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}
