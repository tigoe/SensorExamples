/*
Absolute change
 
 This example finds absolute value of the change in a sensor between its 
 current value and previous value.
 
 This is useful for sensors whose rest value is in the middle of their range, 
 like microphones and accelerometers. Once you know the absolute value of the change,
 you can work out when the sensor reaches a peak value, regardless of whether
 the peak is a positive or a negative peak.
 
 created 20 March 2012
 modified 20 March 2012
 by Tom Igoe
 
 */

int restValue = 403;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //read sensor on pin A0:
  int sensorValue = analogRead(A0);
  
  int change = abs(restValue - sensorValue);
  Serial.println(change);
}

