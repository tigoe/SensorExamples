/*
  Thumb Joystick example
  Written with https://www.sparkfun.com/products/9426,
  but should work with most analog joysticks,
  with some adjustment

  circuit:
  - x axis on analog in 0
  - y axis on analog in 1

  created 26 Feb 2019
  by Tom Igoe
*/
#include <Mouse.h>

void setup() {
  Serial.begin(9600);
  Mouse.begin();
}

void loop() {
  // variables for x and y movement:
  int xMove = 0;
  int yMove = 0;
  // map joystick's raw output from 200-900 to -3 to 3:
  int x = map(analogRead(A0), 200, 900, -3, 3);
  delay(1);
  int y = map(analogRead(A1), 200, 900, -3, 3);

  // The thumb joystick had some play;
  // it never came back exactly to center.
  // So if -1 < x or y < 1, take it as a movement value:
  if (abs(x) > 1) xMove = x;
  if (abs(y) > 1) yMove = y;
  Mouse.move(xMove, yMove, 0);
}
