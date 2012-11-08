/*  
 Polar Heart beat monitior
 
 This sketch reads a Polar wireless heart rate monitor radio.
 You can use Adafruit's model (product no. 1016) or SparkFun's
 discontinued RMCM01.  You'll also need a Polar T3x Heart Rate
 Transmitter (Adafruit, or any sports store).
 
 The circuit:
 * Heart rate receiver output on digital pin 3
 * Heart rate receiver connected to +5V and ground
 
 Created 17 Oct 2012
 By Tom Igoe with input from Maria Paula Saba dos Reis
 */

// timestamp variables:
long then;            // timestamp for the last heart beat
volatile long now;    // timestamp for the current heart beat

void setup()
{
  // You don't want to miss a beat, so use hardware interrupts
  // to get the heart beat.  Interrupt 0 is on digital pin 3.
  // you have a new heart beat when the signal changes from LOW
  // to high, so look for a RISING change:
  attachInterrupt(0, beat, RISING);
  Serial.begin(9600);
}

void loop()
{
  // if the current heartbeat timestamp is different
  // than the last, then calculate the beats per minute:
  if (now > then) {
    // get the time between beats:
    long interval = now - then; 
    // beats per min = (1000 ms / time between beats) * 60:
    float bpm = (1000.0/interval)*60; 
    Serial.println(bpm);
    // save the current timestamp as the last, for next time:
    then = now;
  }
}

void beat()
{
  // in the interrupt function, all you do is get the timestamp
  // for the current beat. You always want to do as little
  // as possible in an interrupt function:
  now = millis();
}



