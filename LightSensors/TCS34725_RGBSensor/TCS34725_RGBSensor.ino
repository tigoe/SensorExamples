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

// Initialize  sensor:
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  // start sensor:
  while (!tcs.begin()) {
    Serial.println("Looking for sensor...");
    delay(100);
  }
}

void loop(void) {
  // every  2 seconds, read sensor:
  if (millis() % 2000 < 2) {
    uint16_t r, g, b, c, colorTemp, lux;
    tcs.getRawData(&r, &g, &b, &c);
    colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
    lux = tcs.calculateLux(r, g, b);
    String reading = "CT: ";
    reading += String(colorTemp);
    reading += " Lux: ";
    reading += lux;
    reading += " R: " + String(r);
    reading += " G: " + String(g);
    reading += " B: " + String(b);
    Serial.println(reading);
  }
}
