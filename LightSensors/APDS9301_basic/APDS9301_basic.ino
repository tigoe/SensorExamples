/*
  APDS9301 simple example
  Reads the APDS9301 light sensor. See readme.md for more details.

  Circuit:
  * APDS9301 sensor attached to SDA and SCL pins
  
  created 19 Jan 2019
  by Tom Igoe
*/
#include "Wire.h"
#include <Sparkfun_APDS9301_Library.h>

APDS9301 apds;              // instance of the sensor library
int sensorDelay = 0;        // delay for sensor integration time
int lastReadingTime = 0;    // last time sensor was read

void setup() {
  Serial.begin(9600);
  Wire.begin();       // not sure why this isn't included in the APDS lib

  // APDS9301 sensor setup
  // using default sensor I2C address:
  apds.begin(0x39);
  // default is low gain:
  apds.setGain(APDS9301::HIGH_GAIN);
  // integration time can be 13_7, 101, or 402 ms:
  apds.setIntegrationTime(APDS9301::INT_TIME_402_MS);

  // sets the sensor reading delay time based on the integration time:
  switch (apds.getIntegrationTime()) {
    case 0:
      sensorDelay = 14;   // integration time 13.7ms
      break;
    case 1:
      sensorDelay = 101;   // integration time 101ms
      break;
    case 2:
      sensorDelay = 407;   // integration time 402ms
      break;
  }
}

void loop() {
  String results = "CH0: ";
  // if the integration time has passed, read the sensor:
  if (millis() - lastReadingTime >= sensorDelay) {
    results += String(apds.readCH0Level());
    results += String("\tCh 1: ");
    results += String(apds.readCH1Level());
    results += String("\tlux: ");
    results += String(apds.readLuxLevel());
    Serial.println(results);
    lastReadingTime = millis();
  }
}
