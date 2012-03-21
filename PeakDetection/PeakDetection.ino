/*
Peak Finder
 
 This example finds the peak value of an analog sensor over time. 
 It assumes the sensor is moving in a simple curve.
 
 The program checks to see that the current value is above a given threshold, 
 then checks to see if the value is greater than the previous value. if so, 
 then it saves the current value as a peak. When the current value goes below 
 the threshold again, it outputs the last peak value recorded.
 
 This works only with sensors that settle at zero or below.  Accelerometers
 and other sensors that settle in the middle of their range require a 
 more complex solution.
 
 created 12 Sept. 2005
 modified 20 March 2012
 by Tom Igoe
 
 */

int peakValue = 0;
int sensorValue = 0;
int lastSensorValue = 0;
int threshold = 50;             //set your own value based on your sensors
int noise = 5;                  //set a noise value based on your particular sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  //read sensor on pin A0:
  sensorValue = analogRead(A0);

  //check to see that it's above the threshold:
  if ( sensorValue >= threshold + noise ) { 
    //if it's greater than the last eading,
    // then make it our current peak:
    if ( sensorValue >= lastSensorValue + noise ) { 
      peakValue = sensorValue;
    }
    //if the sensorValue is not above the threshold,
    // then  the last peak value you got would be the actual peak:
  } 
  else {
    if ( peakValue >= threshold ) { 
      //this is the final peak value; take action
      Serial.print("peak reading: ");
      Serial.println(peakValue);
    }

    //reset peakValue, since youyou've finished with this peak:
    peakValue = 0;
  }

  //store the current sensor value for the next loop:
  lastSensorValue = sensorValue;
}
