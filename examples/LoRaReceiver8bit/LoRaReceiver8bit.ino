#include <SPI.h>
#include <LoRa.h>

// LoRa connect config
#define NSS_PIN    10
#define NRESET_PIN 9
#define DIO0_PIN   8

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
  
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Node - Receiver");
  LoRa.setPins(NSS_PIN, NRESET_PIN, DIO0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while(1);
  }
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(1);
  LoRa.setSpreadingFactor(12);
  LoRa.setPreambleLength(8);
  LoRa.enableCrc();
  //LoRa.setTimeout(100);
}

void loop() {
  if (LoRa.parsePacket() > 0) {
    String text = LoRa.readString();
    Serial.print("Receiver '");
    Serial.print(text);
    Serial.print("' RSSI:");
    Serial.print(LoRa.packetRssi());
    Serial.print(" SNR:");
    Serial.println(LoRa.packetSnr());
    digitalWrite(A2,1);
    led_show(-(LoRa.packetRssi()));
  }
  delay(100);
  digitalWrite(A2,0);
}

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

void led_show(byte number) {
  if (number <= 255) {
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
