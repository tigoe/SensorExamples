/*
  PMS5003 sensor reader 
  buffer read test

  Reads the UART buffer from a PMS3005 AQI sensor and prints it out.
  Uses the Serial.readBytesUntil() function to look for the header. 

  created 21 Jun 2023
  by Tom Igoe
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
}
byte buffer[32];

void loop() {
  // read into the buffer until you hit 0x42:
  int result = Serial1.readBytesUntil(0x42, buffer, 32);
  // print the number of bytes you got:
  Serial.print("Bytes received: ");
  Serial.println(result);
  // if you got no data, skip the rest of the loop:
  if (result <= 0) return;
  // if you didn't get the second header byte, skip the rest of the loop:
  if (buffer[0] != 0x4D) return;
  // print each byte you got:
  for (int i = 0; i < result; i++) {
    Serial.print(buffer[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}
