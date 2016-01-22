/*
    Simplified tap example for the Adafruit LIS3DH accelerometer
    breakout board (https://www.adafruit.com/products/2809)
    based on Kevin Townsend's sample code.

    modified 22 Jan 2016
    by Tom Igoe
*/

#include <Wire.h>
#include <Adafruit_LIS3DH.h>

Adafruit_LIS3DH accelerometer = Adafruit_LIS3DH();
// Adjust this number for the sensitivity of the 'click' force
// this strongly depend on the range! for 16G, try 5-10
// for 8G, try 10-20. for 4G try 20-40. for 2G try 40-80
#define CLICKTHRESHHOLD 40

long steps = 0;

void setup() {
  Serial.begin(9600);
  // 0x18 is the accelerometer's default I2C address:
  if (! accelerometer.begin(0x18)) {
    Serial.println("Couldn't start. Check wiring.");
    while (true);     // stop here and do nothing
  }
  // accelerometer range can be 2, 4, 8, or 16G:
  accelerometer.setRange(LIS3DH_RANGE_2_G);

  // 0 = turn off click detection & interrupt
  // 1 = single click only interrupt output
  // 2 = double click only interrupt output, detect single click
  // Adjust threshhold, higher numbers are less sensitive
  accelerometer.setClick(1, CLICKTHRESHHOLD);
  delay(100);
}

void loop() {

  /*
   * Each bit of the click byte value means something different: 
   * bit 0: there's been a tap on the X axis
   * bit 1: tap on the Y axis
   * bit 2: tap on the Z axis
   * bit 3: direction of the tap
   * bit 4: enable single click detection
   * bit 5: enable double click detection
   * 
   * The example below prints out the click value in binary,
   * so you can see each bit in action. Try tapping on all three
   * axes to see how it works:
   */
  byte click = accelerometer.getClick();
  if (click > 0) {
    // print the whole byte in binary:
    Serial.println(click, BIN);
    // print which axis was tapped:
    if (bitRead(click, 0) == 1) {
      Serial.println("tap on X axis");
    }
    if (bitRead(click, 1) == 1) {
      Serial.println("tap on Y axis");
    }
    if (bitRead(click, 2) == 1) {
      Serial.println("tap on Z axis");
    }
  }

  // adjust the delay depending on how frequently you
  // plan to detect clicks. For a step detector, 30 - 80 ms works:
  delay(30);
}
