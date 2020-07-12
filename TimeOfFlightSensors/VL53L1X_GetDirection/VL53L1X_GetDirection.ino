/*
  VL53L1X Time-of-flight ROI setting and direction reading example
  Uses Sparkfun's VL53L1X library: http://librarymanager/All#SparkFun_VL53L1X

  Borrows from ST's people counting example, explained here:
  https://www.st.com/resource/en/user_manual/dm00626942-counting-people-with-the-vl53l1x-longdistance-ranging-timeofflight-sensor-stmicroelectronics.pdf

  A C example for this algorithm can be found here:
  https://www.st.com/en/imaging-and-photonics-solutions/vl53l1x.html#tools-software under the title
  PEOPLE COUNTING SW code example for VL53L1X:
  https://www.st.com/content/st_com/en/products/embedded-software/proximity-sensors-software/stsw-img010.html


  This example reads one region of interest of about half the sensor.
  If it gets a good reading, changes the ROI to the other half. When it has two
  good readings, it compares them to infer the direction of movement of an object
  or person in front of the sensor. It's currently incomplete and not reliably working.

  The circuit:
  - VL53L1X SDA connected to SDA (A4)
  - VL53L1X SCL connected to SCL (A4)

  Created 7 July 2020
  by Tom Igoe
  based on Sparkfun examples by Nathan Seidle
  and ST examples
*/

#include <SparkFun_VL53L1X.h>

// People Counting defines (from ST example):
#define NOBODY 0
#define SOMEONE 1
#define LEFT 0
#define RIGHT 1
#define DIST_THRESHOLD_MAX  1000

// instance of the sensor library:
SFEVL53L1X sensor;

// settings for optical center of each ROI. These may need adjustment
// depending on your distance from the sensor, and your application:
unsigned int opticalCenter[] = {159, 231};

// which zone, left (0) or right(1):
int zone = 0;

// width and height of the ROI; These may need adjustment as well:
const int roiWidth = 7;
const int roiHeight = 16;

/*
  values for each SPAD in the sensor array (from the library, for reference).
  Orient the sensor appropriately before reading this array.
  Pin 1 is the corner next to the small circle on the breakout board. On the Sparkfun board,
  it's closest to the SHUTDOWN breakout hole. On the Pololu board, it's closes to the
  ground breakout hole.

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
  120, 112, 104, 96, 88, 80, 72, 64,  56, 48, 40, 32, 24, 16, 8, 0  // pin 1 is here
*/

// moved this from ST function to global for use in loop():
int PplCounter = 0;

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

  // this config comes from the ST people counting example.
  // They seem like reasonable settings:
  sensor.setDistanceModeLong();
  sensor.setTimingBudgetInMs(20);
  sensor.setIntermeasurementPeriod(20);

  // set the ROI for next time:
  sensor.setROI(roiWidth, roiHeight,  opticalCenter[zone]);
}
void loop() {
  // start the sensor reading:
  sensor.startRanging();
  // wait for data to be ready:
  while (!sensor.checkForDataReady()) {
    delay(1);
  }
  byte rangeStatus = sensor.getRangeStatus();
  // rangeStatus = 0 is a good reading.
  // if you don't get a good reading, go back to the beginning of the loop:
  if (rangeStatus != 0)  return;

  // once you have data, get the distance:
  int distance = sensor.getDistance();
  // clear the sensor's interrrupts and stop the sensor reading:
  sensor.clearInterrupt();
  sensor.stopRanging();

  // set the ROI for next time:
  sensor.setROI(roiWidth, roiHeight,  opticalCenter[zone]);

  //  call the ST people counting function. Commented out because I'm trying
  // an alternative:
  //  PplCounter = ProcessPeopleCountingData(distance, zone);

  // Serial.println(PplCounter);
  readDirection(distance, zone);

  // Switch zones from 0 to 1 or 1 to 0:
  zone = !zone;

  // delay to conform to configs above
  delay(20);
}


//////////////////  The below is work in progress


// byte array to track the state of the two ROIs:
byte previous[2];

// this is an attempt at a minimal left-right alborithm. It is not finished.
// it's based on the ideas in the People Counting app note mentioned above,
// an attempt to rewrite the ProcessPeopleCountingData function below for clarity:
void readDirection(int thisDist, int thisZone) {
  int current = 0;  // either you have an object or you don't

  // if the reading in this ROI is short enough, you have an object:
  if (thisDist < DIST_THRESHOLD_MAX) {
    current = 1;
  }

  // not using this yet:
  if (current != previous[zone]) {
    // this zone has changed
  }

  // save current in the appropriate left/right previous position
  // for comparison next time:
  previous[zone] = current;

  //  if you have 0-1 or 1-0 in the left/right positions, you're seeing
  // either an object on entering the sytem or exiting:
  if (previous[0] != previous[1]) {
    Serial.print(previous[0]);
    Serial.print(" ");
    Serial.println(previous[1]);
  }

  // if you're seeing 1-1, you've got an object in both ROIs
  if (previous[0] + previous[1] > 1) {
    Serial.print("   ");
    Serial.print(previous[0]);
    Serial.print(" ");
    Serial.println(previous[1]);
  }

}

/*
  this is the people counting function from
  https://www.st.com/resource/en/user_manual/dm00626942-counting-people-with-the-vl53l1x-longdistance-ranging-timeofflight-sensor-stmicroelectronics.pdf

  A C example for this algorithm can be found here:
  https://www.st.com/en/imaging-and-photonics-solutions/vl53l1x.html#tools-software under the title
  PEOPLE COUNTING SW code example for VL53L1X. The function below is from main.c in that software pack.

  https://www.st.com/content/st_com/en/products/embedded-software/proximity-sensors-software/stsw-img010.html
*/

int ProcessPeopleCountingData(unsigned int thisDist, int thisZone) {
  static int PathTrack[] = {0, 0, 0, 0};
  static int PathTrackFillingSize = 1; // init this to 1 as we start from state where nobody is any of the zones
  static int LeftPreviousStatus = NOBODY;
  static int RightPreviousStatus = NOBODY;
  static int PeopleCount = 0;


  int CurrentZoneStatus = NOBODY;
  int AllZonesCurrentStatus = 0;
  int AnEventHasOccured = 0;

  if (thisDist < DIST_THRESHOLD_MAX) {
    // Someone is in !
    CurrentZoneStatus = SOMEONE;
  }

  // left zone
  if (thisZone == LEFT) {
    if (CurrentZoneStatus != LeftPreviousStatus) {
      // event in left zone has occured
      AnEventHasOccured = 1;
      if (CurrentZoneStatus == SOMEONE) {
        AllZonesCurrentStatus += 1;
      }
      // need to check right zone as well ...
      if (RightPreviousStatus == SOMEONE) {
        // event in left zone has occured
        AllZonesCurrentStatus += 2;
      }
      // remember for next time
      LeftPreviousStatus = CurrentZoneStatus;
    }
  }
  // right zone
  else {
    if (CurrentZoneStatus != RightPreviousStatus) {
      // event in left zone has occured
      AnEventHasOccured = 1;
      if (CurrentZoneStatus == SOMEONE) {
        AllZonesCurrentStatus += 2;
      }
      // need to left right zone as well ...
      if (LeftPreviousStatus == SOMEONE) {
        // event in left zone has occured
        AllZonesCurrentStatus += 1;
      }
      // remember for next time
      RightPreviousStatus = CurrentZoneStatus;
    }
  }

  // if an event has occured
  if (AnEventHasOccured) {
    if (PathTrackFillingSize < 4) {
      PathTrackFillingSize ++;
    }

    // if nobody anywhere lets check if an exit or entry has happened
    if ((LeftPreviousStatus == NOBODY) && (RightPreviousStatus == NOBODY)) {

      // check exit or entry only if PathTrackFillingSize is 4 (for example 0 1 3 2) and last event is 0 (nobobdy anywhere)
      if (PathTrackFillingSize == 4) {
        // check exit or entry. no need to check PathTrack[0] == 0 , it is always the case

        if ((PathTrack[1] == 1)  && (PathTrack[2] == 3) && (PathTrack[3] == 2)) {
          // This an entry
          PeopleCount ++;
          Serial.println("left");

        } else if ((PathTrack[1] == 2)  && (PathTrack[2] == 3) && (PathTrack[3] == 1)) {
          // This an exit
          PeopleCount --;
          Serial.println("right");
        }
      }

      PathTrackFillingSize = 1;
    }
    else {
      // update PathTrack
      // example of PathTrack update
      // 0
      // 0 1
      // 0 1 3
      // 0 1 3 1
      // 0 1 3 3
      // 0 1 3 2 ==> if next is 0 : check if exit
      PathTrack[PathTrackFillingSize - 1] = AllZonesCurrentStatus;
    }
  }

  // output debug data to main host machine
  return (PeopleCount);

}
