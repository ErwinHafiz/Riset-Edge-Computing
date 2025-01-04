#include "LoraSX1278.h"


unsigned long lastPacketTime = 0; // Waktu terakhir menerima paket




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

void printSensorData(const SensorData &data) {
  Serial.println("===== Sensor Data Recive=====");
  Serial.print("Counter: "); Serial.println(data.counter);
  Serial.print("Temperature: "); Serial.println(data.temperature);
  Serial.print("Humidity: "); Serial.println(data.humidity);
  Serial.print("Rainfall: "); Serial.println(data.rainfall);
  Serial.print("Soil Moisture (%): "); Serial.println(data.soilMoisturePercent);
  Serial.print("Water Pump Status: "); Serial.println(data.automation);
  Serial.print("Nitrogen: "); Serial.println(data.nitrogen);
  Serial.print("Phosphorus: "); Serial.println(data.phosporus);
  Serial.print("Potassium: "); Serial.println(data.potassium);
  Serial.print("Soil pH: "); Serial.println(data.phTanah);
  Serial.println("=======================");
  Serial.print("Packet RSSI: "); Serial.println(LoRa.packetRssi());
  Serial.print("Packet SNR: "); Serial.println(LoRa.packetSnr());
  Serial.print("Size of data Recive: ");
  Serial.println(sizeof(SensorData));
}

