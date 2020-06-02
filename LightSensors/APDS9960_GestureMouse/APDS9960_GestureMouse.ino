/*
  APDS9960 Gesture Sensor controls mouse movement

  This example reads gesture data from an APDS9960 sensor on
  the Nano 33 IoT (or any USB-capable board). If a directional gesture
  is detected, the mouse moves 50 pixels in the same direction.


  The circuit:
  - Arduino Nano 33 IoT
  - APDS-9960 sensor attached to SDA and SCL

  created 2 Jun 2020
  by Tom Igoe
  based on the default gesture example for Arduino_APDS9960 library.
*/

#include <Arduino_APDS9960.h>
#include <Mouse.h>

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // initialize the sensor:
  if (!APDS.begin()) {
    Serial.println("Sensor not responding");
    while (true);
  }
  // set sensitivity, range of 0 - 100.
  // Higher is more accurate, less sensitive. Default is 80
  APDS.setGestureSensitivity(90);
  
  // initialize mouse control:
  Mouse.begin();

}
void loop() {
  // if a gesture is detected:
  if (APDS.gestureAvailable()) {
    // read which one it was:
    int gesture = APDS.readGesture();

    switch (gesture) {
      case GESTURE_UP:
        Serial.println("up");
        Mouse.move(0, -50, 0);
        break;
      case GESTURE_DOWN:
        Serial.println("down");
        Mouse.move(0, 50, 0);
        break;
      case GESTURE_LEFT:
        Serial.println("left");
        Mouse.move(-50, 0, 0);
        break;
      case GESTURE_RIGHT:
        Serial.println("right");
        Mouse.move(50, 0, 0);
        break;
    }
  }
}
