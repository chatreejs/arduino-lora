#include <SPI.h>
#include <LoRa.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"

Adafruit_AM2320 am2320 = Adafruit_AM2320();

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
  LoRa.setTxPower(17);
  am2320.begin();
}

void loop() {
  LoRa.beginPacket();
  LoRa.print("Humidity: ");
  LoRa.print(am2320.readHumidity());
  LoRa.print("%, temperature: ");
  LoRa.print(am2320.readTemperature());
  LoRa.print("°C");
  LoRa.endPacket();
  Serial.print("Send packet #");
  Serial.println(counter);
  counter++;
  delay(2000);
}
