/*
  Pachube sensor client with Strings for my office
 
 This sketch connects an analog sensor to Pachube (http://www.pachube.com)
 using an Arduino Ethernet. 
 
 This example has been updated to use version 2.0 of the Pachube.com API. 
 
 
 Circuit:
 * BMP085 Temp and pressure sensor attached to I2C
 * DHT22 Temp and humidity sensor attached to pin 2
 * TSL2561 luminance sensor attached to I2C
 * Ethernet attached to SPI
 
 created  15 March 2010
 updated 1 Nov 2012
 by Tom Igoe with input from Usman Haque and Joe Saavedra
 
 */

// include all Libraries needed:
#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>
#include "TSL2561.h"
#include <BMP085.h>
#include "DHT.h"

#define DHTPIN 2        // DHT22's output pin
#define DHTTYPE DHT22   // DHT 22  (AM2302) as opposed to DHT11

#define APIKEY         "YOUR_KEY"             // replace your pachube api key here
#define FEEDID        00000                   // replace your feed ID
#define USERAGENT      "projectName"          // user agent is the project name


char ssid[] = "networkName";      //  your network SSID (name)
char pass[] = "password";   // your network password

int status = WL_IDLE_STATUS;

// initialize the library instance:
WiFiClient client;

TSL2561 tsl(TSL2561_ADDR_FLOAT); 
BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);

// set up net client info:
char server[] = "api.pachube.com";
unsigned long lastConnectionTime = 0;        // last time you connected to the server, in milliseconds
boolean lastConnected = false;      // state of the connection last time through the main loop
const unsigned long postingInterval = 60000;  //delay between updates to Pachube.com
const unsigned long readingInterval = postingInterval / 10;  // delay between sensor reads;
unsigned long lastReadTime = 0;
String dataString = "";

// set up sensor averaging variables:
float avgTemp = 0.0;
float avgLux = 0.0;
float samples = 0;
float avgPressure = 0.0;
float avgHumidity = 0.0;
float bmpTemp = 0.0;

// an LED to see it's still working:
int blinkState = LOW;

void setup() {
  // start serial port:
  Serial.begin(9600);
  // give the ethernet module time to boot up:
  delay(1000);
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  } 
  
  // you're connected now, so print out the status:
  printWifiStatus();   

  // set up light sensor:
  if (tsl.begin()) {
    Serial.println("Found light sensor");
  } 
  else {
    Serial.println("No light sensor?");
    while (true);
  }
  tsl.setGain(TSL2561_GAIN_16X);      // set 16x gain (for dim situations)
  tsl.setTiming(TSL2561_INTEGRATIONTIME_13MS); 

  // set up BMP085 sensor:
  bmp.begin();  

  // set blink pin:
  pinMode(A0, OUTPUT);
  dht.begin();

  // reserve space for dataString:
  dataString.reserve(100);
}

void loop() {
  // get a timestamp so you can calculate reading and sending intervals:
  long now = millis();

  // if reading interval has passed, read:
  if (millis() - lastReadTime > readingInterval) {
    // increment sample count:
    samples++;   

    // read and average humidity reading from DHT22:    
    float humidity = dht.readHumidity(); 
    if (isnan(humidity)) {
      Serial.println("Failed to read from DHT");
    } 
    else {
      avgHumidity = (avgHumidity*(samples-1) + humidity)/samples; 
    }

    // read and average temperature reading from BMP085:    
    float temperature = bmp.readTemperature();
    avgTemp = (avgTemp*(samples-1) + temperature)/samples; 

    // read and average pressure reading from BMP085:    
    float pressure = bmp.readPressure() / 1000.0;
    avgPressure = (avgPressure*(samples-1) + pressure)/samples; 

    // read and average light reading from TSL2561:    
    long lum = tsl.getFullLuminosity();
    long ir, full;
    ir = lum >> 16;
    full = lum & 0xFFFF;
    long lux = tsl.calculateLux(full, ir);
    avgLux = (avgLux*(samples-1) + lux)/samples; 

    // convert the readings to a String to send it:
    dataString = "temp,";
    dataString += floatToString(avgTemp, 2);
    // add lux:
    dataString += "\nLight,";
    dataString += floatToString(avgLux, 2);
    // add pressure:
    dataString += "\nPressure,";
    dataString += floatToString(avgPressure, 2);

    dataString += "\nHumidity,";
    dataString += floatToString(avgHumidity, 2);
    // if serial monitor's open, print it:
    if (Serial) {
      Serial.println(dataString);
    }
    // toggle the LED to give a physical indicator of activity:
    blinkState = !blinkState;
    digitalWrite(A0, blinkState);

    // update the last reading time:
    lastReadTime = now;
  }
  // if there's incoming data from the net connection,
  // send it out the serial port.  This is for debugging
  // purposes only:
  while (client.available()>0) {
    char c = client.read();
    if (Serial) {
      Serial.write(c);
    }
  }

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  // if you're not connected, and the sending interval has passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (now - lastConnectionTime > postingInterval)) {
    sendData(dataString);
    // reset all the variables for next gathering of data:
    lastConnectionTime = now;
    avgTemp= 0.0;
    avgLux = 0.0;
    avgPressure = 0.0;
    samples = 0;
  }
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();
}

// this method makes a HTTP connection to the server:
void sendData(String thisData) {
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.print("PUT /v2/feeds/");
    client.print(FEEDID);
    client.println(".csv HTTP/1.1");
    client.print("Host: api.pachube.com\n");
    client.print("X-PachubeApiKey: ");
    client.println(APIKEY);
    client.print("User-Agent: ");
    client.println(USERAGENT);
    client.print("Content-Length: ");
    client.println(thisData.length(), DEC);

    // last pieces of the HTTP PUT request:
    client.print("Content-Type: text/csv\n");
    client.println("Connection: close\n");

    // here's the actual content of the PUT request:
    client.println(thisData);
    Serial.println(thisData.length());
    Serial.println(thisData);
    // note the time that the connection was made:
    lastConnectionTime = millis();
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    lastConnected = client.connected();
  }
}


String floatToString(double number, uint8_t digits) 
{ 
  String resultString = "";
  // Handle negative numbers
  if (number < 0.0)
  {
    resultString += "-";
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  resultString += int_part;

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0)
    resultString += "."; 

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    resultString += toPrint;
    remainder -= toPrint; 
  } 
  return resultString;
}



void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}













