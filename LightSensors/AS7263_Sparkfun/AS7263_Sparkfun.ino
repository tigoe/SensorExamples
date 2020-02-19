/*
  AS7263 color sensor

  Reads light readings and temperature readings from AMS AS7263 sensor.
  Uses Sparkfun's AS726x library. Works with both Sparkfun and Adafruit 
  breakout boards.

  Datasheet: https://ams.com/documents/20143/36005/AS7263_DS000476_1-00.pdf/4bd22964-7fe0-2053-3e97-906f0836182f
   
   Near IR wavelengths:
   610nm: R
   680nm: S
   730nm: T
   760nm: U
   810nm: V
   860nm: W

   According to the datasheet, all channels tested under 5700K White LED light.

   based on Sparkfun libraries
   modified 16 Feb 2020
   by Tom Igoe
*/

#include <AS726X.h>

// make an instance of the color sensor library:
AS726X colorSensor;

void setup() {
  // initialize serial and I2C communication:
  Serial.begin(9600);
  Wire.begin();
  
  // initialize sensor:
  colorSensor.begin();

  // optional sensor settings:
  //Set the measurement mode
  // 0: Continuous reading of STUV
  // 1: Continuous reading of RTUX
  // 2: Continuous reading of all channels (default)
  // 3: One-shot reading of all channels
  colorSensor.setMeasurementMode(2);

  // Integration time = time to get good readings.
  // number is in units of  2.8ms.
  // for measurement mode 2 or 3, you need 280ms, or integrationTime(100)
  // default is 50:
  colorSensor.setIntegrationTime(100);

  // gain sets sensitivity:
  // 0: 1x (default)
  // 1: 3.7x
  // 2: 16x
  // 3: 64x
  colorSensor.setGain(3);
}

void loop() {
  // read sensor:
  colorSensor.takeMeasurements();

  // get results:
  // for uncalibrated readings use .getR(), .getS(), etc.
  // uncalibrated readings are ints, not floats.
  float cR = colorSensor.getCalibratedR();
  float cS = colorSensor.getCalibratedS();
  float cT = colorSensor.getCalibratedT();
  float cU = colorSensor.getCalibratedU();
  float cV = colorSensor.getCalibratedV();
  float cW = colorSensor.getCalibratedW();
  String readings = "IR-R: ";
  readings += String(cR);
  readings += ", IR-S:";
  readings += String(cS);
  readings += ", IR-T:";
  readings += String(cT);
  readings += ", IR-U: ";
  readings += String(cU);
  readings += ", IR-V:";
  readings += String(cV);
  readings += ", IR-W:";
  readings += String(cW);
  
  // get temperature in degrees C (for degrees F, use float .getTemperatureF())
  readings += ", temp.: ";
  readings += String(colorSensor.getTemperature());

  // print results:
  Serial.println(readings);
}
