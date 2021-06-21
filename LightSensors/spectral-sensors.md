# Spectral Sensors

A group of multi-channel light sensors. The ones covered as of this writing are all from [AMS-Osram](https://ams.com), who make a wide range of light-based sensors. Their spectral sensing family of sensors includes sensors for tristimulus XYZ color sensing as well as multi-channel spectral sensors in both visible and near-infrared ranges. This page covers the AS7262/3 6-channel spectral sensors, the AS7265x sensors, which provide 18 channels together, and the AS7341 sensor, which provides 11 channels of spectral sensing.

Of the lot, the AS7265x and the AS7341 seem to offer the most value for money, in terms of general use. The former supports 18 channels of sensing, and the latter 11. The AS7262/3 are limited to six channels each, and the AS7262 is no longer recommended for use by AMS. The AS7261 looks interesting as well, as it is designed to give results in the CIE XY colorspace.

## What do the Readings Mean?

The AS726xx sensors' results are all returned in counts/&mu;W/cm<sup>2</sup>. One lux = 0.14641 &mu;W/cm<sup>2</sup>. Therefore, one count on any of these sensors is 6.8301 lx in illuminance terms. (**check my math please**). Here is a [Units converter](https://www.unitsconverters.com/en/W/Cm2-To-Lx/Utu-3547-3537) for common physical properties that I used for this math.

**TODO:** work out similar results for AS7341. 

## AS7262/3 6-Channel Sensors
These two 6-channel spectral sensors from AMS have more or less the same interface, but differing ranges of sensitivity. The AS7262 reads in the visual range from 450nm (violet) to 650nm (red), and the AS7263 reads from 610nm (red) to 860nm (infrared). These sensors have both an I2C and a UART interface. Sparkfun's [Hookup Guide to both sensors](https://learn.sparkfun.com/tutorials/as726x-nirvi) is a good summary of the sensor's capabilities and their library functions. Adafruit's [guide to the AS7272](https://learn.adafruit.com/adafruit-as7262-6-channel-visible-light-sensor?view=all) is not bad either. 

#### Breakout boards:
* Sparkfun [AS7262 board](https://www.sparkfun.com/products/14347)
* Sparkfun [AS7263 board](https://www.sparkfun.com/products/14351)
* Adafruit [AS7262 board](https://www.adafruit.com/product/3779)

#### Libraries:
* [Adafruit AS726x](https://github.com/adafruit/Adafruit_AS726x)
* [Sparkfun AS726x](https://github.com/sparkfun/SparkFun_AS726x_Arduino_Library)

### AS7262 Consumer Grade Smart 6-Channel VIS Sensor

Current status on AMS' site: not recommended for new designs.

* [Product Page](https://ams.com/as7262)
* [Datasheet](https://ams.com/documents/20143/36005/AS7262_DS000486_2-00.pdf)

(colors shown are approximate, and taken from John Cook's [Wavelength to RGB Converter](https://www.johndcook.com/wavelength_to_RGB.html))
#### Channels:
* Channel V: 450nm <span style="color:white; background-color:#0046ff;">(violet)</span>
* Channel B: 500nm <span style="color:white; background-color:#00ff92;">(blue)</span>
* Channel G: 550nm <span style="color:white; background-color:#a3ff00;">(green)</span>
* Channel Y: 570nm <span style="color:white; background-color:#e1ff00;">(yellow)</span>
* Channel O: 600nm <span style="color:white; background-color:#ffbe00;">(orange)</span>
* Channel R: 650nm <span style="color:white; background-color:#ff0000;">(red)</span>

### AS7263 6-Channel NIR Spectral_ID Sensor

* [Product Page](https://ams.com/as7263)
* [Datasheet](https://ams.com/documents/20143/36005/AS7263_DS000476_1-00.pdf)

#### Channels: 
* Channel R: 610nm <span style="color:white; background-color:#ff9b00;">(red)</span>
* Channel S: 680nm (infrared)
* Channel T: 730nm (infrared)
* Channel U: 760nm (infrared)
* Channel V: 810nm (infrared)
* Channel W: 860nm (infrared)

## AS7265x 18-Channel VIS to NIR Spectral_ID 3-Sensor Chipset

This is a set of three 6-channel spectral sensors from AMS, covering a range from violet to infrared. Used together, as in the Sparkfun board, they cover a range of frequencies greater than the 726x sensors.

* [Product Page](https://ams.com/as7265x)
* [Datasheet](https://ams.com/documents/20143/36005/AS7265x_DS000612_1-00.pdf)
* [Quickstart Guide](https://ams.com/documents/20143/36005/AS7265x_QG000122_1-00.pdf)

#### Channels:

AS72651:
* Channel R: 610nm <span style="color:white; background-color:#ff9b00;">(red)</span>
* Channel S: 680nm <span style="color:white; background-color:#ff0000;">(red)</span>
* Channel T: 730nm <span style="color:white; background-color:#c80000;">(red)</span>
* Channel U: 760nm <span style="color:white; background-color:#8d0000;">(red)</span>
* Channel V: 810nm (infrared)
* Channel W: 860nm (infrared)

AS75652:
* Channel G: 560nm <span style="color:white; background-color:#c3ff00;">(green)</span>
* Channel H: 585nm <span style="color:white; background-color:#ffef00;">(yellow-green)</span>
* Channel I: 645nm <span style="color:white; background-color:#ff0000;">(red)</span>
* Channel J: 705nm <span style="color:white; background-color:#f60000;">(red)</span>
* Channel K: 900nm (infrared)
* Channel L: 940nm (infrared)

AS72653: 
* Channel A: 395nm <span style="color:white; background-color:#8000a1;">(violet)</span>
* Channel B: 435nm <span style="color:white; background-color:#2300ff;">(deep blue)</span>
* Channel C: 460nm <span style="color:white; background-color:#007bff;">(blue)</span>
* Channel D: 485nm <span style="color:white; background-color:#00eaff;">(teal)</span>
* Channel E: 510nm <span style="color:white; background-color:#00ff00;">(blue-green)</span>
* Channel F: 535nm <span style="color:white; background-color:#70ff00;">(green)</span>

#### Breakout boards:
* [Sparkfun](https://www.sparkfun.com/products/15050)

#### Libraries:
* [Sparkfun](https://github.com/sparkfun/SparkFun_AS7265x_Arduino_Library)

### AS7341 11-Channel Multi-Spectral Digital Sensor

* [Product page](https://ams.com/as7341)
* [Datasheet](https://ams.com/documents/20143/36005/AS7341_DS000504_3-00.pdf)
* Diffuser in tests, according to the datasheet: [ED1-C50](https://www.thorlabs.com/thorproduct.cfm?partnumber=ED1-C50)
* LEDs used in tests: 420nm (blue), 940nm (IR), 2700K warm white 

#### Channels:

* F1: 415nm <span style="color:white; background-color:#7600ed;">(violet)</span>
* F2: 445nm <span style="color:white; background-color:#0028ff;">(blue)</span>
* F3: 480nm <span style="color:white; background-color:#00d5ff;">(light blue)</span>
* F4: 515nm <span style="color:white; background-color:#1fff00;">(green)</span>
* F5: 555nm <span style="color:white; background-color:#b3ff00;">(yellow green)</span>
* F6: 590nm <span style="color:white; background-color:#ffdf00;">(yellow)</span>
* F7: 630nm <span style="color:white; background-color:#ff4f00;">(orange)</span>
* F8: 680nm <span style="color:white; background-color:#ff0000;">(red)</span>
* NIR: 910nm (near IR)
* Clear: non filtered
* FD: (Flicker Detection) non filtered

#### Breakout boards:
* [Sparkfun](https://www.sparkfun.com/products/17719)
* [Adafruit](https://github.com/adafruit/Adafruit_AS7341)
* [DFRobot](https://www.dfrobot.com/product-2132.html)

#### Libraries:
* [Adafruit](https://github.com/adafruit/Adafruit_AS7341)
* [Sparkfun](https://github.com/sparkfun/SparkFun_AS7341X_Arduino_Library)


## Background Reading

See the main [Light Sensors page](/#background-reading)
