// #include "nrf24l01.h"
// #include <Wire.h>
// #include <SPI.h>
// #include <LoRa.h>
#include "LoraSX1278.h"
void setup() {
  // put your setup code here, to run once:
  // setup_esp_nrf24l01();
  Serial.begin(9600);
  delay(100);
  setupLora();
}

void loop() {
  // if (LoRa.parsePacket()) {
  //   read_data_received();
  // }
  // int packetDatang = LoRa.parsePacket();
  // if (packetDatang == sizeof(SensorData)){
  //   read_data_received();
  // }

  // read_data_received();
  
  // Periksa apakah ada paket masuk
  // int packetSize = LoRa.parsePacket();
  // if (packetSize == sizeof(SensorData)) {
  //   readDataLora();
  // } else if (packetSize > 0) {
  //   Serial.println("Invalid packet size received.");
  //   restartLoRa();
  //   // while (LoRa.available()) LoRa.read(); // Clear buffer
  // }
  //   restartLoRa();

  // SensorData data;
  // if(ok(data)){
  //   printSensorData(data);
  // }
// ------ //

  SensorData data;

  // Simulasi data random
  data.temperature = random(20, 35) + random(0, 100) / 100.0;
  data.humidity = random(40, 80) + random(0, 100) / 100.0;
  data.rainfall = random(0, 10) + random(0, 100) / 100.0;
  data.soilMoisturePercent = random(10, 60) + random(0, 100) / 100.0;
  data.phTanah = random(5, 9) + random(0, 100) / 100.0;
  printSensorDataFirst(data);
  Serial.println("=============hoho=============");
  handleOutliers(data);
  printSensorData(data);

  delay(8000); // Delay untuk simulasi

}
