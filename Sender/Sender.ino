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

int a = A0;
int b = A1;
int c = 2;
int d = 3;
int e = 4;
int f = 5;
int g = 6;

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  
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
  initSegment();
}

void loop() {
  switch (th.Read()) {
    case 2:
      Serial.println("CRC failed");
      codeFailed();
      break;
    case 1:
      Serial.println("Sensor offline");
      codeOffline();
    case 0:
      Serial.print("Sending packet: ");
      if(th.Read() == 0){
        showNumber(1);
      }
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

void initSegment() {
  for (int i = 0; i<10 ;i++){
    showNumber(i);
    delay(70);
    turnOff();
  }
}

void showNumber(int number) {
  turnOff();
  if(number != 1 && number != 4)
    digitalWrite(a,LOW);
  if(number != 5 && number != 6)
    digitalWrite(b,LOW);
  if(number != 2)
    digitalWrite(c,LOW);
  if(number != 1 && number != 4 && number != 7)
    digitalWrite(d,LOW);
  if(number == 2 || number == 6 || number == 8 || number == 0)
    digitalWrite(e,LOW);
  if(number != 1 && number != 2 && number != 3 && number != 7)
    digitalWrite(f,LOW);
  if (number != 0 && number != 1 && number != 7)
    digitalWrite(g,LOW);
}

void codeOffline() {
  turnOff();
  digitalWrite(a, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void codeFailed() {
  turnOff();
  digitalWrite(a, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void turnOff() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}
