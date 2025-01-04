#include "npk.h"
#include <Arduino.h>
#include <SoftwareSerial.h>


#define DI 2
#define RO 3
#define DE 7
#define RE 8

// Membuat objek SoftwareSerial untuk menggantikan Serial2
SoftwareSerial npkSerial(RO, DI); // RX, TX


const byte nitro[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];

byte nitrogen() {
  npkSerial.flush();

  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  Serial.println("Sending Nitrogen Command:");
    for (byte i = 0; i < sizeof(nitro); i++) {
      Serial.print("0x");
      Serial.print(nitro[i], HEX);
      Serial.print(" ");
    }
  Serial.println();
  delay(10);
  if (npkSerial.write(nitro, sizeof(nitro)) == 8) {
    npkSerial.flush();
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++) {
      values[i] = npkSerial.read();
    }
  }
  return values[4];
}

byte phosphorous() {
  npkSerial.flush();

  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (npkSerial.write(phos, sizeof(phos)) == 8) {
    npkSerial.flush();
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++) {
      values[i] = npkSerial.read();
    }
  }
  return values[4];
}

byte potassium() {
  npkSerial.flush();

  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  if (npkSerial.write(pota, sizeof(pota)) == 8) {
    npkSerial.flush();
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    for (byte i = 0; i < 7; i++) {
      values[i] = npkSerial.read();
    }
  }
  return values[4];
}

void initNPKSensor() {
  npkSerial.begin(4800);

  // Initiation for NPK sensor
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  // put RS-485 into receive mode
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
}

void readNPKSensor(byte &nitrogen_value, byte &phosphorus_value, byte &potassium_value) {
  npk npkValue;
  nitrogen_value = nitrogen();
  delay(250);
  phosphorus_value = phosphorous();
  delay(250);
  potassium_value = potassium();
  delay(250);
  npkValue.nitrogen =nitrogen_value ; 
  npkValue.phosporus =phosphorus_value ; 
  npkValue.potassium =potassium_value ; 
  Serial.print("FromRead npk sensor harusnya di bodret 4800");
  Serial.println(nitrogen_value);
  Serial.println(phosphorus_value);
  Serial.println(potassium_value);

}