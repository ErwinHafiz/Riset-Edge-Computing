#ifndef LORASX1278_H
#define LORASX1278_H
#include <SPI.h>
#include <LoRa.h>
#include <RF24.h>

// esp32 pin
#define ss 5
#define rst 14
#define dio0 2
#define LORA_MAC_PRIVATE_SYNCWORD                   0x12
#define LORA_MAC_PUBLIC_SYNCWORD                    0x34
#define LORA_FREQUENCY 433E6
// Mosi 23, miso 19 , sck 18 

extern unsigned long lastPacketTime; // Waktu terakhir menerima paket
const unsigned long timeoutDuration = 60000; // Waktu timeout restart LoRa

// Struct untuk menerima data
struct SensorData {
  //dht
  float temperature;
  float humidity;
  //rainfall
  float rainfall;
  //soilMoisture
  // uint16_t adc; // ga dipake buat save nrf byte maximum
  // float tegangan;  // ga dipake buat save nrf byte maximum

  float soilMoisturePercent; 
  // automation 
  bool automation; 
  // counter
  uint16_t counter;
  // NPK
  uint16_t nitrogen ;
  uint16_t phosporus ;
  uint16_t potassium ;
  // PH sensor
  // uint16_t phSensorValue; // ga dipake buat save nrf byte maximum
  float phTanah;

} __attribute__((packed, aligned(1)));

void setupLora();
void readDataLora();
void restartLoRa();
void printSensorData(const SensorData &data);


bool ok(SensorData &data);

#endif