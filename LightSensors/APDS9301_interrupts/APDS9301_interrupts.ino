/*
  APDS9301 interrupt example
  Reads the APDS9301 light sensor when thresholds are crossed. 
  See readme.md for more details.

  Circuit:
  * APDS9301 sensor attached to SDA and SCL pins
  * APDS9301 INT pin attached to INT_PIN of Arduino
  
  created 19 Jan 2019
  by Tom Igoe
*/
#include "Wire.h"
#include <Sparkfun_APDS9301_Library.h>

APDS9301 apds;              // instance of the sensor library
const int INT_PIN = 5;      // sensor interrupt pin. Use 2 or 3 for Uno.
bool interruptFlag = false; // interrupt flag

int sensorDelay = 0;        // delay for sensor integration time
int lastReadingTime = 0;
void setup() {
  Serial.begin(9600);
  Wire.begin();       // not sure why this isn't included in the APDS lib

  // APDS9301 sensor setup
  // using default sensor I2C address:
  apds.begin(0x39);
  // default is low gain:
  apds.setGain(APDS9301::LOW_GAIN);
  // integration time can be 13_7, 101, or 402 ms:
  apds.setIntegrationTime(APDS9301::INT_TIME_13_7_MS);

  // interrupts are generated when CH0 reading is low or high.
  // low 0 disables the low interrupt:
  apds.setLowThreshold(5);
  // high 65535 disables the high interrupt:
  apds.setHighThreshold(65535);
  // set number of readings to base the interrupt on:
  apds.setCyclesForInterrupt(1);
  // enable the interrupt and clear interrupt flag:
  apds.enableInterrupt(APDS9301::INT_ON);
  apds.clearIntFlag();

  // Interrupt setup
  pinMode(INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(5), readInterrupt, FALLING);
}

void loop() {
  if (interruptFlag) {
    Serial.println("Interrupt");
    Serial.print("Ch 0: ");
    Serial.print(apds.readCH0Level());
    Serial.print("\tCh 1: ");
    Serial.print(apds.readCH1Level());
    Serial.print("\tlux: ");
    Serial.println(apds.readLuxLevel());
    lastReadingTime = millis();
    apds.clearIntFlag();
    interruptFlag = false;
  }
}

void readInterrupt() {
  interruptFlag = true;
}
