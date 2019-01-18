I've used a dfew different small joysticks, and I like [this joystick from Adafruit a lot](https://www.adafruit.com/products/512). It's got a select pushbutton, and its pins are nicely arranged so you can connect it directly to any five pins of an Arduino with no shield. This [joystick from Sparkfun](https://www.sparkfun.com/products/9032) can do the same. You'll need the [Sparkfun breakout board](https://www.sparkfun.com/products/9110) as well.

I plug it into the analog pins, then use pins A0 and A4 as Vcc and ground, respectively. Then I configure them as digital outputs, and set A0 high to get voltage from it.  Then I set A3 as a digital input to read the button.  Finally, I read the X and Y outputs of the joystick as plain old analog inputs.


Enjoy.

Tom
