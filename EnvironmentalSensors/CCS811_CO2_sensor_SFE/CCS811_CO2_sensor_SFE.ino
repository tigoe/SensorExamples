/*
   CCS811 CO2 and TVOC sensor from AMS
   (data sheet: https://ams.com/documents/20143/36005/CCS811_DS000459_7-00.pdf/3cfdaea5-b602-fe28-1a14-18776b61a35a

   This example reads the sensor and prints out the basic data.

   Circuit:
   - CCS811 sensor SDA attached to SDA pin (A4 on Nano and Uno boards)
   - CCS811 SCL attached to SCL pin (A5 on Nano/Uno)
   - CCS811 RST pin attached through 10Kilohn resistor to +V

  Uses Sparkfun's library for the sensor (see my other example for the Adafruit library)
  Adafruit's CCS811 breakout board uses I2C address 0x5A; Sparkfun's
  breakout board uses 0x5B. Change the CCS_ADDR to adjust for your board.

  created 30 Jan 2020
  by Tom Igoe
  based on Sparkfun library examples
*/

#include <SparkFunCCS811.h>
#define CCS_ADDR 0x5B // adafruit board uses 0x5A; Sparkfun uses 0x5B

// make an instance of the sensor library:
CCS811 sensor(CCS_ADDR);

void setup() {
  // initialize serial communication
  Serial.begin(9600);
  // the Sparkfun library doesn't initialize the Wire (I2C) library
  // automatically, so you have to do it:
  Wire.begin();

  // initialize the sensor. Sparkfun does begin() differently than most
  // Arduino libraries, in that if begin() succeeds, it returns 0,
  // meaning no error (for most libraries, successful begin() returns 1):
  if (sensor.begin() > 0) {
    Serial.println("Failed to contact sensor. Check wiring.");
    return;
  }
}

void loop() {
  // if the sensor is ready to deliver results:
  if (sensor.dataAvailable()) {
    // try to read the sensor.
    // if sensor reading produces an error, skip the rest:
    if (sensor.readAlgorithmResults()) return;

    // otherwise, read the sensors:
    int co2 = sensor.getCO2();
    int tvoc = sensor.getTVOC();

    // print the results:
    Serial.print("CO2: ");
    Serial.print(co2);
    Serial.print(" ppm, TVOC: ");
    Serial.print(tvoc);
    Serial.println(" ppb");
  }
}
