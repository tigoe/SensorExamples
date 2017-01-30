/*
  Soft pot sensor reading

  Reads a SoftPot and uses the peak touch for each time you touch
  to set an LED's brightness.

  The softpot has a pulldown resistor on the wiper
  per this SparkFun tutorial:
  https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v32/experiment-10-reading-a-soft-potentiometer
  The pulldown resistor ensures that the pot returns
  a low value when not touched

  created 30 Jan 2017
  by Tom Igoe

*/

int lastReading = 0;    // last sensor reading
int threshold = 10;     // touch threshold
int brightness = 0;     // LED brightness
int peak = 0;           // touch peak

void setup() {
  Serial.begin(9600);   // initialize serial
  pinMode(11, OUTPUT);  // make the LED pin an output
}

void loop() {
  int sensor = analogRead(A0);   // read sensor
  if (sensor > threshold) {      // if it's above touch threshold
    if (sensor > lastReading) {  // and it's above last reading
      peak = sensor;             // then it's a peak
    } else {                     // otherwise,
      peak = lastReading;        // last reading is a peak
    }
    brightness = peak / 4;       // brightness is based on peak
    analogWrite(11, brightness); // set LED
    Serial.println(brightness);  // print brightness
  }
  lastReading = sensor;          // save current reading for next time
}
