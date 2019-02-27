/*
  Rotary Switch reading on an analog input
  Uses a range of fixed resistors to create ten voltage dividers
  so you can read a 10-position rotary switch with one analog input

  circuit:
  - common pin of rotry switch to Vcc
  - 10Kilohm resistor connects common pin of rotary switch
    to Vcc
  - 10 different fixed resistors connect other pins of switch
    to ground

  created 26 Feb 2019
  by Tom Igoe
*/
// ADC readings for the 10 positions, determined by experiment.
// your values will depend on your resistors:
int settings [] = {880, 865, 795, 760, 700, 625, 340, 265, 230, 195};

void setup() {
  Serial.begin(9600);
}

void loop() {
  // readings vary by +/- 3 points. That's noise:
  int noise = 3;
  // the current setting:
  int thisSetting = -1;
  // read the switch:
  int sensorReading = analogRead(A0);
  // iterate over the possible readings:
  for (int pos = 0; pos < 10; pos++) {
    // if the difference between the sensor reading
    // and a given setting is less than the noise,
    // than the given setting is the one you are on:
    if (abs(sensorReading - settings[pos] <= noise) ) {
      thisSetting = pos;
    }
  }
  // after checking all, print the current setting:
  Serial.println(thisSetting);
}
