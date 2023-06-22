## Hardware Connection

The PMS5003 sensor sends its data over an asynchronous serial connection (UART). You'll need to read this and interpret the bytes.

Many Arduino boards (though not the Uno) have two UARTs. The first is the USB-Serial connection that you use to upload new code and to send information to the Serial port using `Serial.println()` and other serial commands. The second UART on the Nano 33 IoT is on digital pins 0 and 1 (physical pins 16 and 16, on the bottom right of the board). On the MKR boards it's pn digital pins 13 and 14 (physical pins 22 and 23, on the right side of the board). The second UART on any Arduino or compatible board is addressed as `Serial1` in code, like so:
```
Serial1.begin(9600);
Serial1.println("Hello");
```
 To connect to any UART-based device, the tramsmit pin (TX) of the sensor connects to the receive (RX) pin of the microcontroller, and vice versa. Voltage and ground for the sensor connect to voltage and ground from the microcontroller.


## Sensor Data Format

The sensor's data sheet explains that the default serial data format is a 32-byte sentence, as follows:

| Byte No. | Meaning | Value |
|---|---|---|
| 1 |Header Byte | 0x42 |
| 2 |Header Byte | 0x4D |
| 3 |Frame Length High Byte | variable |
| 4 |Frame Length Low Byte | variable |
| 5 |Data 1 High Byte | variable |
| 6 |Data 1 Low Byte | variable |
| 7-28 |Data 2-12 bytes | variable |
| 29-30 |reserved | variable |
| 31 |Checksum High Byte | variable |
| 32 |Checksum Low Byte | variable |

All of the data bytes represent 2-byte values. You need to combine each pair of bytes into a single value. 

## Combining Bytes Into larger Values

To combine individual bytes into larger values, it helps to imagine those bytes and values as bits in memory. A single byte variable has 8 bits, and a two-byte variable has 16 bits. When you put any value into a variable, it's put in from the low bit first. So if you want to move it, you use the shift operators. For example, here's the decimal value 232 in a byte:
```
11101000
``` 
And here's the decimal value 3:
```
00000111
``` 
Now imagine these two bytes together: 
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
In your program, you can also use the shift operators, `<<` and `>>` to move bits in a byte. For example, take the value 3:
```
00000111
```
Now shift it by 8 bits to the left:
```
00000111 00000000
```
That's 3 * 256 or 768. If you want to combine that with a lower byte value, just add the lower byte on:
3 * 256 + 232 =
```
00000011 11101000
```
That's 1000. 

You'll need this operation for combining the two-byte data pairs in this sensor's data sentence. 

## Reading the Serial Data

The data from the sensor will
be sent over and over again via the UART. So the first thing you need to do is to look for the first byte, whose value in hexadecimal notation is `0x42`. You can do it like so:

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
    // print a space:
    Serial.print(" ");
  }
}
````

You should see output in the Serial Monitor like this:
```
42 4D 0 1C 0 1 0 3 0 3 0 1 0 3 0 3 1 59 0 64 0 12 0 4 0 0 0 0 97 0 2 24 
```
You can see the two header bytes, followed by 15 pairs of bytes. The bytes represent the values as explained in the data format above. To understand them, start with the first two after the header, the data length. They are `0 1C`. Converting that as explained above:
```
(0 * 256) +  28
```
That means the data length is 28 bytes. Sure enough, 28 bytes follow the data length. So far, so good. 

### Calculating the Checksum

The last two bytes of the data sentence are the checksum. A *checksum* is a summary of a data sentence, that you can use to validate the data. To use it, add up all the bytes before the checksum. If their sum matches the value of the checksum, your data is valid. 

Looking at the sentence above, here's the sum of all the bytes before the checksum (keep in mind, they're shown in hexadecimal values here):

```
42 + 4D + 0 + 1C + 0 + 1 + 0 + 3 + 0 + 3 + 0 + 1 + 0 + 3 + 0 + 3 + 1 + 59 + 0 + 64 + 0 + 12 + 0 + 4 + 0 + 0 + 0 + 0 + 97 + 0 = 0x224
```
Sure enough, that matches the value of the last two bytes, 0x224, or 548 in decimal terms. So you know the data is valid. 

### What If One of the Data Bytes matches the Header Byte Values?

It's possible that one of the data bytes could be 0x42, so it's good to check for both header bytes.  The Arduino Serial API offers a few ways to do this: [`Serial.find()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/find/), [`Serial.findUntil()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/finduntil/), [`Serial.readBytes()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/readbytes/), and [`Serial.readBytesUntil()`](https://www.arduino.cc/reference/en/language/functions/communication/serial/readbytesuntil/). After you find the header, you need to wait for the rest of the bytes, however. You can combine these steps using the `Serial.readBytesUntil()` function, which lets you read bytes into a buffer until you get a given byte.   The [buffer_read_test example]({{site.codeurl/EnvironmentalSensors/buffer_read_test/buffer_read_test.ino}}) shows how to do this. 





