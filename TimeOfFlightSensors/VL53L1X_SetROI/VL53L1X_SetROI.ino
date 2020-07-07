/*
  VL53L1X Time-of-flight ROI setting example
  Uses Sparkfun's VL53L1X library: http://librarymanager/All#SparkFun_VL53L1X
  This library has an extensive API that allows you to get and set lots of the properties.
  Listens for settings on the Region  of Interest (ROI).
  To set the ROI, send the following in the serial port:
  s ocX, ocY, roiX, roiY\n
  where
  ocX, ocY - optical center
  roiX, roiY - width and height of region if interest

  To get a sensor reading send space followed by newline

  See the the data sheet and the User manual for details of the properties:
  https://www.st.com/en/imaging-and-photonics-solutions/vl53l1x.html#resource

  For the full API, see
  https://github.com/sparkfun/SparkFun_VL53L1X_Arduino_Library/blob/master/src/SparkFun_VL53L1X.h

  The circuit:
  - VL53L1X SDA connected to SDA (A4)
  - VL53L1X SCL connected to SCL (A4)

  Created 7 July 2020
  by Tom Igoe
  based on Sparkfun examples by Nathan Seidle
*/

#include <SparkFun_VL53L1X.h>

SFEVL53L1X sensor;

// size of the SPAD array:
int arrayWidth = 16;
int arrayHeight = 16;

int roiX = 4;  // min 4
int roiY = 4;  // min 4

// values for each SPAD in the array (from the library):
int spads[] = {
  128, 136, 144, 152, 160, 168, 176, 184,  192, 200, 208, 216, 224, 232, 240, 248,
  129, 137, 145, 153, 161, 169, 177, 185,  193, 201, 209, 217, 225, 233, 241, 249,
  130, 138, 146, 154, 162, 170, 178, 186,  194, 202, 210, 218, 226, 234, 242, 250,
  131, 139, 147, 155, 163, 171, 179, 187,  195, 203, 211, 219, 227, 235, 243, 251,
  132, 140, 148, 156, 164, 172, 180, 188,  196, 204, 212, 220, 228, 236, 244, 252,
  133, 141, 149, 157, 165, 173, 181, 189,  197, 205, 213, 221, 229, 237, 245, 253,
  134, 142, 150, 158, 166, 174, 182, 190,  198, 206, 214, 222, 230, 238, 246, 254,
  135, 143, 151, 159, 167, 175, 183, 191,  199, 207, 215, 223, 231, 239, 247, 255,
  127, 119, 111, 103, 95, 87, 79, 71,  63, 55, 47, 39, 31, 23, 15, 7,
  126, 118, 110, 102, 94, 86, 78, 70,  62, 54, 46, 38, 30, 22, 14, 6,
  125, 117, 109, 101, 93, 85, 77, 69,  61, 53, 45, 37, 29, 21, 13, 5,
  124, 116, 108, 100, 92, 84, 76, 68,  60, 52, 44, 36, 28, 20, 12, 4,
  123, 115, 107, 99, 91, 83, 75, 67,  59, 51, 43, 35, 27, 19, 11, 3,
  122, 114, 106, 98, 90, 82, 74, 66,  58, 50, 42, 34, 26, 18, 10, 2,
  121, 113, 105, 97, 89, 81, 73, 65,  57, 49, 41, 33, 25, 17, 9, 1,
  120, 112, 104, 96, 88, 80, 72, 64,  56, 48, 40, 32, 24, 16, 8, 0
};
// ocX and ocY start with (0,0):
int ocX = 0;
int ocY = 0;
// calculate opticalCenter from array:
unsigned int opticalCenter =  spads[ocX + ocY * arrayWidth];

void setup() {
  // start I2C library:
  Wire.begin();
  // start Serial communications and wait for Serial Monitor to open:
  Serial.begin(9600);
  while (!Serial);

  // sensor.begin works the reverse of many libraries: when it succeeds, it returns 0:
  if (sensor.begin() != 0) {
    Serial.println("VL53L1X not connected, please check your wiring.");
    while (true);
  }
  // set distance to 4m max distance:
  sensor.setDistanceModeLong();
  // tell the sensor to start ranging:
  sensor.startRanging();
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == ' ') {
      // space gets a sensor reading:
      while (!sensor.checkForDataReady());
      // get the distance in mm:
      int distance = sensor.getDistance();
      // print distance in mm:
      Serial.print(distance);
      Serial.println(" mm");
    } else if (cmd == 's') {
      // s signals you want to set ocX, ocY, roiX, roiY:
      ocX = Serial.parseInt();
      ocY = Serial.parseInt();
      roiX = Serial.parseInt();
      roiY = Serial.parseInt();
      ocX = constrain(ocX, 0, arrayWidth - 1);
      ocY = constrain(ocY, 0, arrayHeight - 1);
      roiX = constrain(roiX, 4, arrayWidth);
      roiY = constrain(roiY, 4, arrayHeight);

      opticalCenter =  spads[ocX + ocY * arrayWidth];
      //Set the height and width of the ROI(region of interest) in SPADs.
      // lowest possible option is 4.  optical center is
      // h+1 (right), y-1(above) of the position you want.
      sensor.setROI( roiX, roiY,  opticalCenter);
      Serial.flush();
      printROI();
    }
  }
}

void printROI() {
  Serial.println("SPAD chart: ");
  Serial.println("ocX:\tocY:\troiX:\troiY:\tOC:");
  String data = String(ocX);
  data += "\t" + String(ocY);
  data += "\t" + String(roiX);
  data += "\t" + String(roiY);
  data += "\t" + String(opticalCenter);
  Serial.println(data);
  // iterate over the vertical:
  for (int v = 0; v < arrayHeight; v++) {
    // iterate over the horizontal:
    for (int h = 0; h < arrayWidth; h++) {
      char thisChar = '.';
      // calculate the spad array position of h, v:
      int thisPosition = h + v * arrayWidth;
      int thisSpad = spads[thisPosition];
      // compare this value with the current optical center:
      if (thisSpad == opticalCenter) {
        thisChar = 'x';
      }
      // print the character and a space:
      Serial.write(thisChar);
      Serial.print(" ");
    }
    // end of row:
    Serial.println();
  }
  // end of array:
  Serial.println();
}
