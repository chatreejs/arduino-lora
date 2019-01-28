# LoRaReceiver with 8 bit LED display

[![Build Status](https://travis-ci.org/travis-ci/travis-web.svg?branch=master)](https://travis-ci.org/travis-ci/travis-web)

เป็นการเพิ่มหลอด LED เพื่อวัดค่า RSSI ของ packet ที่ได้รับมาแสดงผลเป็นเลขฐาน 2 8 bit (0 - 255)
## Hardware
* [Arduino UNO R3](https://store.arduino.cc/usa/arduino-uno-rev3)
* [Semtech SX1276/77/78/79](http://www.semtech.com/apps/product.php?pn=SX1276)
* LED 9 หลอด
* ตัวต้านทาน 220 โอห์ม 9 ตัว

## Wiring
![diagram](https://github.com/Chanonsersa/Arduino-LoRa/blob/Chanonsersa-8bitLED/examples/LoRaReceiver8bit/8Bit-LED-diagram.png "8 bit LED display")

## Code
```cpp
void setup() {
    pinMode(2,OUTPUT);   
    pinMode(3,OUTPUT);  
    pinMode(4,OUTPUT);  
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(A0,OUTPUT);
    pinMode(A1,OUTPUT);
    pinMode(A2,OUTPUT);
    ...
```
กำหนด output pin ให้กับขา 2 - 7 และ A0 - A2

และจะใช้ฟังก์ชัน `led_show(number)` ในการเรียกใช้งาน
- โดย `number` จะเป็นค่าตั้งแต่ `0` - `255`
```cpp
void led_show(byte number) {
    if (number <= 128) {
        byte a = number % 2;      
        byte b = number / 2 % 2;     
        byte c = number / 4 % 2;        
        byte d = number / 8 % 2;
        byte e = number / 16 % 2;
        byte f = number / 32 % 2;
        byte g = number / 64 % 2;
        byte h = number / 128 % 2;

        digitalWrite(7,a); 
        digitalWrite(6,b); 
        digitalWrite(5,c); 
        digitalWrite(4,d); 
        digitalWrite(3,e); 
        digitalWrite(2,f); 
        digitalWrite(A0,g);
        digitalWrite(A1,h);
    } else {
        led_off();
    }
}
```

และฟังก์ชัน `led_off()` ในการสั่งปิดไฟทั้งหมด

```cpp
void led_off() {
    digitalWrite(7,0); 
    digitalWrite(6,0); 
    digitalWrite(5,0); 
    digitalWrite(4,0); 
    digitalWrite(3,0); 
    digitalWrite(2,0); 
    digitalWrite(A0,0);
    digitalWrite(A1,0);
}
```

### Example

ในตัวอย่างการเรียกใช้ 8bit LED จะใส่ค่า RSSI ของ packet ที่ได้รับเข้าไป
```cpp
void loop() {
  ...
  led_show(-(LoRa.packetRssi()));
  ...
}
```
ซึ่งค่า RSSI มีค่าเป็นลบ เราจะต้องแปลงให้เป็นค่าบวกก่อน
