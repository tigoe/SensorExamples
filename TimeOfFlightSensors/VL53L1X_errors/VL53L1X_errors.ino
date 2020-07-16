/*
  VL53L1X Time-of-flight error message
  and timing budget adjustment example
  Uses Sparkfun's VL53L1X library: http://librarymanager/All#SparkFun_VL53L1X
  Prints the distance to an object in mm

  The circuit:
  - VL53L1X SDA connected to SDA (A4)
  - VL53L1X SCL connected to SCL (A4)

  Created 16 July 2020
  by Tom Igoe
  based on Sparkfun examples by Nathan Seidle
*/

#include <SparkFun_VL53L1X.h>

long lastReadingTime = 0;  // last time you took a reading, in ms
int timingBudget = 50;    // timing budget of the sensor, in ms. Adjust to address some error messages
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

  Serial.println("\n\n\nError messages: ");
  Serial.println("There are a few error messages this sensor can give when you use the getRangeStatus() function:");
  Serial.println("0  - Good reading.\n");
  Serial.println("1 - Sigma failure. This means that the repeatability (or standard deviation)\n"
                 "    of the measurement is bad due to a decreasing signal-to-noise ratio. \n"
                 "Increasing the timing budget can help to avoid this error.\n");
  Serial.println("2 - signal failure. This means that the return signal is too weak\n"
                 "    to return a good response. Either the target is too far,or\n"
                 "    the target is not reflective enough, or the target is too small, or\n"
                 "    there may be no target in range. \n"
                 "    Increasing the timing bidget might help, assuming there is a known target in range\n");
  Serial.println("7- wrapped target. If the target is very reflective and the distance to it\n"
                 "   is longer than the sensor's measurable limit (~5m when the sensor in long distance mode,\n"
                 "   ~1.3 m when the sensor is in short distance mode).\n"
                 "   e.g. a retroreflective target at 6m may return a range of about 1m and a rangeStatus of 7.\n");
  Serial.println("\n\nPress enter to start reading.");

  // wait for a byte from the serial monitor:
  while (!Serial.available());
  
  // set distance to 1.3m max distance:
  sensor.setDistanceModeLong();
  // set distance to 4m max distance:
  //  sensor.setDistanceModeLong();

  // set sensor reading timing budget in ms:
  sensor.setTimingBudgetInMs(50);
  //  Intermeasurement period must be > or = timing budget. Default = 100 ms.
  timingBudget = sensor.getTimingBudgetInMs();
  sensor.setIntermeasurementPeriod(timingBudget * 2);
  sensor.startRanging(); // Start once

  // tell the sensor to start ranging:
  sensor.startRanging();
}

void loop() {
  // delay for inter-measurement period:
  if (millis() - lastReadingTime > sensor.getIntermeasurementPeriod()) {
    // Wait until  the sensor has a reading:
    while (!sensor.checkForDataReady());
            Serial.print("ms between readings: ");
    Serial.print(millis() - lastReadingTime);

    
    // timestamp when the sensor was ready:
    lastReadingTime = millis();
    // get the distance in mm:
    int distance = sensor.getDistance();
    // print distance in mm:
        Serial.print("\t distance: ");
    Serial.print(distance);
    Serial.print(" mm");

    byte rangeStatus = sensor.getRangeStatus();
    Serial.print("\tRange Status: ");
    Serial.print(rangeStatus);
    //Make it human readable
    switch (rangeStatus)  {
      case 0:
        Serial.print("  Good reading");
        break;
      case 1:
        Serial.print("  Sigma failure");
        break;
      case 2:
        Serial.print("  Signal failure.");
        break;
      case 7:
        Serial.print("  Wrapped target failure");
        break;
      default:
        Serial.print("  Unknown");
        break;
    }
    Serial.println();
  }
}
