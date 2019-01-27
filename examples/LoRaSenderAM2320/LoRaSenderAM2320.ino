#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <AM2320.h>
AM2320 th;

int counter = 0;

// LoRa connect config
#define NSS_PIN    10
#define NRESET_PIN 9
#define DIO0_PIN   8


void setup() {  
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Node - Sender #1");

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
  LoRa.setTxPower(17);
}

void loop() {
  switch (th.Read()) {
    case 2:
      Serial.println("CRC failed");
      break;
    case 1:
      Serial.println("Sensor offline");
      break;
    case 0:
      Serial.print("Sending packet: ");
      Serial.println(counter);
      
      // send packet
      LoRa.beginPacket();
      LoRa.print("Humidity: ");
      LoRa.print(th.h);
      LoRa.print("%, temperature: ");
      LoRa.print(th.t);
      LoRa.print("°C");
      LoRa.endPacket();
      counter++;
      break;
  }
  delay(3000);
}
