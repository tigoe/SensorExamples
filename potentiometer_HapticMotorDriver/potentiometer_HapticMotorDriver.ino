/*
  Haptic Motor Driver with Potentiometer

  This sketch shows how to use the TI DRV2605 Haptic Motor Driver
  (https://cdn-shop.adafruit.com/datasheets/DRV2605.pdf) in realtime.

  Uses Adafruit's library for the driver:
  https://github.com/adafruit/Adafruit_DRV2605_Library

  created 6 Feb. 2017
  by Tom Igoe
*/

#include <Wire.h>           // the motor drier uses I2C
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 motor;     // instance of the motor driver library

void setup() {
  Serial.begin(9600);       // initialize serial communication
  motor.begin();            // initialize motor driver communication
  // set the motor into realtime mode:
  motor.setMode(DRV2605_MODE_REALTIME);
}

void loop() {
  int sensor = analogRead(A0);              // read the potentiometer
  int level = map(sensor, 0, 1023, 0, 100); // mapt it to 0 - 100             
  motor.setRealtimeValue(level);            // set the motor's realtime level
  Serial.println(level);                    // print the level
}
