#ifndef LORASX1278_H
#define LORASX1278_H
#include <SPI.h>
#include <LoRa.h>
#include <vector>

#define ss 5
#define rst 14
#define dio0 2
#define LORA_FREQUENCY 433E6

const size_t BUFFER_SIZE = 10; // Ukuran buffer untuk median

extern unsigned long lastPacketTime; 
const unsigned long timeoutDuration = 60000; // Waktu timeout restart LoRa

// Struct untuk menerima data
struct SensorData {
  float temperature;
  float humidity;
  float rainfall;
  float soilMoisturePercent;
  bool automation;
  uint16_t counter;
  uint16_t nitrogen;
  uint16_t phosporus;
  uint16_t potassium;
  float phTanah;
};

void setupLora();
void readDataLora();
void restartLoRa();
void printSensorDataFirst(const SensorData &data);
void printSensorData(const SensorData &data);
bool isOutlier(float value, const std::vector<float> &buffer);
float calculateMedian(std::vector<float> &buffer);
void updateBuffer(std::vector<float> &buffer, float value);

void handleOutliers(SensorData &data);

#endif
