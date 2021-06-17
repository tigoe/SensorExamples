/*
  Ohmite FSP test for FSP01CE/FSP02CE sensor

  This example shows how to read position and force on a force-sensing potentiometer. \
  Running a finger up and down the sensor results in a position value from 0 to 100.
  Pressing on the sensor produces a force value that varies from 0 to about 3.
  It uses the M2aglabs_Ohmite library by Marc Graham:
  https://github.com/m2ag-labs/m2aglabs_ohmite
  https://m2aglabs.com/2019/08/14/using-ohmite-force-sensitive-potentiometers/

  The circuit:
  - 10Kohm resistor connects Vref (pin A3) to wiper (pin A2)
  - sensor wiper (pin 1): A2
  - sensor V2 (pin 2): A1
  - sensor V1 (pin 3): A0
  - SSD1306
  Note: only wiper needs to be on an analog pin, others can be digital pins

  created 14 Jun 2020
  by Tom Igoe
*/

#include "M2aglabs_Ohmite.h"

#include <Wire.h>
#include <Adafruit_SSD1306.h>
// see https://learn.adafruit.com/adafruit-gfx-graphics-library/using-fonts
// for a list of fonts available in the GFX lib
// or custom fonts from http://oleddisplay.squix.ch/#/home
#include<Fonts/FreeSans9pt7b.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    0  // Reset pin for display (0 or -1 if no reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// threshold for the force sensing. Range is 0 to about 3:
const float threshold =  0.5;

// sensor is attached to pins A2-A1, with the external resistor going from A2 to A3:
// Same code can be used for FSP01CE and FSP02CE, by changing last parameter.
// FSP01CE: false, FSP02CE: true
M2aglabs_Ohmite sensor(A2, A3, A1, A0, false);

void setup() {
  Serial.begin(9600);
  /*
    begin() sets analog resolution and max voltage.
    defaults are 10 and 3.3
    for Uno, use 10 bits resolution and 5V
    for MKR and Nano33, use 3.3V, and you can use up to 12 bits resolution
    by setting analogReadResolution(12).
  */
  sensor.begin(10, 3.3);
  // I2C address is 0x3C, or 3D for some 128x64 modules:
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display setup failed");
    while (true);
  }
  // set fonts botforh display:
  display.setFont(&FreeSans9pt7b);
  // set the text size to 1:
  display.setTextSize(1);
  // set the text color to white:
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int pos; //Position is an integer
  float force; //Force is a float

  // get the force reading:
  force = sensor.getForce();
  // clear the display:
  display.clearDisplay();

  // move the cursor to 0,0:
  display.setCursor(0, 12);
  // print the seconds:
  display.print("force: " + String(force));

  // if the force is high enough, someone's touching the sensor,
  // so get the position:
  if (force > threshold) {
    // False reads from tail to tip. True reads from tip to tail
    pos = sensor.getPosition(false);
    // move the cursor down 20 pixels:
    display.setCursor(0, 30);
    display.println("position: " + String(pos));
  }
  // push everything out to the screen:
  display.display();
}
