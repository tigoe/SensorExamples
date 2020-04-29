/*
  Arduino LSM6DS3 orientation

  only prints out the accelerometer orientation if it is stable.
  avoids the problem of having to move through adjacent orientations,
  e.g. left -> top -> right. Instead, it will just print left -> right,
  if you move fast enough.

  created 29 Apr 2020
  by Tom Igoe

*/

#include <Arduino_LSM6DS3.h>
int lastOrientation = -1; // previous orientation of the accelerometer
int sameReading = 0;      // how many times you've gotten the same reading
int threshold = 7;        // how many same readings make the reading stable

void setup() {
  // initialize serial communication:
  Serial.begin(9600);

  // start the IMU:
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (true);
  }
}

void loop() {
  // variables for accelerometer readings:
  float x, y, z;
  // variable for orientation:
  int orientation = -1;
  // if the accelerometer's got readings,
  if (IMU.accelerationAvailable()) {
    // read the accelerometer:
    IMU.readAcceleration(x, y, z);

    // calculate the absolute values, to determine the largest
    int absX = abs(x);
    int absY = abs(y);
    int absZ = abs(z);

    // if Z  is greatest, we must be on the Z axis:
    if ( (absZ > absX) && (absZ > absY)) {
      if (z > 0) {
        orientation = 0;  // Z up
      } else {
        orientation = 1;  // Z down
      }
      // if Y  is greatest, we must be on the Y axis:
    } else if ( (absY > absX) && (absY > absZ)) {

      if (y > 0) {
        // Y up:
        orientation = 2;
      } else {
        // Y down:
        orientation = 3;
      }
      // if X  is greatest, we must be on the X axis:
    } else if ( (absX > absY) && (absX > absZ)) {
      if (x < 0) {
        // X up:
        orientation = 4;
      } else {
        // X down:
        orientation = 5;
      }
    }

    // if we have a valid reading:
    if (orientation > -1 ) {
      // if the reading has been the same many times in a row,
      // then it is stable. print it:
      if (sameReading == threshold) {
        Serial.println(orientation);
      }

      // if the orientation has changed:
      if (orientation != lastOrientation) {
        // save the current for next time:
        lastOrientation = orientation;
        // clear sameReading:
        sameReading = 0;
      } else {
        // increment sameReading:
        sameReading++;
      }
    }
  }
}
