# Arduino UNO LoRa

ต้องกำหนดขาเชื่อมต่อ `LoRa` เข้ากับ `Arduino` ตามตารางนี้

## Wiring
| Semtech SX1276/77/78/79 | Arduino |
| :---------------------: | :------:|
| VCC | 3.3V |
| GND | GND |
| SCK | SCK |
| MISO | MISO |
| MOSI | MOSI |
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
- ??????????????????????????????????????????????? ????????????????????????????????
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
Returns the frequency error of the received packet in Hz. The frequency error is the frequency offset between the receiver centre frequency and that of an incoming LoRa signal.

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
Put the radio in idle (standby) mode.
```
LoRa.idle();
```

### Sleep mode
Put the radio in sleep mode.
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
Change the frequency of the radio.
```
LoRa.setFrequency(frequency);
```
   - `frequency` - frequency in Hz (433E6, 866E6, 915E6)
   
### Spreading Factor
Change the spreading factor of the radio.
```
LoRa.setSpreadingFactor(spreadingFactor);
```
   - `spreadingFactor` - spreading factor, defaults to `7`
Supported values are between `6` and `12`. If a spreading factor of `6` is set, implicit header mode must be used to transmit and receive packets.

### Signal Bandwidth
Change the signal bandwidth of the radio.
```
LoRa.setSignalBandwidth(signalBandwidth);
```
   - `signalBandwidth` - signal bandwidth in Hz, defaults to `125E3`.
Supported values are `7.8E3`, `10.4E3`, `15.6E3`, `20.8E3`, `31.25E3`, `41.7E3`, `62.5E3`, `125E3`, and `250E3`.

### Coding Rate
Change the coding rate of the radio.
```
LoRa.setCodingRate4(codingRateDenominator);
```
   - `codingRateDenominator` - denominator of the coding rate, defaults to `5`
Supported values are between `5` and `8`, these correspond to coding rates of `4/5` and `4/8`. The coding rate numerator is fixed at `4`.

### Preamble Length
Change the preamble length of the radio.
```
LoRa.setPreambleLength(preambleLength);
```
   - `preambleLength` - preamble length in symbols, defaults to `8`
Supported values are between `6` and `65535`.

### Sync Word
Change the sync word of the radio.
```
LoRa.setSyncWord(syncWord);
```
   - `syncWord` - byte value to use as the sync word, defaults to `0x12`
   
### CRC
Enable or disable CRC usage, by default a CRC is not used.
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
