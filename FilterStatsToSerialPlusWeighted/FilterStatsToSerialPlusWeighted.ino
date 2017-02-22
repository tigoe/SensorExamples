/**
   FilterStatsToSerial
   Uses the the "Filter" Arduino library and a weighted average to smooth
   a sensor reading

   This code reads an analog sensor and outputs the current value, as well
   as the mean, maximum, minimum, and standard deviation values (based on the
   last 100 values).  the data is then used in a weighted average routine to
   a smoothed sensor reading. The weighted average uses the ratio of the
   standard deviation to the max. std. dev. as its weighting.

   Author: Tom Igoe, adapted from Karl Ward's example
   License: this example code is released into the public domain
   (note that the Filter library itself is not public domain)
*/
// See https://github.com/karlward/Filter
#include "Filter.h"
// See https://github.com/karlward/DataStream
#include "DataStream.h"

float currentEstimate = 0;
float lastEstimate = 0;

// we're going to store 100 values for analysis
Filter filteredData(100);

// and we're going to get those values from pin A0
int analogPin = A0;
// highest recorded standard dev:
float stdDevMax = 0.000001;

void setup() {
  // open serial port to see debugging output
  Serial.begin(9600);
}

void loop() {
  // read the sensor
  int analogValue = analogRead(analogPin);

  // put that sensor value into the Filter object
  filteredData.write(analogValue);

  // calculate mean, median, and standard deviation
  int analogMean = filteredData.mean();
  int analogMaximum = filteredData.maximum();
  int analogMinimum = filteredData.minimum();
  int analogStDev = filteredData.stDevPopulation();

  // calculate the max recorded std. dev:
  if (analogStDev > stdDevMax) {
    stdDevMax = analogStDev;
  }

  //calculate the weighted average weighting factor.
  // This is basically your confidence in the accuracy of the sensor reading,
  // from 0 to 1:
  float confidence = analogStDev / stdDevMax;
  currentEstimate = (analogValue * confidence) + (lastEstimate * (1 - confidence));
  lastEstimate = currentEstimate;


  // output the results to the serial port so you can see them
  Serial.print(confidence);
  Serial.print(",");
  Serial.print(analogValue);
  Serial.print(",");
  Serial.print(currentEstimate);
  Serial.print(",");
  Serial.print(analogMean);
  Serial.print(",");
  Serial.print(analogMaximum);
  Serial.print(",");
  Serial.print(analogMinimum);
  Serial.print(",");
  Serial.print(stdDevMax);
  Serial.print(",");
  Serial.println(analogStDev);
}





