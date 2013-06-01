/*
ADXL326 Accelerometer

  For Arduino Leonardo and other 32U4-based boards
 
 This example reads an ADXL accelerometer and prints either the voltage
 from each axis, or the g-force from each axis.
 
 When the serial port is opened by a remote program or the Serial Monitor,
 the sketch prints out the units it's using and the range first.

 
 Circuit:
 * ADXL326 attached to pins A0 - A2
 * ADXL 3Vo pin attached to AREF
 * ADXL326 is powered off of 3.3V, not 5V 
 
 created 1 June 2013
 by Tom Igoe
 
 */

float voltage = 3.3;              // analog reference voltage
const float resolution = 1024.0;  // A-to-D resolution
float sensitivity = 0.057;        // from the datasheet, output is 57mV/g
float restVoltage = 1.65;         // output at 0g = 1.65V
String  units = "g";              // use "Volts" if you want voltage output
String range = "-16, 16";         // use "0, 3.3" for voltage

void setup() {
  Serial.begin(9600);            // initialize serial communication
  analogReference(EXTERNAL);     // use the external AREF pin
  waitForListener();             // wait for the serial port to open
}

void loop() {
  // read the X axis:
  int x = analogRead(A0);                                // read the X axis
  float xVoltage = (x/resolution) * voltage;             // convert to voltage:
  float xAccel = (restVoltage - xVoltage)/ sensitivity;  // convert to g's
  delay(2);                                              // give the ADC time to settle


  int y = analogRead(A1);                                // read the X axis
  float yVoltage = (y/resolution) * voltage;             // convert to voltage:
  float yAccel = (restVoltage - yVoltage)/ sensitivity;  // convert to g's
  delay(2);                                              // give the ADC time to settle


  int z = analogRead(A2);                                // read the X axis
  float zVoltage = (z/resolution) * voltage;             // convert to voltage:
  float zAccel = (restVoltage - zVoltage)/ sensitivity;  // convert to g's


  // print the results:
  if (units == "g") {
    Serial.print(xAccel);
    Serial.print(",");
    Serial.print(yAccel);
    Serial.print(",");
    Serial.println(zAccel);
  }

  if (units == "Volts") {
    Serial.print(xVoltage);
    Serial.print(",");
    Serial.print(yVoltage);
    Serial.print(",");
    Serial.println(zVoltage);
  }

  delay(10);

  if (!Serial) {         // check to see if the serial port is closed
    Serial.flush();      // clear the serial buffer
    waitForListener();   // wait until the serial port's opened
  }
}

// waits for the serial port to open from the remote end
void waitForListener() {
  while(!Serial);               // do nothing while the port is closed
  Serial.print(units);          // print the units
  Serial.print(",");
  Serial.println(range);        // print the range

}




