/*
  Kalman filter

  Reads an analog sensor on pin A0 and smooths the result with a Kalman filter.
  Uses the SimpleKalmanFilter library (https://github.com/denyssene/SimpleKalmanFilter)
  Install the library from the Library Manager.
  The best way to see the result is to use the Serial Plotter
  from the Tools menu in the Arduino IDE (command-shift-L).

  Circuit:
    Analog sensor attached to pin A0 (use something noisy)

  created 19 Jan 2019
  by Tom Igoe
*/
#include <SimpleKalmanFilter.h>

// first 2 numbers are the amount of variation,
// third is how fast the measurement moves. recommended: 0.01.
// change these values and see how the result changes.
SimpleKalmanFilter filter(2, 2, 0.01);

int intensity = 0;
int lastEstimate = 0;
int peakValue = 0;
int threshold = 605;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // read the input:
  float sensorValue = analogRead(A0);
  Serial.print(sensorValue);
  Serial.print(",");

  // calculate the estimated value with Kalman Filter
  float estimate = filter.updateEstimate(sensorValue);
  Serial.println(estimate);
}
