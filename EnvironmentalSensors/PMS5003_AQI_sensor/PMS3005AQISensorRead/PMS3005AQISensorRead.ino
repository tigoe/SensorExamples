/*
  PMS3005 AQI Sensor Reader
  Reads the sensor via UART and prints out the values and their labels

  created 22 Jun 2023
  by Tom Igoe
*/

// a buffer for the raw bytes from the sensor:
byte buffer[32];
// a buffer for the processed data readings:
int readings[13];

// names of each of the data readings (for printing, from the data sheet):
String readingNames[] = {
  "PM1.0 (std particle)",
  "PM2.5 (std particle)",
  "PM10 (std particle)",
  "PM1.0 (under atmospheric environment)",
  "PM2.5 (under atmospheric environment)",
  "PM10 (under atmospheric environment)",
  "particles/0.1L (>0.3um)",
  "particles/0.1L (>0.5um)",
  "particles/0.1L (>1.0um)",
  "particles/0.1L (>2.5um)",
  "particles/0.1L (>5.0um)",
  "particles/0.1L (>10um)",
  "reserved"
};

void setup() {
  // Setup the two UARTs for USB-serial and the sensor:
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // read into the buffer until you hit 0x42:
  int result = Serial1.readBytesUntil(0x42, buffer, 32);
  // if you got no data, skip the rest of the loop:
  if (result <= 0) return;
  // if the second header byte is missing, skip the rest of the loop:
  if (buffer[0] != 0x4D) return;
  // if you got a full buffer (31 bytes), process it and print it:
  if (result == 31) {
    Serial.print("bytes received: ");
    processData();
    // print all the readings:
    for (int r = 0; r < 13; r++) {
      Serial.print(readingNames[r]);
      Serial.print(": ");
      Serial.println(readings[r]);
    }
  }
}

int processData() {
  //  if the first byte is not 0x42, return error -1:
  if (buffer[0] != 0x4D) return -1;

  // calculate checksum starting with the first byte:
  int checksum = 0x42;
  for (int i = 0; i < 29; i++) {
    checksum += buffer[i];
  }

  int checksumValue = (buffer[29] << 8) + buffer[30];
  // if the checksum is wrong, return error -2;
  if (checksum != checksumValue) return -2;

  // if all is good, continue processing:
  int dataLength = (buffer[1] << 8) + buffer[2];
  // boil the next 26 bytes down into 13 data readings:
  for (int r = 0; r < 13; r++) {
    // calculate the actual reading values:
    // you're starting with byte 3 of the buffer:
    int offset = 3;
    // and each reading includes two of the buffer's bytes:
    int bufferIndex = (r * 2) + offset;
    // combine a byte and the one next to it:
    readings[r] = (buffer[bufferIndex] << 8) + buffer[bufferIndex + 1];
  }
  // return success:
  return 0;

  // here's a guide to which readings are in which buffer positions:
  // int pm1Std = (buffer[3] << 8) + buffer[4];
  // int pm25Std = (buffer[5] << 8) + buffer[6];
  // int pm10Std = (buffer[7] << 8) + buffer[8];
  // int pm1Atmo = (buffer[9] << 8) + buffer[10];
  // int pm25Atmo = (buffer[11] << 8) + buffer[12];
  // int pm10Atmo = (buffer[13] << 8) + buffer[14];
  // int particle03 = (buffer[15] << 8) + buffer[16];
  // int particle05 = (buffer[17] << 8) + buffer[18];
  // int particle1 = (buffer[19] << 8) + buffer[20];
  // int particle25 = (buffer[21] << 8) + buffer[22];
  // int particle50 = (buffer[23] << 8) + buffer[24];
  // int particle10 = (buffer[25] << 8) + buffer[26];
  // reserved: buffer 27 and 28
}
