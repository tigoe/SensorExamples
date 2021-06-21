# Light Sensors

This page covers a variety of light sensors, most of which are either single-channel or three- or four-channel sensors (RGB or RGBC). There are also a few specialty sensors, like the MAX30105 sensor which can be used for pulse oximetry or the APDS-9960 sensor which can measure RGB as well as sensing gesture and proximity. There is a separate page for [multi-channel spectral sensors](spectral-sensors). 

## Luminosity Sensors 
TSL2591 - Light levels, visible & IR
* [Adafruit breakout board](https://www.adafruit.com/product/1980)
* [Adafruit library](https://github.com/adafruit/Adafruit_TSL2591_Library)
* [Datasheet](https://github.com/adafruit/Adafruit_TSL2591_Library)


## RGB Sensors
ISL29125 - RGB with IR blocking filter
* [Sparkfun breakout board](https://www.sparkfun.com/products/12829)
* [Sparkfun library](https://github.com/sparkfun/SparkFun_ISL29125_Breakout_Arduino_Library)
* [Datasheet](https://www.renesas.com/us/en/www/doc/datasheet/isl29125.pdf)

## RGBC Sensors
TCS34725 - 4-channel, red, green, blue, clear
* [Adafruit breakout board](https://www.adafruit.com/product/1334)
* [Adafruit library](https://github.com/adafruit/Adafruit_TCS34725)
* [Datasheet](https://ams.com/documents/20143/36005/TCS3472_DS000390_2-00.pdf/6e452176-2407-faaf-a590-d526c78c7432)


APDS9960 - RGB and gesture
* [Sparkfun breakout board](https://www.sparkfun.com/products/12787)
* [Sparkfun Library](https://github.com/sparkfun/SparkFun_APDS-9960_Sensor_Arduino_Library/tree/V_1.4.2)
[Adafruit breakout board](https://www.adafruit.com/product/3595)
* [Adafruit Library](https://github.com/adafruit/Adafruit_APDS9960)
* [Arduino BLE Sense](https://store.arduino.cc/usa/nano-33-ble-sense)
* [Arduino Library](https://www.arduino.cc/en/Reference/ArduinoAPDS9960)
* [Datasheet](https://docs.broadcom.com/docs/AV02-4191EN)

## Specialty Sensors

MAX30105 - red, IR, green, for pulse oximetry and particle detection
* [Sparkfun breakout board](https://www.sparkfun.com/products/14045)
* [Sparkfun library](https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library)
* [Datasheet](https://datasheets.maximintegrated.com/en/ds/MAX30105.pdf)
* Being replaced by [MAX30101](https://datasheets.maximintegrated.com/en/ds/MAX30101.pdf)


## Discontinued Sensors

GA1AS202L - ambient light
* [Adafruit breakout board](https://www.adafruit.com/product/1384)
* [Datasheet](https://www.digchip.com/datasheets/download_datasheet.php?id=3860632&part-number=GA1A1S202WP)

APDS9301 - ambient light sensor
* [Sparkfun breakout board](https://www.sparkfun.com/products/retired/14350) part is retired
* [Sparkfun library](https://www.sparkfun.com/products/retired/14350) part is retired
[Datasheet](https://cdn.sparkfun.com/assets/3/2/c/0/8/AV02-2315EN0.pdf)

## Background Reading

* Rune Madsen's [Programming Design Systems](https://programmingdesignsystems.com/) book is a great intro to visual design and programming and his chapters on color are a helpful intro to color theory for understanding sensors and LED color mixing: 
   * [A Short History of Color Theory](https://programmingdesignsystems.com/color/a-short-history-of-color-theory/index.html#a-short-history-of-color-theory-xZzRFOZ)
   * [Color Models and Color Spaces](https://programmingdesignsystems.com/color/color-models-and-color-spaces/index.html#color-models-and-color-spaces-JDQ1fRD)
* A pretty good [introduction to colorimetry](https://medium.com/hipster-color-science/a-beginners-guide-to-colorimetry-401f1830b65a)
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
* AMS Application Note: [DN40-Rev 1.0 – Lux and CCT Calculations using ams Color Sensors](https://ams.com/documents/20143/80162/ColorSensors_AN000166_1-00.pdf/c0b4a4b4-9948-f2a7-f8a1-36a8208bd0a9) 
* [Accurate method for computing correlated color temperature](https://www.osapublishing.org/DirectPDFAccess/271508BC-9A43-6E9C-75B4043231D56AE2_344803/oe-24-13-14066.pdf?da=1&id=344803&seq=0&mobile=no)
* [Correlated Color Temperature Determination for LED Modules Using a Digital Color Sensor](https://www.scientificbulletin.upb.ro/rev_docs_arhiva/full3fa_651029.pdf)
* [Calculate CIE 1931 xy coordinates from color temperature](https://www.waveformlighting.com/tech/calculate-cie-1931-xy-coordinates-from-cct/)
* An interesting [discussion on the CCT calculation in the Adafruit TCS34725 library](https://github.com/adafruit/Adafruit_TCS34725/issues/21)