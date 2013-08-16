/*
  TMP36 temperature sensor
 Reads an analog input on pin 0, prints the result to the serial monitor 
 
 */

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  int sensorValue = analogRead(A0);
  // convert the reading to millivolts:
  float voltage = sensorValue *  (5.0/ 1024.0); 
  // convert the millivolts to temperature celsius:
  float temperature = (voltage - 0.5)/0.01;
  // print the temperature:
  Serial.println(temperature);
}





