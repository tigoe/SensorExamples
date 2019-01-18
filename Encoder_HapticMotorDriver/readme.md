# Haptic Motor Driver with Encoder

This sketch shows how to use an effect from the effects library
of the [TI DRV2605 Haptic Motor Driver](https://cdn-shop.adafruit.com/datasheets/DRV2605.pdf). Each time the encoder changes, the haptic motor effect runs.  

The [Sparkfun breakout board for the motor driver](https://www.sparkfun.com/products/14538) or the [Adafruit motor driver board](https://www.adafruit.com/product/2305) will both work for this. 
(https://cdn-shop.adafruit.com/datasheets/DRV2605.pdf).

Uses Adafruit's [DRV2605 library](https://github.com/adafruit/Adafruit_DRV2605_Library), and Paul Stoffregen's [Encoder library](https://www.pjrc.com/teensy/td_libs_Encoder.html).

## The Patterns

Page 55-56 of the [DRV2605 datasheet](https://cdn-shop.adafruit.com/datasheets/DRV2605.pdf) covers the different haptic patterns the motor can do. To change the pattern in this code, change the pattern number in lines 28-29 of the code, from 47 (Buzz 1 – 100%) to whatever pattern you prefer.

## The Circuit

The motor driver is connected to the Vcc and ground pins of the microcontroller, and the I2C pins. The SCL pin of the driver connects to the SCL pin of the microcontroller (Top right side pin on the Uno format; 9th pin from top right on the MKR format); likewise, the SDA pin of the driver connects to the SDA pin of the microcontroller(second from top right side pin on the Uno format; 10th pin from top right on the MKR format). The pin numbers for each version of the board are in Table 1 below. These pin numbers assume you're holding the breakout board with the pins facing to the left. The two motor pins are on the right side of the board.

<table>
    <tr>
        <th>Pin Function</th>
        <th>Sparkfun Pin No.</th>
        <th>Adafruit Pin No.</th>
    </tr>
    <tr>
        <td>Vin</td>
        <td>2</td>
        <td>1</td>
    </tr>
     <tr>
        <td>Ground</td>
        <td>1</td>
        <td>2</td>
    </tr>
    <tr>
        <td>SCL</td>
        <td>3</td>
        <td>3</td>
    </tr>
        <tr>
        <td>SDA</td>
        <td>4</td>
        <td>4</td>
    </tr>
    <tr>
        <td>In</td>
        <td>5</td>
        <td>5</td>
    </tr>
     <tr>
        <td>Enable</td>
        <td>6</td>
        <td>No pin</td>
    </tr>
</table>


