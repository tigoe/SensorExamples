# Spectral Sensors

A group of multi-channel light sensors. 

## AS7262/3 6-Channel Sensors

These two 6-channel spectral sensors from AMS have more or less the same interface, but differing ranges of sensitivity. The AS7262 reads in the visual range from 450nm (violet) to 650nm (red), and the AS7263 reads from 610nm (red) to 860nm (infrared).

#### Breakout boards:
* Sparkfun [AS7262 board](https://www.sparkfun.com/products/14347)
* Sparkfun [AS7263 board](https://www.sparkfun.com/products/14351)
* Adafruit [AS7262 board](https://www.adafruit.com/product/3779)

#### Libraries:
* [Adafruit AS726x](https://github.com/adafruit/Adafruit_AS726x)
* [Sparkfun AS726x](https://github.com/sparkfun/SparkFun_AS726x_Arduino_Library)

Sparkfun's [Hookup Guide to both sensors](https://learn.sparkfun.com/tutorials/as726x-nirvi) is a good summary of the sensor's capabilities and their library functions. Adafruit's [guide to the AS7272](https://learn.adafruit.com/adafruit-as7262-6-channel-visible-light-sensor?view=all) is not bad either. 

### AS7262 Consumer Grade Smart 6-Channel VIS Sensor

* [Product Page](https://ams.com/as7262)
* [Datasheet](https://ams.com/documents/20143/36005/AS7262_DS000486_2-00.pdf)

#### Channels:
* Channel V: 450nm (violet)
* Channel B: 500nm (blue)
* Channel G: 550nm (green)
* Channel Y: 570nm (yellow)
* Channel O: 600nm (orange)
* Channel R: 650nm (red)

### AS7263 6-Channel NIR Spectral_ID Sensor

* [Product Page](https://ams.com/as7263)
* [Datasheet](https://ams.com/documents/20143/36005/AS7263_DS000476_1-00.pdf)

#### Channels: 
* Channel R: 610nm (red)
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
* Channel R: 610nm (red)
* Channel S: 680nm (red)
* Channel T: 730nm (red)
* Channel U: 760nm (red)
* Channel V: 810nm (infrared)
* Channel W: 860nm (infrared)

AS75652:
* Channel G: 560nm (green) 
* Channel H: 585nm (yellow-green)
* Channel I: 645nm (red)
* Channel J: 705nm (red)
* Channel K: 900nm (infrared)
* Channel L: 940nm (infrared)

AS72653: 
* Channel A: 395nm (violet)
* Channel B: 435nm (deep blue)
* Channel C: 460nm (blue)
* Channel D: 485nm (teal)
* Channel E: 510nm (blue-green)
* Channel F: 535nm (green)

#### Breakout boards:
* [Sparkfun](https://www.sparkfun.com/products/15050)

#### Libraries:
* [Sparkfun](https://github.com/sparkfun/SparkFun_AS7265x_Arduino_Library)

### AS7341 11-Channel Multi-Spectral Digital Sensor

* [Product page](https://ams.com/as7341)
* [Datasheet](https://ams.com/documents/20143/36005/AS7341_DS000504_3-00.pdf)

#### Channels:

* F1: 415nm (violet)
* F2: 445nm (blue)
* F3: 480nm (light blue)
* F4: 515nm (green)
* F5: 555nm (yellow green)
* F6: 590nm (yellow)
* F7: 630nm (orange)
* F8: 680nm (red)
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


## Background reading:
* A quick introduction to [Melanopic Equivalent Daylight Illuminace (EDI)](https://biosinstitute.org/melanopic-equivalent-daylight-illuminance/)
* [CIE Position Statement on Non-Visual Effects of Light](http://cie.co.at/files/CIE%20Position%20Statement%20-%20Proper%20Light%20at%20the%20Proper%20Time%20(2019)_0.pdf) 
* [User Guide to the &alpha;-opic Toolbox
for implementing CIE S 026](http://files.cie.co.at/CIE%20S%20026%20alpha-opic%20Toolbox%20User%20Guide.pdf)
* [Userguide to the Equivalent Daylight (D65) 
Illuminance Toolbox](https://www.nsvv.nl/wp-content/uploads/2019/03/CIE-S-026-EDI-Toolbox-Userguide-vE1.05x.pdf)
* White paper from AMS: [Chip-scale spectral sensing:
understanding the new uses
for ultra-precise light-source
measurement ](https://ams.com/documents/20143/215005/ams_WhitePaper_Chip-scale_spectral_sensing_022021.pdf)