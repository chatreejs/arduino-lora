# Arduino LoRa

[![Build Status](https://travis-ci.org/sandeepmistry/arduino-LoRa.svg?branch=master)](https://travis-ci.org/sandeepmistry/arduino-LoRa)

[Arduino](https://arduino.cc/) library สำหรับการรับและการส่งข้อมูลโดยใช้คลื่นสัญญาณ [LoRa](https://www.lora-alliance.org/)

## Compatible Hardware

 * [Semtech SX1276/77/78/79](http://www.semtech.com/apps/product.php?pn=SX1276) based boards including:
   * [Dragino Lora Shield](http://www.dragino.com/products/module/item/102-lora-shield.html)
   * [HopeRF](http://www.hoperf.com/rf_transceiver/lora/) [RFM95W](http://www.hoperf.com/rf_transceiver/lora/RFM95W.html), [RFM96W](http://www.hoperf.com/rf_transceiver/lora/RFM96W.html), and [RFM98W](http://www.hoperf.com/rf_transceiver/lora/RFM98W.html)
   * [Modtronix](http://modtronix.com/) [inAir4](http://modtronix.com/inair4.html), [inAir9](http://modtronix.com/inair9.html), and [inAir9B](http://modtronix.com/inair9b.html)
 * [Arduino MKR WAN 1300](https://store.arduino.cc/usa/mkr-wan-1300)
   * **NOTE:** Requires firmware v1.1.6 or later on the on-board Murata module. Please use the [MKRWANFWUpdate_standalone example](https://github.com/arduino-libraries/MKRWAN/blob/master/examples/MKRWANFWUpdate_standalone/MKRWANFWUpdate_standalone.ino) from latest [MKRWAN library](https://github.com/arduino-libraries/MKRWAN) release to update the firmware.
   * **WARNING**: [LoRa.onReceive(...)](https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md#register-callback) and [LoRa.recieve()](https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md#receive-mode) is not compatible with this board!

### Semtech SX1276/77/78/79 wiring (การเดินสายไฟ)

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


`NSS`, `NRESET`, และ `DIO0` pins สามารถเปลี่ยนได้โดยใช้ฟังก์ชัน `LoRa.setPins(ss, reset, dio0)` pin `DIO0` เป็น optional เอาไว้ใช้เฉพาะการรับแบบ callback mode ถ้าใช้ pin `DIO0` **จะต้อง** สามารถ interrupt ผ่าน [`attachInterrupt(...)`] ได้(https://www.arduino.cc/en/Reference/AttachInterrupt).

**NOTES**:
 * บอร์ดบางบอร์ด (เช่น Arduino Nano) ไม่สามารถจ่ายกระแสไฟได้อย่างเพียงพอให้ SX127x ในโหมด TX มันทำให้เกิดการ lockups เมื่อทำการส่งต้องแน่ใจว่าใช้แหล่งจ่ายไฟจากด้านนอก 3.3 V และใช้กระแสอย่างน้อย 120mA เมื่อใช้บอร์ดเหล่านี้
 * ถ้าบอร์ดมีไฟเลี้ยง 5V เช่น the Arduino Uno, Leonardo หรือ Mega จำเป็นที่จะต้องใช้ตัวแปลงแรงดันในการเดินวงจรไปยังโมดูล Semtech SX127x เพราะ โมดูล Semtech SX127x ไม่มีตัวแปลงแรงดันในตัว

## Installation

### Using the Arduino IDE Library Manager

1. Choose `Sketch` -> `Include Library` -> `Manage Libraries...`
2. Type `LoRa` into the search box.
3. Click the row to select the library.
4. Click the `Install` button to install the library.

### Using Git

```sh
cd ~/Documents/Arduino/libraries/
git clone https://github.com/chanonsersa/arduino-LoRa LoRa
```

## API

See [API.md](API.md).

## Examples

See [examples](examples) folder.

## FAQ

**1) Initilizating the LoRa radio is failing**

ให้ตรวจสอบการเดินสายไฟของคุณว่าตรงกับตารางหรือไม่
[Semtech SX1276/77/78/79 wiring](#semtech-sx1276777879-wiring)คุณสามารถใช้ฟังก์ชัน `LoRa.setPins(ss, reset, dio0)` เพื่อเปลี่ยน pin เดิมได้ วงจรแปลงแรงดันบางตัวไม่สามารถทำงานที่ความถี่ 8 MHz ได้ คุณสามารถใช้คำสั่ง `LoRa.setSPIFrequency(frequency)` เพื่อลดความถี่ SPI และต้องเรียกใช้ API ทั้งสองอันนี้ก่อน `LoRa.begin(...)`

**2) Can other radios see the packets I'm sending?**

ได้ เพราะ ทุกคลื่นสัญญาณ LoRa ที่มีการกำหนดค่าพารามิเตอร์เดียวกันและอยู่ในในระยะทางที่ packet สามารถส่งได้ จะสามารถเห็น packets ที่ส่งออกไป

**3) Is the data I'm sending encrypted?**

ไม่ เพราะทุกๆข้อมูลที่ส่งออกไปนั้นไม่มีการเข้ารหัส ถ้าต้องการให้ packet มีการเข้ารหัส คุณต้องทำการเข้ารหัสข้อมูลก่อนแล้วค่อยเขียนลงใน library ตามด้วยการถอดรหัสที่จุดรับข้อมูล

**4) How does this library differ from LoRaWAN libraries?**

ไลบรารีนี้จะกระจายสัญญาณ LoRa โดยตรง และให้ส่งข้อมูลไปถึงตัวรับได้ในระยะที่ส่งถึงและมี parameters เดียวกัน ทุกข้อมูลจะเป็นการ broadcast ไมมีการกำหนด address ส่วน LoRaWAN สร้างอยู่บน LoRA แต่มีการเพิ่ม address การเข้ารหัส และ การลำดับชั้น layer ซึ่งมันต้องการ LoRaWAN gateway และ LoRaWAN network และ application server

**5) Does this library honor duty cycles?**

ไม่ คุณต้องจัดการด้วยตัวเอง

**6) Which frequencies can I use?**

คุณสามารถใช้[ตารางนี้](https://www.thethingsnetwork.org/wiki/LoRaWAN/Frequencies/By-Country)เพื่อดูคลื่นความถี่ที่สามารถใช้ได้ในประเทศ การเลือกใช้คลื่นความถี่อยู่ที่ตัว hardware ซึ่งสามารถดูได้จาก data sheet หรือถามจาก supplier

โปรดสังเกตความถี่ที่ใช้ด้วยเพราะมีผลต่อกฎหมาย

## License

Libary นี้[ได้รับอณุญาติ](LICENSE) ภายใต้ [MIT Licence](https://en.wikipedia.org/wiki/MIT_License).
