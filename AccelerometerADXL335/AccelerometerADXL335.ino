/*
ADXL335 Accelerometer
 
 This example reads an ADXL335 accelerometer (Adafruit breakout board model)
 and prints either the analogRead value from each axis.
 
 Circuit:
 * ADXL335 attached to pins A0 - A5 as follows:
 ** Vin: A0
 ** GND: A2
 ** X axis: A5
 ** Y Axis: A4
 ** z Axis:  A3
 
 created 18 Aug 2013
 by Tom Igoe
 
 */

void setup() {
  pinMode(A0, OUTPUT);     // Vin for accelerometer
  pinMode(A2, OUTPUT);     // ground for accelerometer
  digitalWrite(A0, HIGH);  // make A0 a voltage supply for the accelerometer
  digitalWrite(A2, LOW);   // make A2 ground for the accelerometer
  Serial.begin(9600);
}

void loop() {
  int xAxis = analogRead(A5);  // Xout pin of accelerometer
  Serial.print("x: ");
  Serial.print(xAxis);

  int yAxis = analogRead(A4);  // Yout pin of accelerometer
  Serial.print("\ty: ");
  Serial.print(yAxis);

  int zAxis = analogRead(A3);  // Zout pin of accelerometer
  Serial.print("\tz: ");
  Serial.println(zAxis);
}



