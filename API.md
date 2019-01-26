# Arduino UNO LoRa

ต้องกำหนดขาเชื่อมต่อ `LoRa` เข้ากับ `Arduino` ตามตารางนี้

## Wiring
| Semtech SX1276/77/78/79 | Arduino |
| :---------------------: | :------:|
| VCC | 3.3V |
| GND | GND |
| SCK | 13 / SCK |
| MISO | 12 / MISO |
| MOSI | 11 / MOSI |
| NSS | 10 |
| NRESET | 9 |
| DIO0 | 8 |

## Include Library
จะต้อง import library ก่อนใช้งาน
```cpp
#include <SPI.h>
#include <LoRa.h>
```
## Setup
### Begin
```
LoRa.begin(frequency);
```
- เป็นฟังก์ชันที่ใช้กำหนดความถี่ของคลื่นที่จะใช้งาน
    - `frequency` คือ คลื่นความถี่ของที่จะใช้งานมีหน่วยเป็น Hz (`433E6`, `866E6`, `915E6`)
    - สำหรับประเทศไทยให้กำหนดเป็น 433MHz หรือใส่ในโค้ดว่า 433E6

### Set pins
```
LoRa.setPins(ss, reset, dio0);
```
- เป็นฟังก์ชั่นที่ใช้กำหนดขาที่เชื่อมต่ออยู่กับขา `NSS` `NRESET` และ `DIO0` ของโมดูล LoRa มีรายละเอียดของพารามิเตอร์ดังนี้
    - `SS` หมายถึง ขาที่ต่อกับ `NSS` 
    - `RESET` หมายถึง ขาที่ต่อกับ `NRESET` 
    - `DIO0` หมายถึง ขาที่ต่อกับ `DIO0`

## Sending Data
### Begin packet
```
LoRa.beginPacket();

LoRa.beginPacket(implicitHeader);
```
   - เป็นการกำหนดให้เริ่มส่ง packet
   - `implicitHeader` - (optional) `true` จะเปิดใช้ implicit mode, `false` จะไม่เปิด implicit mode (ค่าเริ่มต้น)
Return `1` เมื่อวิทยุพร้อมส่งสัญญาณ, `0` เมื่อวิทยุไม่ว่างหรือเกิดดข้อผิดพลาด

### Printing
```
LoRa.print(data)
```
   - `data` - ข้อมูลที่ต้องการจะให้ส่งออกไป (`String`, `int`,` char`, `byte`, `long`)
   
### End packet
```
LoRa.endPacket();

LoRa.endPacket(async);
```
   - เป็นฟังก์ชันที่ใช้จบการเขียนข้อมูลลงใน packet เพื่อที่จะส่งออกไป
   - `async` - (optional) `true` จะเปิดใช้ non-blocking mode, `false` จะระให้การส่งสัญญาณเสร็จก่อน (ค่าเริ่มต้น)
Return `1` เมื่อสำเร็จ, `0` เมื่อเกิดข้อผิดพลาด

## Recieving data
### Parsing packet
ทำการตรวจสอบว่ามีการรับ packet เข้ามา
```
int packetSize = LoRa.parsePacket();

int packetSize = LoRa.parsePacket(size);
```
   - `size` - (optional) ถ้า `> 0` implicit header mode is enabled with the expected a packet of size bytes, default mode is explicit header mode
Return ขนาดของ packet เป็น bytes หรือ `0` ถ้าไม่มีการรับ packet เช้ามา

### Packet RSSI
```
int rssi = LoRa.packetRssi();
```
Return RSSI ของ packet ที่ได้รับ

### Packet SNR
```
float snr = LoRa.packetSnr();
```
Returns SNR โดยประมาณของ packet ที่ได้รับมา มีหน่วยเป็น dB

### Packet Frequency Error
```
long freqErr = LoRa.packetFrequencyError();
```
   - Frequency error คือ offset ระหว่างความถี่ของตัวรับสัญญาณและความถี่ของสัญญาณที่เข้ามา

Returns frequency error ของ packet ที่ได้รับเป็น Hz

### Available
```
int availableBytes = LoRa.available()
```
Returns number of bytes available for reading.

### Peeking
Peek at the next byte in the packet.
```
byte b = LoRa.peek();
```
Returns the next byte in the packet or -1 if no bytes are available.

### Reading
Read the next byte from the packet.
```
byte b = LoRa.read();
```
Returns the next byte in the packet or -1 if no bytes are available.
**Note:** Other Arduino [`Stream` API's](https://www.arduino.cc/reference/en/language/functions/communication/stream/) can also be used to read data from the packet

## Other radio modes
### Idle mode
ปรับให้ทำงาน idle (standby) mode
```
LoRa.idle();
```

### Sleep mode
ปรับให้เข้าสู่ sleep mode
```
LoRa.sleep();
```

## Radio Paramiters
### Tx Power
```
LoRa.setTxPower(txPower);

LoRa.setTxPower(txPower, outputPin);
```
   - `txPower` - TX power in dB, defaults to 17
   - `outputPin` - (optional) PA output pin, supported values are `PA_OUTPUT_RFO_PIN` and `PA_OUTPUT_PA_BOOST_PIN`, defaults to `PA_OUTPUT_PA_BOOST_PIN`.
Supported values are `2` to `20` for `PA_OUTPUT_PA_BOOST_PIN`, and `0` to `14` for `PA_OUTPUT_RFO_PIN`.

Most modules have the PA output pin connected to PA BOOST,

### Frequency
ตั้งค่าคลื่นความถี่ของโมดูล
```
LoRa.setFrequency(frequency);
```
   - `frequency` - คลื่นความถี่เป็น Hz (`433E6`, `866E6`, `915E6`)
   
### Spreading Factor
ตั้งค่า spreading factor ของโมดูล
```
LoRa.setSpreadingFactor(spreadingFactor);
```
   - `spreadingFactor` - spreading factor, ค่าเริ่มต้นคือ `7`
สามารถตั้งค่าได้ระหว่าง `6` ถึง `12` ถ้า spreading factor คือ `6` implicit header mode จะถูกใช้ในการรับส่ง packets

### Signal Bandwidth
ตั้งค่า bandwidth ของโมดูล
```
LoRa.setSignalBandwidth(signalBandwidth);
```
   - `signalBandwidth` - signal bandwidth เป็น Hz, ค่าเริ่มต้นคือ `125E3`.
ค่าที่สามารถตั้งได้ คือ `7.8E3`, `10.4E3`, `15.6E3`, `20.8E3`, `31.25E3`, `41.7E3`, `62.5E3`, `125E3`, และ `250E3`

### Coding Rate
ตั้งค่า coding rate ของโมดูล
```
LoRa.setCodingRate4(codingRateDenominator);
```
   - `codingRateDenominator` - ตัวส่วนของ coding rate, ค่าเริ่มต้นคือ `5`
สามารถตั้งค่าได้ระหว่าง `5` ถึง `8` ตัวอย่างเช่น `4/5` และ `4/8` ตัวเศษของ coding rate จะมีค่าเป็น `4` เสมอ

### Preamble Length
ตั้งค่าความยาว preamble ของโมดูล
```
LoRa.setPreambleLength(preambleLength);
```
   - `preambleLength` - ความยาวของ preamble, ค่าเริ่มต้นคือ `8`
สามารถตั้งค่าได้ตั้งแต่ `6` ถึง `65535`.

### Sync Word
Change the sync word of the radio.
```
LoRa.setSyncWord(syncWord);
```
   - `syncWord` - byte value to use as the sync word, defaults to `0x12`
   
### CRC
เปิดหรือปิด CRC โดยค่าเริ่มต้น CRC จะปิดอยู่
```
LoRa.enableCrc();

LoRa.disableCrc();
```
### Invert IQ Signals
Enable or disable Invert the LoRa I and Q signals, by default a invertIQ is not used.
```
LoRa.enableInvertIQ();

LoRa.disableInvertIQ();
```
## Other functions
### Random
Generate a random byte, based on the Wideband RSSI measurement.
```
byte b = LoRa.random();
```
Returns random byte.
