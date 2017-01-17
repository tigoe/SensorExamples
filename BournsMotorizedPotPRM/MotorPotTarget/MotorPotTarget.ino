/*
    Motorized potentiometer controller
    Moves a motorized potentiometer in the direction
    of a target value.

    This was designed to work with a Bourns PRM series potentiometer
    e.g. PRM162-K420K-103B1

    created 17 Jan 2017
    by Tom Igoe
*/
int target = 512;       // target pot value
int noise = 5;          // electrical noise value for pot
void setup() {
  Serial.begin(9600);   // open serial communications
  pinMode(4, OUTPUT);   // H-bridge is on pins 4 and 5
  pinMode(5, OUTPUT);
}

void loop() {
  int sensor = analogRead(A0);        // read pot
  int difference =  target - sensor;  // determine difference
  Serial.print(sensor);               // print sensor
  Serial.print("\t");                 // print tab
  Serial.println(difference);         // print difference

  // if difference is < noise in either direction:
  if (abs(difference) < noise) {
    difference = 0;       // difference is irrelevant
  } 
  moveMotor(difference);  // move motor
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

