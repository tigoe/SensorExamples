/*
 Adafruit joystick example
 
 Reads an Adafruit joystick and maps the X and Y outputs to a range from
 -1 to 1.  Also inverts the button reading so that pressed = 1 and unpressed = 0
 
 circuit: Adafruit joystick attached to A0 through A4, with Vcc on A0
 (https://www.adafruit.com/products/512)
 
 created 10 Sept 2012
 by Tom Igoe
 
 */
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // configure analog pins for Adafruit joystick:
  pinMode(A0, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, INPUT_PULLUP);    // joystick pushbutton
  // turn on A0 for +v connection of joystick:
  digitalWrite(A0, HIGH);
  // turn off A4 for gnd connection of joystick:
  digitalWrite(A4, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int x = analogRead(A1);
  delay(1);
  int y = analogRead(A2);
  int button = !digitalRead(A3);

  // map x and y readings to a 3-point range
  // and subtract 1 to get -1 to 1, with
  // 0 at rest:
  x = map(x, 0, 1023, 0, 3) - 1;
  y = map(y, 0, 1023, 0, 3) -1;

  // print the results
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.println(button);
}



