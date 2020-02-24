/*
  Stable Potentiometer change sensor

  Sometimes you need a continuously changing analog sensor
  (like a potentiometer) to send only when it stops changing.
  One way to do this is to only send periodically, and only
  if the sensor has changed significantly. This sketch shows
  how that can work.

  Circuit:
  - potentiometer attached to pin A0

  created 23 Feb 2020
  by Tom Igoe
*/

// noise threshold. any change less than this is noise:
int noise = 5;
// previous reading:
int lastReading = 0;
// send interval, in ms:
int sendInterval = 1000;
// last time you sent a reading, in ms:
long lastSendTime = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // if the send interval has passed:
  if (millis() - lastSendTime > sendInterval) {
    // read the sensor:
    int sensor = analogRead(A0);
    // map to a different range if needed:
    //    sensor = map(sensor, 0, 1023, 0, 255);
    // if the difference between current and last > noise:
    if (abs(sensor - lastReading) > noise) {
      // send it:
      Serial.println(sensor);
    }
    // save current reading for comparison next time:
    lastReading = sensor;
    // take a timestamp of when you sent:
    lastSendTime = millis();
  }
}
