/*
  PMS5003 simple data read
  Reads the bytes from a PMS5003 sensor and prints them. 
  Does not parse the data.

  created 20 Jun 2023
  by Tom Igoe
*/


void setup() {
  // Initialize both the USB serial port and sensor serial port:
  Serial.begin(9600);
  Serial1.begin(9600);
}
void loop() {
  // if there's incoming serial data from the sensor:
  if (Serial1.available()) {
    // read one byte:
    byte input = Serial1.read();
    // if that byte is the first header byte,
    // print a newline so you can see once  packet per line:
    if (input == 0x42) {
      Serial.println();
    }
    // print the byte no matter what it is:
    Serial.print(input, HEX);
    // print a space after each byte:
    Serial.print(" ");
  }
}