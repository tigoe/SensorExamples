/*
  PIR sensor reader
  Assumes a sensor with an activation time of 2 seconds. 
  Example was built with the BS412 mini basic PIR sensor from Adafruit:
  https://www.adafruit.com/product/4666

  This will probably work with other PIR sensors as well, since the BS412's
  behavior is typical of others too.

  The circuit:
  * PIR sensor pin 1 connected to ground
  * PIR sensor pin 2 connected to ground for an on time of 2 sec.
  * PIR sensor pin 3 connnected to 3.3V
  * PIR sensor pin 4 connected to Arduino digital pin 2

  created 3 Jan 2023
  by Tom Igoe
*/
const int sensorPin = 2;
const int resetInterval = 2000;
int lastReading = 0;
long lastRelease = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // if it's been less than the resetInterval, 
  // then skip the rest of the loop:
  if (millis() - lastRelease < resetInterval) return;
  // read the sensor:
  int reading = digitalRead(sensorPin);
  // set the LED using the reading:
  digitalWrite(LED_BUILTIN, reading);
  // // if it's LOW, then the sensor is resetting:
  if (reading != lastReading && reading == LOW) {
    lastRelease == millis();
  }
  // save current reading for comparison next time:
  lastReading = reading;
}