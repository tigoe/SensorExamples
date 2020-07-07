
/*
  VL53L1X Time-of-flight config settings example
  Uses Sparkfun's VL53L1X library: http://librarymanager/All#SparkFun_VL53L1X
  This library has an extensive API that allows you to get and set lots of the properties.
  Prints all the sensor properties that you can get with the Sparkfun library's API.

  See the the data sheet and the User manual for details of the properties:
  https://www.st.com/en/imaging-and-photonics-solutions/vl53l1x.html#resource

  For the full API, see
  https://github.com/sparkfun/SparkFun_VL53L1X_Arduino_Library/blob/master/src/SparkFun_VL53L1X.h

  The circuit:
  - VL53L1X SDA connected to SDA (A4)
  - VL53L1X SCL connected to SCL (A4)

  Created 6 July 2020
  by Tom Igoe
  based on Sparkfun examples by Nathan Seidle
*/

#include <SparkFun_VL53L1X.h>

SFEVL53L1X sensor;

void setup() {
  // start I2C library:
  Wire.begin();
  // start Serial communications and wait for Serial Monitor to open:
  Serial.begin(9600);
  while (!Serial);

  // sensor.begin works the reverse of many libraries: when it succeeds, it returns 0:
  if (sensor.begin() != 0) {
    Serial.println("VL53L1X not connected, please check your wiring.");
    while (true);
  }
  Serial.println();
  Serial.println("VL53L1X Sensor configuration: ");
  Serial.println();
  // assemble the software version into a string:
  String softwareVersion = String(sensor.getSoftwareVersion().major);
  softwareVersion += ".";
  softwareVersion += String(sensor.getSoftwareVersion().minor);
  softwareVersion += ".";
  softwareVersion += String(sensor.getSoftwareVersion().build);
  softwareVersion += ".";
  softwareVersion += String(sensor.getSoftwareVersion().revision);
  Serial.print("Software Version: ");
  Serial.println(softwareVersion);

  // get the other properties:
  Serial.print("I2C address: 0x");
  Serial.println(sensor.getI2CAddress(), HEX);
  Serial.print("Interrupt Polarity: ");
  Serial.println(sensor.getInterruptPolarity());
  Serial.print("Timing Budget (ms): ");
  Serial.println(sensor.getTimingBudgetInMs());
  Serial.print("Distance Mode: ");
  Serial.println(sensor.getDistanceMode());
  Serial.print("Inter-measurement Period (ms): ");
  Serial.println(sensor.getIntermeasurementPeriod());
  Serial.print("Sensor ID: 0x");
  Serial.println(sensor.getSensorID(), HEX);
  Serial.print("Signal per SPAD (kcps/SPAD): ");
  Serial.println(sensor.getSignalPerSpad());
  Serial.print("ambient noise when not measuring a signal (kcps/SPAD): ");
  Serial.println(sensor.getAmbientPerSpad());
  Serial.print("signal rate (kcps. All SPADs combined) ");
  Serial.println(sensor.getSignalRate());
  Serial.print("current number of enabled SPADs: ");
  Serial.println(sensor.getSpadNb());
  Serial.print("total ambient rate (kcps. All SPADs combined):");
  Serial.println(sensor.getAmbientRate());
  Serial.print("current offset (mm):");
  Serial.println(sensor.getOffset());
  Serial.print("current crosstalk value (cps):");
  Serial.println(sensor.getXTalk());
  Serial.print("distance threshold window option: ");
  Serial.println(sensor.getDistanceThresholdWindow());
  Serial.print("Distance lower bound (mm):");
  Serial.println(sensor.getDistanceThresholdLow());
  Serial.print("Distance upper bound (mm):");
  Serial.println(sensor.getDistanceThresholdHigh());

  Serial.print("Region of Interest size (x, y in SPADs):");
  Serial.print(sensor.getROIX());
  Serial.print(",");
  Serial.println(sensor.getROIY());
  Serial.print("signal threshold (kcps):");
  Serial.println(sensor.getSignalThreshold());
  Serial.print("current sigma threshold: ");
  Serial.println(sensor.getSigmaThreshold());

  // that's the whole config:
  while (true);
}

void loop() {

}
