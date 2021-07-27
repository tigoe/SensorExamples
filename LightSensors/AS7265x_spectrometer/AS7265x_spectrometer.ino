/*
  AS7265x spectrometer test

  Works with MKR1010, MKR1000, Nano 33 IoT
  Uses the following libraries:
   http://librarymanager/All#SparkFun_AS7265X (for the sensor)

  created 22 Jun 2021
  by Tom Igoe
*/
// include required libraries and config files
#include <SparkFun_AS7265X.h>

// initialize the light sensor:
AS7265X sensor;

void setup() {
  Serial.begin(9600);  // initialize serial communication
  // if serial monitor is not open, wait 3 seconds:
  if (!Serial) delay(3000);
  if (!sensor.begin()) {
    Serial.println("Sensor is not responding. Please check wiring.");
    while (true)
      ;
  }
  // print header labels:
  Serial.println("395nm, 435nm, 460nm, 485nm, 510nm, 535nm, \
  560nm, 585nm, 645nm, 705nm, 900nm, 940nm, \
    610nm, 680nm, 730nm, 760nm, 810nm, 860nm");
}

void loop() {

  // Read all 18 channels. This takes several seconds:
  sensor.takeMeasurements();
  // print a header:
  Serial.print("/* ");
  // Print sensor readings:
  Serial.print(sensor.getCalibratedA());
  Serial.print(",");
  Serial.print(sensor.getCalibratedB());
  Serial.print(",");
  Serial.print(sensor.getCalibratedC());
  Serial.print(",");
  Serial.print(sensor.getCalibratedD());
  Serial.print(",");
  Serial.print(sensor.getCalibratedE());
  Serial.print(",");
  Serial.print(sensor.getCalibratedF());
  Serial.print(",");
  Serial.print(sensor.getCalibratedG());
  Serial.print(",");
  Serial.print(sensor.getCalibratedH());
  Serial.print(",");
  Serial.print(sensor.getCalibratedI());
  Serial.print(",");
  Serial.print(sensor.getCalibratedJ());
  Serial.print(",");
  Serial.print(sensor.getCalibratedK());
  Serial.print(",");
  Serial.print(sensor.getCalibratedL());
  Serial.print(",");
  Serial.print(sensor.getCalibratedR());
  Serial.print(",");
  Serial.print(sensor.getCalibratedS());
  Serial.print(",");
  Serial.print(sensor.getCalibratedT());
  Serial.print(",");
  Serial.print(sensor.getCalibratedU());
  Serial.print(",");
  Serial.print(sensor.getCalibratedV());
  Serial.print(",");
  Serial.print(sensor.getCalibratedW());
  // print a footer:
  Serial.println(" */");
}
