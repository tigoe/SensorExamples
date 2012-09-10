I've used a dfew different small joysticks, and I like <a href="https://www.adafruit.com/products/512">this one from Adafruit</a> a lot. It's got a select pushbutton, and its pins are nicely arranged so you can connect it directly to any five pins of an Arduino with no shield. 

I plug it into the analog pins, then use pins A0 and A4 as Vcc and ground, respectively. Then I configure them as digital outputs, and set A0 high to get voltage from it.  Then I set A3 as a digital input to read the button.  Finally, I read the X and Y outputs of the joystick as plain old analog inputs.


Enjoy.

Tom
