/*
  AS7341 sensor readings.  Reads and prints the results 
  as a CSV string. This version uses a non-blocking 
  approach, using the startReading() and checkReadingProgress() 
  functions. It's about 2 seconds between readings.

  The printing and the JSON file with this sketch are formatted
  for use with Serial Studio:
  https://github.com/Serial-Studio/Serial-Studio

  Library:
  http://librarymanager/All#Adafruit_AS7341

 
  created 18 Jun 2021
  modified 22 Jun 2021
  by Tom Igoe

*/

#include <Adafruit_AS7341.h>
// instance of the sensor library:

Adafruit_AS7341 as7341;
// array to hold the raw readings:
uint16_t readings[12];

void setup() {
  // init serial, wait 3 secs for serial monitor to open:
  Serial.begin(9600);
  if (!Serial) delay(3000);

  if (!as7341.begin()) {
    Serial.println("Sensor not found, check wiring");
    while (true)
      ;
  }

  Serial.println("415nm, 445nm, 480nm, 515nm, 555nm, 590nm, 630nm, 680nm, Clear, 910nm");
  // set integration time:
  as7341.setATIME(35);
  as7341.setASTEP(10000);
  as7341.setGain(AS7341_GAIN_256X);
  // start a new reading cycle:
  as7341.startReading();
}


void loop() {

  //  checkReadingProgress() is non-blocking so you can do
  //  other things in the loop if you wish

  // check to see if readings are done:
  if (as7341.checkReadingProgress()) {
    // if so, read them:
    as7341.getAllChannels(readings);
    // print a header:
    Serial.print("/* ");
    // loop over the readings and print them out:

    for (int r = 0; r < 12; r++) {
      // skip 4 and 5 as they are repeats:
      if (r == 4 || r == 5) continue;
      Serial.print(readings[r]);
      if (r < 11) Serial.print(",");
    }
    // print a footer:
    Serial.println(" */");
    // start a new reading cycle:
    as7341.startReading();
  }
}
