/*
    Color view using TCS34725 sensor and NeoPixel
    Based on Adafruit's colorview example for the sensor

    adapted 28 Nov 2021
    by Tom Igoe
*/

// sensor library:
#include <Wire.h>
#include "Adafruit_TCS34725.h"
// neoPixel library:
#include <Adafruit_NeoPixel.h>

// pin number to contro neoPixel:
const int neoPixelPin = 2;  // control pin for the neoPixel
// setup for the pixel:
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, neoPixelPin, NEO_GRB + NEO_KHZ800);

// setup for the sensor:
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_4X);

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  // wait for the serial monitor to open:
  while (!Serial);

  // initialize the neoPixel power and ground on pins 3 and 4:
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  // make them ground (3) and power (4):
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);

  // see if the sensor responds:
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No sensor found. Check your wiring");
    while (true); // stop the program
  }

  // turn off white LED:
  tcs.setInterrupt(true);

  pixel.begin();    // initialize pixel
  pixel.clear();    // turn all LEDs off
}

void loop() {
  // raw values from the sensor:
  float r, g, b, c;
  // converted values:
  int red, green, blue;

  // turn on white LED:
  tcs.setInterrupt(false);
  // takes 154ms to read:
  delay(160);

  // get raw values from sensor:
  tcs.getRGB(&r, &g, &b);

  // turn off white LED:
  tcs.setInterrupt(true);

  // convert the readings to integers:
  red = int(r);
  green = int(g);
  blue = int(b);

  // print them:
  Serial.print("red:");
  Serial.print(red);
  Serial.print(", green:");
  Serial.print(green);
  Serial.print(", blue:");
  Serial.println(blue);

  // convert them to levels for the LED, and turn on the LED:
  pixel.setPixelColor(0, gamma(red), gamma(green), gamma(blue));
  pixel.show();
}

/*
  this function converts the sensor readings
  into equivalent levels for the LED
  (taken from Adafruit example)
  converts reading levels to match the brightness of the LED
  to levels we can see:
*/
int gamma(int rawValue) {
  // take the raw value, make it a floating point number:
  float result = rawValue;
  // divide the result by 255:
  result = result / 255;
  // raise to the 2.5th power:
  result = pow(result, 2.5);
  // multiply by 255:
  result = result * 255;
  // return the final number:
  return result;
}
