/*
  Grove Mini Trackball example
  Uses Grove Mini Trackball:
  https://www.seeedstudio.com/Grove-Mini-Track-Ball.html
  and associated library:
  https://github.com/Seeed-Studio/Grove_Mini_Track_Ball

  Runs on any USB-native Arduino (e.g. MKR boards, Nano 33 IoT, 
  Leonardo, Micro) and turns it into a mouse.

  Created 16 Nov 2022
  by Tom Igoe
 */


#include "MiniTrackball.h"
#include "Wire.h"
#include <Mouse.h>

// make an instance of the trackball library:
MiniTrackBall miniTrackball;
// for tracking the state of the button:
int lastButtonState = LOW;
void setup() {
  // initiate I2C and asynchronous serial and Mouse lib:
  Wire.begin();
  Serial.begin(9600);
  Mouse.begin();
}

void loop() {
  // trackball data array: 0: up, 1: down, 2: left, 3: right, 4: button
  byte track_data[5];
  // read tracking data:
  miniTrackball.GetTrackData(track_data);
  // y movement (up is negative):
  int y = (track_data[1] - track_data[0]) * 4;
  // x movement (left is negative):
  int x = (track_data[3] - track_data[2]) * 4;
  // if x or y have moved:
  if (x != 0 || y != 0) {
    Mouse.move(x, y, 0);
  }
// compare button state to last button state:
  int buttonState = track_data[4];

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      Mouse.press(MOUSE_LEFT);
    } else {
      Mouse.release(MOUSE_LEFT);
    }
  }
  // save button state for comparison next time:
  lastButtonState = buttonState;
  delay(10);
}