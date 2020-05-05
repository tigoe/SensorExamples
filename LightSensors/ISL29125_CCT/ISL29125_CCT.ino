/*
  ISL29125 light sensor with OLED display

  Reads data from an ISL29125 light sensor and displays it on an SSD1306 OLED display.
  Uses Sparkfun's SparkFunISL29125 library and Adafruit's Adafruit_SSD1306 library.

  Sparkfun sensor library: https://github.com/sparkfun/SparkFun_ISL29125_Breakout_Arduino_Library
  ISL29125 datasheet: https://cdn.sparkfun.com/datasheets/Sensors/LightImaging/isl29125.pdf
  Adafruit OLED library:
  SSD1306 datasheet:

  created 10 Feb 2020
  by Tom Igoe
*/

#include <Wire.h>
#include <SparkFunISL29125.h>

// initialize light sensor:
SFE_ISL29125 lightSensor;

void setup() {
  // initialize serial and wait for serial monitor to open:
  Serial.begin(9600);
  while (!Serial);

  // if the light sensor doesn't initialize, quit:
  if (!lightSensor.init()) {
    Serial.println("Light sensor failed. Check wiring.");
    return;
  }
}

void loop() {

  unsigned int red = lightSensor.readRed();
  unsigned int green =  lightSensor.readGreen();
  unsigned int blue =  lightSensor.readBlue();
  unsigned int cct = calculateColorTemperature(red, green, blue);
  unsigned int lux = calculateLux(red, green, blue);
Serial.print(red);
Serial.print("\t");
Serial.print(green);
Serial.print("\t");
Serial.print(blue);
Serial.print("\t");
Serial.print(cct);
Serial.print("\t");
Serial.println(lux);
  // take 2 seconds between readings:
  delay(2000);
}



unsigned int calculateColorTemperature(unsigned int r, unsigned int g,
                                       unsigned int b) {
  float X, Y, Z; /* RGB to XYZ correlation      */
  float xc, yc;  /* Chromaticity co-ordinates   */
  float n;       /* McCamy's formula            */
  float cct;

  if (r == 0 && g == 0 && b == 0) {
    return 0;
  }

  /* 1. Map RGB values to their XYZ counterparts.    */
  /* Based on 6500K fluorescent, 3000K fluorescent   */
  /* and 60W incandescent values for a wide range.   */
  /* Note: Y = Illuminance or lux                    */
  X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
  Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
  Z = (-0.68202F * r) + (0.77073F * g) + (0.56332F * b);

  /* 2. Calculate the chromaticity co-ordinates      */
  xc = (X) / (X + Y + Z);
  yc = (Y) / (X + Y + Z);

  /* 3. Use McCamy's formula to determine the CCT    */
  n = (xc - 0.3320F) / (0.1858F - yc);

  /* Calculate the final CCT */
  cct =
    (449.0F * powf(n, 3)) + (3525.0F * powf(n, 2)) + (6823.3F * n) + 5520.33F;

  /* Return the result  s in degrees Kelvin */
  return (unsigned int)cct;
}

unsigned int calculateLux(unsigned int r, unsigned int g, unsigned int b) {
  float illuminance;
  illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);

  return (unsigned int)illuminance;
}
