/*
   Motorized potentiometer controller
   Moves a motorized potentiometer back and forth
   across its range.

    This was designed to work with a Bourns PRM series potentiometer
    e.g. PRM162-K420K-103B1

   created 17 Jan 2017
   by Tom Igoe
*/

int direction = 1;

void setup() {
  Serial.begin(9600);   // open serial communications
  pinMode(4, OUTPUT);   // H-bridge is on pins 4 and 5
  pinMode(5, OUTPUT);
}

void loop() {
  int sensor = analogRead(A0);  // read sensor
  Serial.println(sensor);       // print it

  if (sensor >= 1020) {         // if sensor is near top of range
    direction = -1;             // direction is downward
  }
  if (sensor <= 10) {           // if sensor is near bottom of range
    direction = 1;              // direction is upwards
  }
  moveMotor(direction);         // move motor
}

// direction of amount sets direction of motor
// if direction = 0, motor turns off.
// magnitude of direction is not used.
void moveMotor(int amount) {
  if (amount < 0) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  } else {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }
  if (amount == 0) {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
}

