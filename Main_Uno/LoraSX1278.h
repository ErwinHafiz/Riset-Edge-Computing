#ifndef LORASX1278_H
#define LORASX1278_H
#include <SPI.h>
#include <LoRa.h>



extern const int ss;
extern const int tst;
extern const int dio;
extern const uint8_t LORA_MAC_PRIVATE_SYNCWORD;
extern const uint8_t LORA_MAC_PUBLIC_SYNCWORD;
extern const uint32_t LORA_FREQUENCY;

/* Lora arduino pin 
 SCK ---> 13
 MISO  ---> 12 
 MOSI  ---> 11 
 NSS   ---> 10 
 RST ---> 9
 DIO0 ---> 4
 GND --> GND 
 3.3V --> 3.3V
*/

// Define the data structure
struct SensorData {
  uint8_t counter; 
  uint8_t temperature;
  float humidity;
  float rainfall;
  float soilMoisturePercent;
  bool automation;
  uint16_t nitrogen;
  uint16_t phosporus;
  uint16_t potassium;
  float phTanah;
}__attribute__((packed, aligned(1)));

void setupLora();
void readData(SensorData &data);
void sendDataLora(const SensorData &data);
void printDataLora(const SensorData &data);

#endif