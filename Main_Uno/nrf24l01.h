#include <SPI.h>
#include <LoRa.h>
#include <nRF24L01.h>
#include <RF24.h>
/* arduino pin 
 ce   ---> 9 
 csn  ---> 10 
 csk  ---> 13 
 MOSI ---> 11 
 MISO ---> 12
*/
const int CePin = 9  ; // CE pin for radio object
const int CsnPin = 10  ;// CSN pin for radio object




extern RF24 radio;  // CE, CSN
const byte address[6] = "00001"; // alamat


// Struct untuk mengirimkan data
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


void setupNrf24l01();
void readData(SensorData &data);
void sendData(const SensorData &data);
void printSensorData(const SensorData &data);


