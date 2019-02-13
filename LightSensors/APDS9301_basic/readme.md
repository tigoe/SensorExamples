# APDS9301 Basic Example

This example shows how to do a basic reading on the APDS9301 light sensor. It will print out the readings on the visible and infrared channels and the calculated lux level. You can use this example to experiment with the integration time and gain settings. 

Sparkfun has a decent[ APDS9301 library](https://github.com/sparkfun/APDS-9301_Breakout) for this sensor, and a [hookup guide](https://learn.sparkfun.com/tutorials/apds-9301-sensor-hookup-guide) that explains its use. This sensor has two photodiodes, one that reads visible light (CH0, 640nm) and one that reads infrared light (CH1, 940nm)

If you change the integration time setting the sketch will change the delay for when it reads the sensor accordingly.  Changing the integration time will change the values you get on channels 0 and 1, but it shouldn't make a huge difference in the overall lux reading. That reading is based on the ratio of CH0 to CH1, as described on page 4 of the [APS9301 datasheet](https://cdn.sparkfun.com/assets/3/2/c/0/8/AV02-2315EN0.pdf).

If you change the gain settings, you should also see a change in the CH0 and CH1 readings, but not the overall lux reading.

The datasheet details the calculation of lux value based on the channel 0 and 1 levels, as follows (p. 4):

| CH1/CH0| Sensor Lux Formula|
|-----|-----|
| 0 < CH1/CH0 ≤ 0.50 | Sensor Lux = (0.0304 x CH0) – (0.062 x CH0 x ((CH1/CH0)<sup>1.4</sup>))  |
0.50 < CH1/CH0 ≤ 0.61 |  Sensor Lux = (0.0224 x CH0) – (0.031 x CH1)| 
0.61 < CH1/CH0 ≤ 0.80 | Sensor Lux = (0.0128 x CH0) – (0.0153 x CH1)|
0.80 < CH1/CH0 ≤ 1.30 | Sensor Lux = (0.00146 x CH0) – (0.00112 x CH1)|
CH1/CH0>1.30| Sensor Lux = 0|
