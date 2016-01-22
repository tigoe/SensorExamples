/* 
    Simplified example for the Adafruit MMA8451 accelerometer
    breakout board (https://www.adafruit.com/products/2019)
    based on Kevin Townsend's sample code.

    Note: this code sets the accelerometer to 2G (aka 2x the acceleration
    due to gravity). The accelerometer has a 14-bit range, or -8193 to 8192.
    So at 1G, when the full force of gravity is on one of the axes, 
    the reading should be around 4095 for that axis (or -4096, depending on 
    the orientation).

    modified 23 Nov 2015
    by Tom Igoe
*/

#include <Wire.h>
#include <Adafruit_MMA8451.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

void setup(void) {
  Serial.begin(9600);
// initialize communications with the accelerometer:
  if (! mma.begin()) {
    Serial.println("Couldnt start. Check wiring the to the sensor.");
    while (true);   // stop here and do nothing else
  }
  // set accelerometer range to 2G max:
  mma.setRange(MMA8451_RANGE_2_G);
}

void loop() {
  // Read the accelerometer data
  // (ranges from -8193 to 8192 at max acceleration):
  mma.read();
  Serial.print("X: ");
  Serial.print(mma.x);
  Serial.print("\tY: ");
  Serial.print(mma.y);
  Serial.print("\tZ: ");
  Serial.println(mma.z);

}
