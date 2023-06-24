/*
  ENS160 AQI sensor/SHTC3 Tempersature and rH sensor

  Reads values from an ENS160 Air Quality Sensor 
  and a SHTC3 tempoerature and relative humidty sensor
  as a JSON string.

  The sensors are attached to the Arduino via the I2C interface. 
  Based on Sparkfun ENS160 temp and humidity compensation example

  created 14 Dec 2022
  by Tom Igoe
*/

#include <Wire.h>
#include "SparkFun_ENS160.h"
#include "SparkFun_SHTC3.h"

// instance of the ENS160 sensor library:
SparkFun_ENS160 AQISensor;
SHTC3 temp_rHSensor;

// last time the client sent a message, in ms:
long lastTimeRead = 0;
// message sending interval:
int interval = 10 * 1000;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // wait for serial monitor to open:
  if (!Serial) delay(3000);

  // attempt to start the sensors:
  Wire.begin();

  // try to initialize the sensors. If they don't respond,
  // report via serial and stop forever (while(true);) :
  if (!AQISensor.begin(0x53)) {
    Serial.println("AQI Sensor is not responding. Check wiring.");
    while (true)
      ;
  }

  if (temp_rHSensor.begin() != SHTC3_Status_Nominal) {
    Serial.println("Temp & Humidity Sensor is not responding. Check wiring.");
    while (1)
      ;
  }
  // Reset the indoor air quality sensor's settings.
  if (!AQISensor.setOperatingMode(SFE_ENS160_RESET)) {
    while (1)
      ;
  }
  // Device needs to be set to idle to apply any settings.
  AQISensor.setOperatingMode(SFE_ENS160_IDLE);
  // get an update from the temp/rH sensor:
  temp_rHSensor.update();
  // wait until sensor returns a value:
  while (temp_rHSensor.lastStatus != SHTC3_Status_Nominal) {
    Serial.println("Humidity and Temperature Sensor is not ready.");
  }
  // read temp and rH:
  float rh = temp_rHSensor.toPercent();
  float tempC = temp_rHSensor.toDegC();

  // Give values to AQI sensor:
  AQISensor.setTempCompensationCelsius(tempC);
  AQISensor.setRHCompensationFloat(rh);
  // delay to make sure updates are written:
  delay(500);
  // Set AQI to standard operation:
  AQISensor.setOperatingMode(SFE_ENS160_STANDARD);
}

void loop() {
  // once every interval, read the sensor:
  if (millis() - lastTimeRead > interval) {
    // if the AQI sensor is ready:
    if (AQISensor.checkDataStatus()) {
      // ask for a reading:
      temp_rHSensor.update();
      // read the results:
      float tempC = AQISensor.getTempCelsius();
      float rh = AQISensor.getRH();

      // the sensor can have four possible states:
      // 0 - Operating ok: Standard Operation
      // 1 - Warm-up: occurs for 3 minutes after power-on.
      // 2 - Initial Start-up: Occurs for the first hour of operation.
      //											 and only once in sensor's lifetime.
      // 3 - No Valid Output
      int ensStatus = AQISensor.getFlags();
      // if the sensor's ready to read, read it:
      int AQI = AQISensor.getAQI();
      int TVOC = AQISensor.getTVOC();
      int eCO2 = AQISensor.getECO2();

      // Make a the JSON String:
      String readingString = "{\"AQI\": aqi, \"TVOC\": tvoc, \ 
\"eCO2\": eco2, \"status\": ensStat, \"temp\": temperature, \
\"humidity\", relHum}";

      // replace the value substrings with actual values:
      readingString.replace("aqi", String(AQI));
      readingString.replace("tvoc", String(TVOC));
      readingString.replace("eco2", String(eCO2));
      readingString.replace("ensStat", String(ensStatus));
      readingString.replace("temperature", String(tempC));
      readingString.replace("relHum", String(rh));
      // send it as JSON:
      Serial.println(readingString);
    }
    // timestamp this message:
    lastTimeRead = millis();
  }
}