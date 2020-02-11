/*
  ISL29125 light sensor with OLED display
  
  Reads data from an ISL29125 light sensor and displays it on an SSD1306 OLED display.
  Uses Sparkfun's SparkFunISL29125 library and Adafruit's Adafruit_SSD1306 library.
  
  created 10 Feb 2020
  by Tom Igoe
*/

#include <Wire.h>
#include <SparkFunISL29125.h>

#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    0  // Reset pin for display (0 or -1 if no reset pin)

// initialize display:
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
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
  // if display doesn't initialize, quit:
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display setup failed. Check wiring");
    return;
  }
}

void loop() {
  // make a string to display on the screen:
  String sensorReadings = "r:";
  // Read sensor values  as 16 bit integers:
  sensorReadings += lightSensor.readRed();
  // add newline and next label:
  sensorReadings += "\ng:";
  sensorReadings += lightSensor.readGreen();
  // add newline and next label:
  sensorReadings += "\nb:";
  sensorReadings += lightSensor.readBlue();
  // update the display:
  displayWrite(sensorReadings);
  // take 2 seconds between readings:
  delay(2000);
}

void displayWrite (String message) {
  // clear the display:
  display.clearDisplay();
  // set the text size to 2:
  display.setTextSize(2);
  // set the text color to white:
  display.setTextColor(SSD1306_WHITE);

  // move the cursor to 0,0:
  display.setCursor(0, 0);
  // print the seconds:
  display.print(message);
  // push everything out to the screen:
  display.display();
}
