/*
Temperature and Humidity sensors
 
 This example gives temperature and humidity using two inexpensive sensors,
 the Analog Devices TMP36 and the Honeywell HIH-4030.
 
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
 
 Note: If you are using a 3.3V model, adjust the voltage variable accordingly.
 
 created 1 June 2013
 by Tom Igoe
 
 */

float voltage = 5.0;              // analog reference voltage
const float resolution = 1024.0;  // A-to-D resolution

float tempOffset = 0.5;           // temp sensor offset
float tempSlope = 0.01;           // temp sensor slope
float rhSlope = 0.0062 * voltage; // humidity sensor slope
float rhOffset = 0.16 * voltage;  // humidity sensor offset

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the temperature sensor:
  int tempSensor = analogRead(A0);
  // convert to voltage:
  float tempVoltage = (tempSensor/resolution) * voltage;
  // convert to temperature (degrees Celsius):
  float temperature = (tempVoltage -0.5) / tempSlope;

  delay(2);      // give the ADC time to settle
  
  // read the humidity sensor:
  int humiditySensor = analogRead(A1);
  // convert to voltage:
  float humidityVoltage = (humiditySensor/resolution) * voltage; 
  // convert to relative humidity (rH): 
  float sensorRH = (humidityVoltage - rhOffset) / rhSlope;
  // adjust for temperature:
  float trueRH = sensorRH / (1.0546 - (0.00216 * temperature)); 

  // print the results:
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" degrees C");
  Serial.print("\tHumidity: ");
  Serial.print(trueRH);
  Serial.println("%");
  delay(10);
}

