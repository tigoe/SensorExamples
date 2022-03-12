

import processing.serial.*;

Serial port;

int red, green, blue = 0;
String ports[];
String whichPort = "";

void setup() {
  size(400, 400);

  //port = new Serial(this, "/dev/cu.usbmodem14201", 9600); 
  //port.clear();
  //port.bufferUntil('\n');
}

void draw() {
  if (port == null) {
    choosePort();
    return;
  }
  background(red, green, blue);
  fill(255);
  // print all the colors out:
  text("range for each color is 0-255: ", 10, 30 );
  text("red: " + red + ", green: " + green + ", blue: " + blue, 10, 60 );
  text("in hexadecimal: #" + hex(red, 2) + hex(green, 2) + hex(blue, 2), 10, 90);
}

void choosePort() {
  background(0);
  fill(255);
  text("type a port number then hit return:", 10, 20); 
  ports = Serial.list();
  for (int p=0; p< ports.length; p++) {
    text(p + ") " + ports[p], 10, 40+(p*20));
  }
}

void keyReleased() {
  println(key);
  if (key >= '0' && key <= '9') {
    // add the keystroke to the whichPort string:
    whichPort += key;
  }
  if (key == ENTER) {
    // if enter is pressed, convert whichPort string into an int:
    int portNum = int(whichPort);
    // if the port num is less than the length of the port list:
    if (portNum < ports.length) {
      // open the port:
      port = new Serial(this, ports[portNum], 9600);
      // clear the port buffers:
      port.clear();
      //generate serialEvents on newline character:
      port.bufferUntil('\n');
    } else {
      // inform the user that they entered a bad port number:
      println(portNum + " is not a port");
      whichPort = "";
    }
  }
}
void serialEvent(Serial thisPort) {
  String incoming = thisPort.readString();
  if (incoming != null) {
    // trim the carriage return and newline, split into three strings:
    String[] colors = trim(split(incoming, ","));
    // iterate over the substrings:
    for (int i=0; i < colors.length; i++) {
      // split the substring into two more substrings on the colon:
      String[] thisColor = split(colors[i], ":");
      // get the color name from the first elements:
      String colorName = trim(thisColor[0]);
      // depending on the color name, assign the second element
      // to a color variable:
      if (colorName.equals("red")) {
        red = int(thisColor[1]);
      }
      if (colorName.equals("green")) {
        green = int(thisColor[1]);
      }
      if (colorName.equals("blue")) {
        blue = int(thisColor[1]);
      }
    }
  }
}
