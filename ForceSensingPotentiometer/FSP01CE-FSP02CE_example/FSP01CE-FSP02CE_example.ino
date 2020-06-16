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
  Note: only wiper needs to be on an analog pin, others can be digital pins

  created 14 Jun 2020
  by Tom Igoe
*/

#include "M2aglabs_Ohmite.h"

// threshold for the force sensing. Range is 0 to about 3:
const float threshold =  0.5;

// sensor is attached to pins A2-A1, with the external resistor going from A2 to A3:
// Same code can be used for FSP01CE and FSP02CE, by changinf last parameter.
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
}

void loop() {
  int pos; //Position is an integer
  float force; //Force is a float

  // get the force reading:
  force = sensor.getForce();
  Serial.print("force: ");
  Serial.print(force);
  // if the force is high enough, someone's touching the sensor,
  // so get the position:
  if (force > threshold) {
    // False reads from tail to tip. True reads from tip to tail
    pos = sensor.getPosition(false);
    Serial.print("   position: ");
    Serial.print(pos);
  }
  Serial.println();
}
