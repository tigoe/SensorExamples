/*
    Simplified example for the Adafruit LIS3DH accelerometer
    breakout board (https://www.adafruit.com/products/2809)
    based on Kevin Townsend's sample code.

    Note: this code sets the accelerometer to 2G (aka 2x the acceleration
    due to gravity). The accelerometer has a 14-bit range, or -8193 to 8192.
    So at 1G, when the full force of gravity is on one of the axes,
    the reading should be around 4095 for that axis (or -4096, depending on
    the orientation).

    modified 24 Nov 2015
    by Tom Igoe
*/

#include <Wire.h>
#include <Adafruit_LIS3DH.h>

Adafruit_LIS3DH accelerometer = Adafruit_LIS3DH();

void setup() {
  Serial.begin(9600);
  if (! accelerometer.begin(0x18)) {
    Serial.println("Couldn't start. Check wiring.");
    while (true);     // stop here and do nothing
  }

  accelerometer.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!

}

void loop() {
  int adc;
  float volt;
  String output;
  // read the ADCs
  for (int channel = 1; channel < 4; channel++) {
    adc = accelerometer.readADC(channel);
    // LIS3DH ADCs are only sensitive in a range from 1.7V to 0.9V:
    volt = map(adc, -32512, 32512, 1700, 900);
    output = "ADC ";
    output += channel;
    output += ": ";
    output += adc;
    output += "  ";
    output += volt;
    output += " mV\t";
    Serial.print(output);
    delay(10);
  }
  Serial.println();
}
