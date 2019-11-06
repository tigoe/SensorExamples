/*
  Encoder and button reader.
  Most encoders have a detent every 4 steps. This example reads
  for the detent steps.

  Circuit:
    - rotary encoder attached to pins 2 and 3
    - pushbutton attached to pin 4, connected to ground

  created 23 Feb 2019
  by Tom Igoe
*/

#include <Encoder.h>

const int buttonPin = 4;    // pushbutton pin
Encoder knob(2, 3);        // encoder on pins 2 and 3
int lastButtonState = LOW;  // last button state
int lastKnobState = -1;     // last knob state
int timestamp = 0;          // timestamp

int steps = 0;
const int maxSteps = 24;

void setup() {
  // initialize button pin and Serial and keyboard:
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // read the sensors:
  int buttonState = digitalRead(buttonPin);
  int knobState = knob.read();

  // if the button has changed:
  if (buttonState != lastButtonState) {
    // debounce the button:
    delay(10);
    // if button is pressed:
    if (buttonState == LOW) {
      Serial.println("button press");
    } else {
      Serial.println("button release");
    }
    // save current state for next time through the loop:
    lastButtonState = buttonState;
  }

  // compare current and last knob state:
  int knobChange = knobState - lastKnobState;
  // if it's changed by 4 or more (one step):
  if (abs(knobChange) >= 4) {
    // get the direction (-1 or 1):
    int knobDirection = (knobChange / abs(knobChange));
    steps += knobDirection;
    // if you want to make the steps rollover, use this:
    //steps = steps % maxSteps;
    
    Serial.println(steps);

    // save knobState for next time through loop:
    lastKnobState = knobState;
  }
}
