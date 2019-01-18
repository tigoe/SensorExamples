# Accelerometers

This folder contains examples for various accelerometers.

## Analog Devices ADXL3xx

Analog Devices makes a family of accelerometers, the [ADXL3xx accelerometers](https://www.analog.com/en/parametricsearch/11175#/p4503=select%20all&p4504=select%20all&sel=row33|row34|row31|row48), with analog voltage outputs for each axis. They are very simple to use with a microcontroller, because all you need to do is power them and connect their outputs to analog inputs of your microcontroller.  For Arduino, there is no library needed to use these accelerometers. Different models have different sensitivities. Sparkfun has breakout boards for the [ADXL337 and ADXL377](https://learn.sparkfun.com/tutorials/adxl337-and-adxl377-accelerometer-hookup-guide). Adafruit has boards for the [ADXL326](https://www.adafruit.com/product/1018), [ADXL335](https://www.adafruit.com/product/163), and [ADXL377](https://www.adafruit.com/product/1413).

## STMicroelectronics LIS3DH

STMicroelectronics' [LIS3DH accelerometer](https://www.st.com/en/mems-and-sensors/lis3dh.html) is an inexpensive accelerometer with a variable range of sensitivity. It connects to a microcontroller using I2C. It's a great one to use when budget is a consideration. It also has some nice features like tap detection on all three axes.

## Freescale MMA8451

Freescale's MMA8451 is an inexpensive accelerometer that communicates over I2C. Adafruit has an [MMA8451 breakout board](https://www.adafruit.com/product/2019)