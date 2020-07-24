/*
  VL53L1X Time-of-flight distance example
  Uses Sparkfun's VL53L1X library: http://librarymanager/All#SparkFun_VL53L1X
  Prints the distance to an object in mm, cm, m, in, ft.

  For greater than 1.3m, use setDistanceModeLong()

  set timing budgets for different distances Sparkfun recommends:
  20ms - short distance, 33ms - medium, 100ms - long distance. 100ms is the default.
  in practice, I found that for beyond 2m, I needed 200 or 500ms.

  The circuit:
  - VL53L1X SDA connected to SDA (A4)
  - VL53L1X SCL connected to SCL (A5)

  Created 6 July 2020
  Modified 21 July 2020
  by Tom Igoe
  based on Sparkfun examples by Nathan Seidle
*/

#include <SparkFun_VL53L1X.h>

int timingBudget = 33;
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
  // set distance to 1.3m max distance:
  sensor.setDistanceModeShort();
  // set distance to 4m max distance:
  //  sensor.setDistanceModeLong();

  // set sensor reading timing budget in ms:
  sensor.setTimingBudgetInMs(timingBudget);
  // Intermeasurement period must be > or = timing budget.
  timingBudget = sensor.getTimingBudgetInMs();
  sensor.setIntermeasurementPeriod(timingBudget);
}

void loop() {
  //initiate measurement:
  sensor.startRanging();
  // See if the sensor has a reading:
  while (!sensor.checkForDataReady());
  // get the distance in mm:
  int distance = sensor.getDistance();
  // clear the sensor's interrupt and turn off ranging:
  sensor.clearInterrupt();
  sensor.stopRanging();

  // if you didn't get a good reading, exit the loop:
  if (sensor.getRangeStatus() != 0) return;

  // if you did get a good reading,
  // print distance in mm:
  Serial.print(distance);
  Serial.print(" mm, ");

  // if you don't like millimeters:
  float cm = distance / 10.0;
  float meters = distance / 1000.0;
  float inches = distance  * 0.03937007;
  float feet = inches / 12.0;
  Serial.print(cm, 2);
  Serial.print(" cm, ");
  Serial.print(meters, 2);
  Serial.print(" m, ");
  Serial.print(inches, 2);
  Serial.print(" in, ");
  Serial.print(feet, 2);
  Serial.print(" ft");

  Serial.println();
}
