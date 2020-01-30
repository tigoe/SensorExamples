/*
   CCS811 CO2 and TVOC sensor from AMS
   (data sheet: https://ams.com/documents/20143/36005/CCS811_DS000459_7-00.pdf/3cfdaea5-b602-fe28-1a14-18776b61a35a

   This example reads the sensor and prints out the basic data.

   Circuit:
   CCS811 sensor SDA attached to SDA pin (A4 on Nano and Uno boards)
   CCS811 SCL attached to SCL pin (A5 on Nano/Uno)
   CCS811 RST pin attached through 10Kilohn resistor to +V

  Adafruit's CCS811 breakout board uses I2C address 0x5A; Sparkfun's
  breakout board uses 0x5B. Change the CCS_ADDR to adjust for your board.

  created 30 Jan 2020
  by Tom Igoe
  based on Adafruit library examples
*/

#include <Adafruit_CCS811.h>
#define CCS_ADDR 0x5B // adafruit board uses 0x5A; Sparkfun uses 0x5B

// make an instance of the sensor library:
Adafruit_CCS811 sensor;

void setup() {
  // initialize serial communication
  Serial.begin(9600);
  // wait until serial monitor is opened on the host computer:
  while (!Serial);

  // initialize the sensor. If you fail, stop the program running:
  if (!sensor.begin(CCS_ADDR)) {
    Serial.println("Failed to contact sensor. Check wiring.");
    return;
  }

}

void loop() {
  // if the sensor is ready to deliver results:
  if (sensor.available()) {
    // try to read the sensor.
    // if sensor reading produces an error, skip the rest:
    if (sensor.readData()) return;

    // otherwise, read the sensors:
    int co2 = sensor.geteCO2();
    int tvoc = sensor.getTVOC();

    // print the results:
    Serial.print("CO2: ");
    Serial.print(co2);
    Serial.print(" ppm, TVOC: ");
    Serial.print(tvoc);
    Serial.println(" ppb");
  }
}
