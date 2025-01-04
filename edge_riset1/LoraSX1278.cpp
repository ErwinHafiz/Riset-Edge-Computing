#include "LoraSX1278.h"

unsigned long lastPacketTime = 0; // Waktu terakhir menerima paket 

// Buffer untuk menyimpan data
std::vector<float> tempBuffer, humBuffer, rainBuffer, soilBuffer, phBuffer;

// Nilai sebelumnya
float prevTemp = 25.0, prevHum = 50.0, prevRain = 0.0, prevSoil = 30.0, prevPH = 7.0;




void setupLora(){
  // Serial.begin(9600);
  // delay(250);
  Serial.println("LoRa Receiver");

  // Setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  // param tambahan
  LoRa.setSPIFrequency(10000000);
  LoRa.setSignalBandwidth(125E3); // Bandwidth 125 kHz
  LoRa.setCodingRate4(5);         // Coding rate 4/5
  LoRa.setSpreadingFactor(7);     // Spreading factor 7
 
  if (!LoRa.begin(LORA_FREQUENCY)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  Serial.println("LoRa Initializing OK!");
  lastPacketTime = millis(); // Inisialisasi waktu awal
}

bool isOutlier(float value, const std::vector<float> &buffer) {
  if (buffer.size() < 2) return false; // Tidak cukup data untuk deteksi outlier
  Serial.print("Buffer size");
  Serial.println(buffer.size());

  std::vector<float> sortedBuffer = buffer;
  std::sort(sortedBuffer.begin(), sortedBuffer.end());

  size_t mid = sortedBuffer.size() / 2;
  float Q1 = sortedBuffer[mid / 2];
  float Q3 = sortedBuffer[mid + mid / 2];
  float IQR = Q3 - Q1;

  return (value < Q1 - 1.5 * IQR || value > Q3 + 1.5 * IQR);
}

float calculateMedian(std::vector<float> &buffer) {
  std::sort(buffer.begin(), buffer.end());
  size_t size = buffer.size();
  if (size % 2 == 0)
    return (buffer[size / 2 - 1] + buffer[size / 2]) / 2.0;
  else
    return buffer[size / 2];
}

void updateBuffer(std::vector<float> &buffer, float value) {
  if (buffer.size() >= BUFFER_SIZE) buffer.erase(buffer.begin());
  buffer.push_back(value);
}

void handleOutliers(SensorData &data) {
  // Temperature
  if (isOutlier(data.temperature, tempBuffer)) {
    data.temperature = tempBuffer.size() >= BUFFER_SIZE ? calculateMedian(tempBuffer) : prevTemp;
  } else {
    updateBuffer(tempBuffer, data.temperature);
    prevTemp = data.temperature;
  }

  // Humidity
  if (isOutlier(data.humidity, humBuffer)) {
    data.humidity = humBuffer.size() >= BUFFER_SIZE ? calculateMedian(humBuffer) : prevHum;
  } else {
    updateBuffer(humBuffer, data.humidity);
    prevHum = data.humidity;
  }

  // Rainfall
  if (isOutlier(data.rainfall, rainBuffer)) {
    data.rainfall = rainBuffer.size() >= BUFFER_SIZE ? calculateMedian(rainBuffer) : prevRain;
  } else {
    updateBuffer(rainBuffer, data.rainfall);
    prevRain = data.rainfall;
  }

  // Soil Moisture
  if (isOutlier(data.soilMoisturePercent, soilBuffer)) {
    data.soilMoisturePercent = soilBuffer.size() >= BUFFER_SIZE ? calculateMedian(soilBuffer) : prevSoil;
  } else {
    updateBuffer(soilBuffer, data.soilMoisturePercent);
    prevSoil = data.soilMoisturePercent;
  }

  // Soil pH
  if (isOutlier(data.phTanah, phBuffer)) {
    data.phTanah = phBuffer.size() >= BUFFER_SIZE ? calculateMedian(phBuffer) : prevPH;
  } else {
    updateBuffer(phBuffer, data.phTanah);
    prevPH = data.phTanah;
  }
}

void printSensorData(const SensorData &data) {
  Serial.println("===== Sensor Data After compute =====");
  Serial.print("Temperature: "); Serial.println(data.temperature);
  Serial.print("Humidity: "); Serial.println(data.humidity);
  Serial.print("Rainfall: "); Serial.println(data.rainfall);
  Serial.print("Soil Moisture (%): "); Serial.println(data.soilMoisturePercent);
  Serial.print("Soil pH: "); Serial.println(data.phTanah);
  Serial.println("========================");
}

void printSensorDataFirst(const SensorData &data) {
  Serial.println("===== Sensor Data FIRST=====");
  Serial.print("Temperature: "); Serial.println(data.temperature);
  Serial.print("Humidity: "); Serial.println(data.humidity);
  Serial.print("Rainfall: "); Serial.println(data.rainfall);
  Serial.print("Soil Moisture (%): "); Serial.println(data.soilMoisturePercent);
  Serial.print("Soil pH: "); Serial.println(data.phTanah);
  Serial.println("========================");
}



void readDataLora(){
    SensorData receivedData;
    LoRa.readBytes((uint8_t *)&receivedData, sizeof(receivedData));
    printSensorData(receivedData);
    lastPacketTime = millis(); 
    delay(100);
}

void restartLoRa(){
      // Jika tidak ada paket diterima dalam waktu tertentu, lakukan reset LoRa
  if (millis() - lastPacketTime > timeoutDuration) {
    Serial.println("No packet received for a while. Restarting LoRa...");
    LoRa.end(); // Matikan LoRa
    delay(100); // Tunggu sejenak
    if (LoRa.begin(LORA_FREQUENCY)) {
      Serial.println("LoRa restarted successfully.");
    } else {
      Serial.println("LoRa restart failed!");
    }
    lastPacketTime = millis(); // Perbarui waktu setelah restart
  }
}

// void printSensorData(const SensorData &data) {
//   Serial.println("===== Sensor Data Recive=====");
//   Serial.print("Counter: "); Serial.println(data.counter);
//   Serial.print("Temperature: "); Serial.println(data.temperature);
//   Serial.print("Humidity: "); Serial.println(data.humidity);
//   Serial.print("Rainfall: "); Serial.println(data.rainfall);
//   Serial.print("Soil Moisture (%): "); Serial.println(data.soilMoisturePercent);
//   Serial.print("Water Pump Status: "); Serial.println(data.automation);
//   Serial.print("Nitrogen: "); Serial.println(data.nitrogen);
//   Serial.print("Phosphorus: "); Serial.println(data.phosporus);
//   Serial.print("Potassium: "); Serial.println(data.potassium);
//   Serial.print("Soil pH: "); Serial.println(data.phTanah);
//   Serial.println("=======================");
//   Serial.print("Packet RSSI: "); Serial.println(LoRa.packetRssi());
//   Serial.print("Packet SNR: "); Serial.println(LoRa.packetSnr());
//   Serial.print("Size of data Recive: ");
//   Serial.println(sizeof(SensorData));
// }

