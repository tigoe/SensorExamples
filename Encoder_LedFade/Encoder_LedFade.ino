/*
  Rotary encoder controlling the brightness of an LED
  with on-off button

  This sketch uses a rotary encoder to set the fadeState of an LED
  and a pushbutton to turn it on or off to the last set level

  This sketch breaks the problem into three parts:
    read sensors and determine any changes
    use changes to set the level for the LED
    set the LED

  Uses Paul Stoffregen's Encoder library:
  https://www.pjrc.com/teensy/td_libs_Encoder.html

  created 6 Feb. 2017
  by Tom Igoe
*/

#include <Encoder.h>
// turn off hardware interrupts. On an M0-based board, you can skip this line
// because most of the IO pins on those boards have interrupts
#define ENCODER_USE_INTERRUPTS 0

Encoder encoder(6, 7);      // initialize the encoder on pins 6 and 7
long lastPosition = 0;      // last position of the knob
int lastButtonState = HIGH; // last state of the button
int fadeState = 0;          // calculated level for the LED (0-255)
boolean onOffState = false; // whether the light is on or off

void setup() {
  Serial.begin(9600);       // initialize serial communication
  pinMode(5, OUTPUT);       // LED on pin 5
  pinMode(2, INPUT_PULLUP); // pushbutton on pin 2
}

void loop() {
  // this section reads the sensors and determines if they've changed:
  long encoderPos = encoder.read();        // read encoder
  // calculate change in encoder:
  int encoderChange = encoderPos - lastPosition;
  lastPosition = encoderPos;              // save current position for next time

  int buttonState = digitalRead(2);       // read pushbutton
  if (buttonState != lastButtonState) {   // if button has changed
    delay(3);                             // wait a few ms (debounce delay)
    if (buttonState == LOW) {             // if button is pressed
      onOffState = !onOffState;           // change on-off state¨
    }
  }
  lastButtonState = buttonState;                // save current button state for next time

  // this section sets the light level:
  int brightness = 0;                           // variable to hold the light level
  if (onOffState == true) {                     // if the light should be on
    if (encoderChange != 0) {                   // if there was a change in the encoder
      fadeState = fadeState + encoderChange;    // change the fadeState
      fadeState = constrain(fadeState, 0, 255); // constrain it to 0-255
      Serial.println(fadeState);
    }
    brightness = fadeState;                     // set brightness from encoder
  } else {
    // if onOffState is false, turn the LED off:
    brightness = 0;
  }

  // this section controls the light:
  analogWrite(5, brightness);
}
