/*
Peak Finder

 This example finds the peak value of an analog sensor over time.
 It assumes the sensor is moving in a simple curve.

 The program checks to see that the current value is above a given threshold,
 then checks to see if the value is greater than the previous value. if so,
 then it saves the current value as a peak. When the current value goes below
 the threshold again, it outputs the last peak value recorded.

 created 12 Sept. 2005
 modified 9 Sept. 2014
 by Tom Igoe

 */

int peakValue = 0;
int threshold = 50;   //set your own value based on your sensors
int noise = 5;        //set a noise value based on your particular sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  //read sensor on pin A0:
  int sensorValue = analogRead(A0);
  // check if it's higher than the current peak:
  if (sensorValue > peakValue) {
    peakValue = sensorValue;
  }
  if (sensorValue <= threshold - noise ) {
    if (peakValue > threshold + noise) {
      Serial.println(peakValue);
      peakValue = 0;
    }
  }
}
