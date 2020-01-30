/*
   CCS811 CO2 and TVOC sensor from AMS
   (data sheet: https://ams.com/documents/20143/36005/CCS811_DS000459_7-00.pdf/3cfdaea5-b602-fe28-1a14-18776b61a35a

   This example reads the sensor and displays the basic data
   on a n SSD1306 OLED

   Circuit:
   * CCS811 sensor SDA attached to SDA pin (A4 on Nano and Uno boards)
   * CCS811 SCL attached to SCL pin (A5 on Nano/Uno)
   * CCS811 RST pin attached through 10Kilohn resistor to +V
   * SSD1306 OLED screen SDA and SCL pins attached to SDA and SCL as well.
   
  Adafruit's CCS811 breakout board uses I2C address 0x5A; Sparkfun's
  breakout board uses 0x5B. Change the CCS_ADDR to adjust for your board.

  created 30 Jan 2020
  by Tom Igoe
  based on Adafruit library examples
*/

#include <Adafruit_CCS811.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define CCS_ADDR 0x5B // adafruit board uses 0x5A; Sparkfun uses 0x5B

// make an instance of the sensor library:
Adafruit_CCS811 sensor;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // initialize serial communication
  Serial.begin(9600);
  // wait until serial monitor is opened on the host computer:
  //    while (!Serial);

  // initialize the sensor. If you fail, stop the program running:
  if (!sensor.begin(CCS_ADDR)) {

    Serial.println("Failed to contact sensor. Check wiring.");
    return;
  }

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println("SSD1306 setup failed. Check wiring");
    return;
  }
  oled.setTextSize(2); // Draw 2X-scale text
  oled.setTextColor(WHITE);

}

void loop() {
  // if the sensor is ready to deliver results:
  if (sensor.available()) {
    // try to read the sensor.
    // if sensor reading produces an error, skip the rest:
    if (sensor.readData()) return;

    // otherwise, read the sensors:
    String message = "CO2:";
    message += String(sensor.geteCO2());
    message += "ppm\nTVOC:";
    message += String(sensor.getTVOC());
    message += "ppb";
    // display the results:
    oled.setCursor(0, 0);
    oled.clearDisplay();
    oled.println(message);
    oled.display();
    
    // print the results:
    Serial.println(message);
  }
}
