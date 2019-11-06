/*
   Encoder reset
   Uses the pushbutton on a rotary encoder
   to reset the count on the encoder

  Uses Paul Stoffregen's encoder library:
  http://www.pjrc.com/teensy/td_libs_Encoder.html

  created 19 Feb 2018
  modified 6 Nov 2019
  by Tom Igoe
*/

#include <Encoder.h>
Encoder thisEncoder(2,3);
const int buttonPin = 4;
long lastPosition  = -1;
int lastButtonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
}


void loop() {
  // read the encoder:
  int currentPosition = thisEncoder.read();
  // see if it's changed:
  if (currentPosition != lastPosition) {
    Serial.println(currentPosition);
  }
  // save current position for comparison next time:
  lastPosition = currentPosition;

  // read the pushbutton state:
  int buttonState = digitalRead(buttonPin);
  // see if it's changed:
  if (buttonState != lastButtonState) {
    // if it's currently pressed:
    if (buttonState == LOW) {
      // reset the encoder count:
      thisEncoder.write(0);
      Serial.println("reset");
    }
  }
  // save current state for comparison next time:
  lastButtonState = buttonState;
}
