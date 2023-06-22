## Hardware Connection

The PMS5003 sensor sends its data over an asynchronous serial connection (UART). You'll need to read the data over a UART interface on your microcontroller and interpret the bytes.

Many Arduino boards (though not the Uno) have two UARTs. The first is the USB-Serial connection that you use to upload new code and to send information to the Serial port using `Serial.println()` and other serial commands. The second UART on the Nano 33 IoT is on digital pins 0 and 1 (physical pins 16 and 16, on the bottom right of the board). On the MKR boards it's on digital pins 13 and 14 (physical pins 22 and 23, on the right side of the board). The second UART on any Arduino or compatible board is addressed as `Serial1` in code, like so:
```
Serial1.begin(9600);
Serial1.println("Hello");
```
 To connect to any UART-based device, the tramsmit pin (TX) of the sensor connects to the receive (RX) pin of the microcontroller, and vice versa. Voltage and ground for the sensor connect to voltage and ground from the microcontroller, respectively.

## Sensor Data Format

The sensor's [data sheet](https://www.aqmd.gov/docs/default-source/aq-spec/resources-page/plantower-pms5003-manual_v2-3.pdf) explains that the default serial data format is a 32-byte sentence, as follows:

| Byte No. | Meaning | Value |
|---|---|---|
| 1 |Header Byte | 0x42 |
| 2 |Header Byte | 0x4D |
| 3 |Frame Length High Byte | variable |
| 4 |Frame Length Low Byte | variable |
| 5 |Data 1 High Byte | variable |
| 6 |Data 1 Low Byte | variable |
| 7-28 |Data 2-12 high and low bytes | variable |
| 29-30 |reserved | variable |
| 31 |Checksum High Byte | variable |
| 32 |Checksum Low Byte | variable |


> **Note:** in programming contexts, single-byte values are often written in base-16, or *hexadecimal* notation. In this notation, each digit has 16 possible values, 0-9 then A-F. The `0x` at the beginning indicates that a number is hexadecimal. It makes it easy to write each byte as a two-digit figure: 0-255 in decimal notation is 0-FF in hexadcimal. These notes will follow that convention.

## Reading the Serial Data

The data from the sensor will
be sent over and over again via the UART. So the first thing you need to do is to look for the first byte, whose value in hexadecimal notation is `0x42`. 

You can do look for the first header byte like so:

````arduino
void setup() {
  // Initialize both the USB serial port and sensor serial port:
  Serial.begin(9600);
  Serial1.begin(9600);
}
void loop() {
  // if there's incoming serial data from the sensor:
  if (Serial1.available()) {
    // read one byte:
    byte input = Serial1.read();
    // if that byte is the first header byte,
    // print a newline so you can see once sentence per line:
    if (input == 0x42) {
      Serial.println();
    }
    // print the byte no matter what it is:
    Serial.print(input, HEX);
    // print a space after each byte:
    Serial.print(" ");
  }
}
````

You should see output in the Serial Monitor like this:
```
42 4D 0 1C 0 1 0 3 0 3 0 1 0 3 0 3 1 59 0 64 0 12 0 4 0 0 0 0 97 0 2 24 
```
You can see the two header bytes, followed by 15 pairs of bytes. The bytes represent the values as explained in the data format above. To understand them, start with the first two after the header, the data length. They are `0 1C`. You can combine them into a single byte by multiplying the first byte by 256 and adding it to the second byte (this math is explained in more detail below). Since the first byte is 0, you just need the second byte, `0x1C`, which is 28 in decimal notation.  That means the data length is 28 bytes. Sure enough, 28 bytes follow the data length. So far, so good. 

### Calculating the Checksum

The last two bytes of the data sentence are the checksum. A *checksum* is a summary of a data sentence, that you can use to validate the data. To use it, add up all the bytes before the checksum. If their sum matches the value of the checksum, your data is valid. 

Looking at the sentence above, here's the sum of all the bytes before the checksum (keep in mind, they're shown in hexadecimal values here):

```
42 + 4D + 0 + 1C + 0 + 1 + 0 + 3 + 0 + 3 + 0 + 1 + 0 + 3 + 0 + 3 + 1 + 59 + 0 + 64 + 0 + 12 + 0 + 4 + 0 + 0 + 0 + 0 + 97 + 0 = 0x224
```
Sure enough, that matches the value of the last two bytes, 0x224, or 548 in decimal notation. So you know the data is valid. 

## Reading the Header

Since the sensor data is continually repeated, you need to look for the header to know when you're at the beginning of each set of readings. The Arduino Serial API offers a few ways to do this: 
* [`Serial.find()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/find/) looks for a string of text, 
* [`Serial.findUntil()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/finduntil/) looks for a string, but terminates if it hits a single-byte terminator, 
* [`Serial.readBytes()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/readbytes/) reads the whole serial buffer into an array,
* [`Serial.readBytesUntil()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/readbytesuntil/) reads the serial buffer into an array until it reaches a given character. 

After you find the header, you need to wait for the rest of the bytes, however, so the `Serial.readBytesUntil()` function is the best one in this case. It lets you combine finding the header with storing the rest in an array. The [buffer_read_test example]({{site.codeurl}}/EnvironmentalSensors/PMS3005_AQI_sensor/buffer_read_test/buffer_read_test.ino) shows how to do this. It looks for the first header byte, 0x42, and stores bytes in a 32-byte array called `buffer` until it finds that byte. The key function is `Serial1.readBytesUntil()`, used like so:

```arduino
 // read into the buffer until you hit 0x42:
  int result = Serial1.readBytesUntil(0x42, buffer, 32);
```
The variable `result` tells you how many bytes you got, so you can use it to make sure you got all the bytes, like so:
```arduino
// if you got no data, skip the rest of the loop:
  if (result <= 0) return;
```

### What If One of the Data Bytes Matches the Header Byte Values?

It's possible that one of the data bytes could be 0x42, so it's good to check for both header bytes. It will be the first byte in the buffer array after you use `Serial1.readBytesUntil()`. You check like so:

```arduino
  // if you didn't get the second header byte, skip the rest of the loop:
  if (buffer[0] != 0x4D) return;
``` 

## Combining Bytes Into Larger Values

All of the data bytes represent 2-byte values. You need to combine each pair of bytes into a single value.

To combine individual bytes into larger values, it helps to imagine those bytes and values as bits in memory. A single byte variable has 8 bits, and a two-byte variable has 16 bits. When you put any value into a variable, it's put in from the low bit first. If you want to move that value to a different starting position, you multiply by 2 (remember, binary notation is base-20 OR use the shift operators `<<` and `>>`.

For example, here's the decimal value 232 in a `byte` variable:
```
11101000
``` 
And here's the decimal value 3 in a `byte` variable:
```
00000111
``` 
Now imagine these two bytes together in a larger variable, perhaps an `int` variable: 
```
00000011 11101000
```
That's 3 in the high byte and 232 in the low byte. What is it as a single value? Each byte has 256 possible values, so to find out, multiply the high byte by 256 and add it to the low byte:
```
(3 * 256) + 232 = 1000
```
Whenever you need to combine two bytes into a single value, you can use this formula:
```
data value = (highbyte * 256) + lowByte
```
In your program, you can also use the shift operators, `<<` and `>>` to move bits in a byte. For example, imagine the value 3 in an int variable:
```
00000000 00000111
```
Now shift it by 8 bits to the left:
```
00000111 00000000
```
That's 3 * 256 or 768. When you want to combine that with a lower byte value, just add the lower byte on:
3 * 256 + 232:
```
00000011 11101000
```
That's 1000. 

You'll need this operation for combining the two-byte data pairs in this sensor's data sentence. 

> **Note:** Arduino variable sizes depend on the processor your code is running on. See the reference for more on this