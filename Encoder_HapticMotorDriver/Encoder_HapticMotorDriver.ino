/*
Haptic Motor Driver with Encoder

This sketch shows how to use an effect from the effects library
of the TI DRV2605 Haptic Motor Driver(https://cdn-shop.adafruit.com/datasheets/DRV2605.pdf).

Uses Adafruit's library for the driver, and Paul Stoffregen's Encoder library:
https://github.com/adafruit/Adafruit_DRV2605_Library
https://www.pjrc.com/teensy/td_libs_Encoder.html

 created 6 Feb. 2017
 by Tom Igoe
 */

#include <Encoder.h>
#include <Wire.h>           // the motor drier uses I2C
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 motor;     // instance of the motor driver library

Encoder knob(6, 7);         // initialize the encoder on pins 6 and 7    
long lastPosition = 0;      // last position of the knob

void setup() {
  Serial.begin(9600);       // initialize serial communication
  motor.begin();            // initialize motor driver communication
  motor.setWaveform(0, 47);  // buzz1 - 100%
  motor.setWaveform(47, 0);  // ramp down to 0
}

void loop() {
  long knobPosition = knob.read();    // read encoder
  if (knobPosition != lastPosition) { // if it's changed
    motor.go();                       // activate the motor
    Serial.println(knobPosition);     // print the encoder value
  }
  lastPosition = knobPosition;        // save current position for next time
}
