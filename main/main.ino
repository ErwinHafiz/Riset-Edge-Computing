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
  // put your main code here, to run repeatedly:
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

  SensorData data;
  if(ok(data)){
    printSensorData(data);
  }

}
