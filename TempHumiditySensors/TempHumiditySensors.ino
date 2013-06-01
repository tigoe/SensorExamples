/*
Temperature and Humidity sensors
 
 This example gives temperature and humidity using two inexpensive sensors,
 the Analog Devices TMP36 and the Honeywell HIH-4030.
 
 Example derived from the datasheets, and from numerous examples,
 including Adafruit, Bildr, the Arduino forums, and others. 
 Citations coming.
 
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
  int tempSensor = analogRead(A0);
  float tempVoltage = (tempSensor/resolution) * voltage;
  float temperature = (tempVoltage -0.5) / tempSlope;

  int humiditySensor = analogRead(A1);
  float humidityVoltage = (humiditySensor/resolution) * voltage;  
  float sensorRH = (humidityVoltage - rhOffset) / rhSlope;
  float trueRH = sensorRH / (1.0546 - (0.00216 * temperature)); 

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" degrees C");
  delay(10);
}
