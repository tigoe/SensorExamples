/*
  ENS160 AQI sensor

  Reads values from an ENS160 Air Quality Sensor as a JSON string 

  The ENS160 sensor is attached to the Arduino via the I2C interface. 
  Based on Sparkfun ENS160 basic example

  created 12 Dec 2022
  by Tom Igoe
*/

#include <Wire.h>
#include "SparkFun_ENS160.h"

// instance of the ENS160 sensor library:
SparkFun_ENS160 AQISensor;

// last time the client sent a message, in ms:
long lastTimeRead = 0;
// message sending interval:
int interval = 10 * 1000;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // wait for serial monitor to open:
  if (!Serial) delay(3000);

  // attempt to start the sensor:
  Wire.begin();
  if (!AQISensor.begin(0x53)) {
    Serial.println("Sensor is not responding. Check wiring.");
    // stop the program here if the sensor didn't respond:
    while (true)
      ;
  }

  // Reset the indoor air quality sensor's settings:
  if (AQISensor.setOperatingMode(SFE_ENS160_RESET)) {
    Serial.println("Ready.");
  }
  delay(100);
  // Set to standard operation:
  AQISensor.setOperatingMode(SFE_ENS160_STANDARD);
}

void loop() {
  // once every interval, read the sensor:
  if (millis() - lastTimeRead > interval) {

    // the sensor can have four possible states:
    // 0 - Operating ok: Standard Operation
    // 1 - Warm-up: occurs for 3 minutes after power-on.
    // 2 - Initial Start-up: Occurs for the first hour of operation.
    //												and only once in sensor's lifetime.
    // 3 - No Valid Output
    int ensStatus = AQISensor.getFlags();
    // if the sensor's ready to read, read it:
    if (AQISensor.checkDataStatus()) {
      int AQI = AQISensor.getAQI();
      int TVOC = AQISensor.getTVOC();
      int eCO2 = AQISensor.getECO2();

      // Make a the JSON String:
      String readingString = "{\"AQI\": aqi, \"TVOC\": tvoc, \"eCO2\": eco2, \"status\": ensStat}";

      // replace the value substrings with actual values:
      readingString.replace("aqi", String(AQI));
      readingString.replace("tvoc", String(TVOC));
      readingString.replace("eco2", String(eCO2));
      readingString.replace("ensStat", String(ensStatus));
      // send it as JSON:
      Serial.println(readingString);
      // timestamp this message:
      lastTimeRead = millis();
    }
  }
}