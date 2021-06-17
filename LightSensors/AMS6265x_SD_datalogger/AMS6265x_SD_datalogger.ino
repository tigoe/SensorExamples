/*
  Sets the realtime clock on any of the MKR or M0 boards
  using the compile time and compile date.
  Wakes once a minute to log data from an AMS7265x spectrometer
Uses the following libraries:
   http://librarymanager/All#WiFi101  // use this for MKR1000
   http://librarymanager/All#WiFiNINA  // use this for MKR1010, Nano 33 IoT
   http://librarymanager/All#ArduinoHttpClient
   http://librarymanager/All#Arduino_JSON
   http://librarymanager/All#RTCZero

 http://librarymanager/All#SparkFun_AS7265X

  created 7 May 2021
  by Tom Igoe
*/

#include <Wire.h>
#include <RTCZero.h>
#include <SPI.h>
#include <SD.h>
#include <Arduino_JSON.h>
#include <SparkFun_AS7265X.h>
#include <SPI.h>
//#include <WiFi101.h>        // for MKR1000 modules
#include <WiFiNINA.h>  // for MKR1010 modules
#include <ArduinoHttpClient.h>
// include crypto chip library:
#include <ECCX08.h>
// network names and passwords:
#include "arduino_secrets.h"

const int SD_CHIP_SELECT = 10;
// init realtime clock:
RTCZero rtc;
// init the sensor:
AS7265X sensor;

String logFile = "DATALOG.JS";  // data file name
JSONVar sensorData;

volatile bool alarm = false;  // alarm occurred?
bool SDAvailable = false;     // SD card slot working?

// network socket to server. For HTTP instead of HTTPS,
// use WiFiClient instead of WiFiSSLClient:
WiFiSSLClient netSocket;
// server name:
const char server[] = SECRET_SERVER;
// Server port. For HTTP instead of HTTPS, use 80 instead of 443:
const int port = 443;
// API route:
String route = "/data";
// set the content type:
const char contentType[] = "application/json";

// the HTTP client is global so you can use it in multiple functions below:
HttpClient client(netSocket, server, port);

void setup() {
  Serial.begin(9600);
  // delay 1 second so sleep doesn't occur right away:
  delay(1000);
  // initialize LED pin:
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize SD card:
  while (!SD.begin(SD_CHIP_SELECT))
    ;
  Serial.println("Card working");
  while (!sensor.begin())
      ;
  Serial.println("sensor working");

  // initialize the realtime clock:
  rtc.begin();
  // start the crypto chip and get serial number:
  ECCX08.begin();
  sensorData["uid"] = ECCX08.serialNumber();

  // connect to network and get time:
  connectToNetwork();

  // set wakeup alarm time, once a minute:
  rtc.setAlarmTime(00, 00, 00);
  rtc.enableAlarm(rtc.MATCH_SS);
  rtc.attachInterrupt(connectToNetwork);
}

void loop() {
  readSensor();
  if (Serial) Serial.println(JSON.stringify(sensorData));

  // if you disconnected from the network, reconnect:
  if (WiFi.status() == WL_CONNECTED) {
    // If the there's not a request in progress, make a post request:
    if (!client.connected()) {
      client.post(route, contentType, JSON.stringify(sensorData));
    }

    // delay to wait for server response:
    delay(30);

    // If there is a response available, read it:
    if (client.available()) {
      int statusCode = client.responseStatusCode()
                       // timestamp the request if you got a good response:
                       if (statusCode == 200) {
        if (Serial) Serial.println("successfully logged to server");
      }
      else {
        // log to SD card
      }
      // close the request:
      client.stop();
    }
  } else {
    // if WiFi not connected, write to card:
    writeToSDCard(JSON.stringify(sensorData));
    if (Serial) Serial.println("logged to SD card.");
  }

  // TODO: read from card, upload previous readings

  // go to sleep:
  rtc.standbyMode();
}

void readSensor() {
  sensor.takeMeasurements();
  sensorData["datetime"] = getISOTimeString();
  sensorData["A"] = sensor.getCalibratedA();
  sensorData["B"] = sensor.getCalibratedB();
  sensorData["C"] = sensor.getCalibratedC();
  sensorData["D"] = sensor.getCalibratedD();
  sensorData["E"] = sensor.getCalibratedE();
  sensorData["F"] = sensor.getCalibratedF();
  sensorData["G"] = sensor.getCalibratedG();
  sensorData["H"] = sensor.getCalibratedH();
  sensorData["I"] = sensor.getCalibratedI();
  sensorData["J"] = sensor.getCalibratedJ();
  sensorData["K"] = sensor.getCalibratedK();
  sensorData["L"] = sensor.getCalibratedL();
  sensorData["R"] = sensor.getCalibratedR();
  sensorData["S"] = sensor.getCalibratedS();
  sensorData["T"] = sensor.getCalibratedT();
  sensorData["U"] = sensor.getCalibratedU();
  sensorData["V"] = sensor.getCalibratedV();
  sensorData["W"] = sensor.getCalibratedW();
}

// write a string to the SD card:
void writeToSDCard(String message) {
  // If the SD card initialized correctly,
  // write to it:
  if (SDAvailable) {
    File dataFile = SD.open(logFile, FILE_WRITE);
    if (dataFile) {
      dataFile.println(message);
      dataFile.close();
    }
  }
}

String getISOTimeString() {
  // ISO8601 string: yyyy-mm-ddThh:mm:ssZ
  String timestamp = "20";
  if (rtc.getYear() <= 9) timestamp += "0";
  timestamp += rtc.getYear();
  timestamp += "-";
  if (rtc.getMonth() <= 9) timestamp += "0";
  timestamp += rtc.getMonth();
  timestamp += "-";
  if (rtc.getDay() <= 9) timestamp += "0";
  timestamp += rtc.getDay();
  timestamp += "T";
  if (rtc.getHours() <= 9) timestamp += "0";
  timestamp += rtc.getHours();
  timestamp += ":";
  if (rtc.getMinutes() <= 9) timestamp += "0";
  timestamp += rtc.getMinutes();
  timestamp += ":";
  if (rtc.getSeconds() <= 9) timestamp += "0";
  timestamp += rtc.getSeconds();
  timestamp += "Z";
  return timestamp;
}


void connectToNetwork() {
  int attempts = 0;

  // try to connect to the network:
  while (WiFi.status() != WL_CONNECTED) {
    if (Serial) Serial.println("Attempting to connect to: " + String(SECRET_SSID));
    //Connect to WPA / WPA2 network:
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    delay(2000);
    attempts++;
    // give up  and quit the function after three attempts
    if (attempts > 3) return;
  }

  if (Serial) Serial.println("connected to: " + String(SECRET_SSID));
  IPAddress ip = WiFi.localIP();
  if (Serial) Serial.print(ip);
  if (Serial) Serial.print("  Signal Strength: ");
  if (Serial) Serial.println(WiFi.RSSI());
  // get the time from the network and set the RTC:
  unsigned long epoch = WiFi.getTime();
  if (epoch > 0) {
    rtc.setEpoch(epoch);
  }

  if (Serial) Serial.println(getISOTimeString());
}
