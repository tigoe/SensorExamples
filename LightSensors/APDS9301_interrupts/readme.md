# APDS9301 Interrupt Example

This example is for experimenting with the interrupts on the APDS9301 light sensor. The readings will only be printed if the interrupt is triggered. 

Sparkfun has a decent[ APDS9301 library](https://github.com/sparkfun/APDS-9301_Breakout) for this sensor, and a [hookup guide](https://learn.sparkfun.com/tutorials/apds-9301-sensor-hookup-guide) that explains its use. This sensor has two photodiodes, one that reads visible light (CH0, 640nm) and one that reads infrared light (CH1, 940nm)

The interrupt can be triggered in one of two ways: either the reading on CH0 goes below the low threshold, or it goes above the high threshold. The threshold settings in the sketch are set to 10 (low) and 100 (high) to begin with. 

To effectively disable the high threshold, set it to the maximum value, 65535.  To effectively disable the low threshold, set it to the maximum value, 0.Try different readings for the thresholds to see how they operate. When you understand them, try changing the integration time and the gain to see how they affect the thresholds.

For more about the sensor's settings, see the Sparkfun [hookup guide](https://learn.sparkfun.com/tutorials/apds-9301-sensor-hookup-guide) and the [APS9301 datasheet](https://cdn.sparkfun.com/assets/3/2/c/0/8/AV02-2315EN0.pdf).


