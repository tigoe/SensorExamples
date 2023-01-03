# PIR Sensor

This is an example for a PIR (passive infrared) sensor. These sensors typically read a wide field of view, and if they detect any motion, the output pin changes from high to low. They typically need about two seconds to reset. The one used here, the BS412 [mini basic PIR from Adafruit](https://www.adafruit.com/product/4666), has a 120 degree field of view and can read a range of about 5 to 8 meters. 

This code will probably work with other PIR sensors as well, as this behavior is typical of others I have used. 

The pin diagram for this particular model is a bit tricky. It's on page 7 of the [datasheet](https://cdn-shop.adafruit.com/product-files/4666/Datasheet.pdf), and it is the view of the sensor from the bottom (not noted in the sheet). Looking at the sensor itself, there is only one pin that doesn't have a dark circle around it: pin 1. That's how you differentiate it from the others. 

## The Circuit

The pin connections are as follows:
 * PIR sensor pin 1 connected to ground
  * PIR sensor pin 2 connected to ground for an on time of 2 sec.
  * PIR sensor pin 3 connnected to 3.3V (**NOT 5V tolerant**! Use 3.3V)
  * PIR sensor pin 4 connected to Arduino digital pin 2

## The Program

This Arduino program first checks to see if at least two seconds have passed since the sensor was reset (meaning no motion detected). If so, it reads the sensor, sets the built-in LED to the sensor's state and compares its reading to the previous reading. If they're different, then the sensor has either detected motion, or the motion has stopped and it's resetting itself. A high-to-low transition indicates that motion's been detected, and low-to-high means it's no longer detecting motion. That triggers the two-second wait time.

This example uses a quick-and-dirty way of handling the wait time: if it's been less than two seconds since the last release time, it just exits the loop. If you are doing something more complex in your code, you probably want to use something like the [BlinkWithoutDelay](https://www.arduino.cc/en/Tutorial/BuiltInExamples/BlinkWithoutDelay) example, a bit like this:

````
if (millis() - lastRelease > resetInterval) {
  // read the sensor and do your checks 
  // for its change here
}
````