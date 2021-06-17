# Spectral Sensors

A group of multi-channel light sensors from AMS. 

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

#### Breakout boards:
* Sparkfun
* Adafruit

#### Libraries:
* [Adafruit](https://github.com/adafruit/Adafruit_AS726x)
* Sparkfun

### AS7263 6-Channel NIR Spectral_ID Sensor

* [Product Page](https://ams.com/as7263)
* [Datasheet](https://ams.com/documents/20143/36005/AS7263_DS000476_1-00.pdf)

#### Channels: 
* Channel R: 610nm
* Channel S: 680nm
* Channel T: 730nm
* Channel U: 760nm
* Channel V: 810nm
* Channel W: 860nm

#### Breakout boards:
* Sparkfun

#### Libraries:
* [Adafruit](https://github.com/adafruit/Adafruit_AS726x)
* Sparkfun

### AS7265x 18-Channel VIS to NIR Spectral_ID 3-Sensor Chipset

* [Product Page](https://ams.com/as7265x)
* [Datasheet](https://ams.com/documents/20143/36005/AS7265x_DS000612_1-00.pdf)
* [Quickstart Guide](https://ams.com/documents/20143/36005/AS7265x_QG000122_1-00.pdf)

#### Channels:

AS72651:
* Channel R: 610nm
* Channel S: 680nm
* Channel T: 730nm
* Channel U: 760nm
* Channel V: 810nm
* Channel W: 860nm

AS75652:
* Channel G: 560nm
* Channel H: 585nm
* Channel I: 645nm
* Channel J: 705nm
* Channel K: 900nm
* Channel L: 940nm

AS72653: 
* Channel A: 395nm
* Channel B: 435nm
* Channel C: 460nm
* Channel D: 485nm
* Channel E: 510nm
* Channel F: 535nm

#### Breakout boards:
* [Sparkfun](https://www.sparkfun.com/products/15050)

#### Libraries:
* [Sparkfun](https://github.com/sparkfun/SparkFun_AS7265x_Arduino_Library)

### AS7341 11-Channel Multi-Spectral Digital Sensor

* [Product page](https://ams.com/as7341)
* [Datasheet](https://ams.com/documents/20143/36005/AS7341_DS000504_3-00.pdf)

#### Channels:

| Channel | Center Wavelength (nm) | Full Width Half Maximum (nm) | 
|---|---|---|
| F1  | 415  | 26 | 
| F2  | 445  | 30 | 
| F3  | 480  | 36 | 
| F4  | 515  | 39 | 
| F5  | 555  | 39 | 
| F6  | 590  | 40 | 
| F7  | 630  | 50 | 
| F8  | 680  | 52 | 
| NIR (Near IR) | 910 | n/a |
| Clear | Si response/non filtered | n/a |
| FD (Flicker Detection) | Si response/non filtered | n/a |

#### Breakout boards:
* [Sparkfun](https://www.sparkfun.com/products/17719)
* [Adafruit](https://github.com/adafruit/Adafruit_AS7341)
* DFRobot

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