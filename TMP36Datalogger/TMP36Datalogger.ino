/*
Temperature and Humidity sensors
 
 This example gets temperature and humidity using two inexpensive sensors,
 the Analog Devices TMP36 and the Honeywell HIH-4030. It then writes them to an SD card.
 
 Example derived from the datasheets, and from numerous examples,
 including Adafruit, Bildr, the Arduino forums, and others:
 TMP36 datasheet:http://www.ladyada.net/media/sensors/TMP35_36_37.pdf
 HIH-4030 datasheet:https://www.sparkfun.com/datasheets/Sensors/Weather/SEN-09569-HIH-4030-datasheet.pdf
 Adafruit on TMP36: http://learn.adafruit.com/tmp36-temperature-sensor/
 Bildr on HIH-4030: http://bildr.org/2012/11/hih4030-arduino/
 Arduino forum example for HIH-4030: http://forum.arduino.cc/index.php/topic,19961.0.html
 
 Circuit:
 * TMP36 on A0
 * HIH-4030 on A1
 * SD card on SPI MISO, MOSI, CLK pins, 
 * SD card CS on pin 4
 
 created 1 June 2013
 by Tom Igoe
 
 */


#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;         // CS pin for the SD card. Will change depending on your shield or module
boolean cardReady = false;

float voltage = 5.0;              // analog reference voltage
const float resolution = 1024.0;  // A-to-D resolution

float tempOffset = 0.5;           // temp sensor offset
float tempSlope = 0.01;           // temp sensor slope
float rhSlope = 0.0062 * voltage; // humidity sensor slope
float rhOffset = 0.16 * voltage;  // humidity sensor offset

void setup() {
  Serial.begin(9600);
  cardReady = initializeCard();
}

void loop() {
  float temperature = tempRead(A0);                // get a temperature reading
  delay(2);                                        // give the ADC time to settle
  float humidity = humidityRead(A1, temperature);  // get a humidity reading
  writeToCard(temperature, humidity);              // write the readings to the SD card
  delay(1000);                                     // wait a second
}


float tempRead(int pinNumber) {  // read the temperature sensor:
  int tempSensor = analogRead(pinNumber);
  // convert to voltage:
  float tempVoltage = (tempSensor/resolution) * voltage;
  // convert to temperature (degrees Celsius):
  float currentTemp = (tempVoltage -0.5) / tempSlope;
  return currentTemp;
}


float humidityRead(int pinNumber,float temp) {
  // read the humidity sensor:
  int humiditySensor = analogRead(pinNumber);
  // convert to voltage:
  float humidityVoltage = (humiditySensor/resolution) * voltage; 
  // convert to relative humidity (rH): 
  float sensorRH = (humidityVoltage - rhOffset) / rhSlope;
  // adjust for temperature:
  float trueRH = sensorRH / (1.0546 - (0.00216 * temp)); 
  return trueRH;
} 

boolean initializeCard() {
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return false;
  }
  Serial.println("card initialized.");
  return true; 
}

boolean writeToCard(float temp, float rH) {
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.print(temp);
    dataFile.print(",");
    dataFile.println(rH);
    dataFile.close();
    Serial.println("data written");
    return true;
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening  datalog.txt");
    return false;
  } 
}




