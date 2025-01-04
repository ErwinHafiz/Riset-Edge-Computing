#include "LoraSX1278.h"
#include "rainfall.h"
#include "soilMoisture.h"
#include "automation.h"
#include "npk.h"
#include "phSensor.h"
#include "soilMoisture.h"
#include "dhht.h"


const int ss = 10;
const int rst = 9;
const int dio0 = 4;
const uint8_t LORA_MAC_PRIVATE_SYNCWORD = 0x12;
const uint8_t LORA_MAC_PUBLIC_SYNCWORD = 0x34;
const uint32_t LORA_FREQUENCY = 433E6;


void setupLora(){
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
  // Parameter tambahan 
  LoRa.setSPIFrequency (10000000); // cuman bisa 10 kalo 20 ga jalan
  LoRa.setTxPower(20);
  LoRa.setSignalBandwidth(125E3); // Bandwidth 125 kHz
  LoRa.setCodingRate4(5);         // Coding rate 4/5
  LoRa.setSpreadingFactor(7);     // Spreading factor 7
  // Set the LoRa frequency
  while (!LoRa.begin(433E6)) {
    Serial.println("Initializing LoRa...");
    delay(100);
  }
  LoRa.setSyncWord(LORA_MAC_PRIVATE_SYNCWORD); // Sync word for private network

  Serial.println("LoRa Initializing OK!");
}


void sendDataLora(const SensorData &data){
  if (!LoRa.beginPacket()){
    Serial.println("failed send packet" );
    return;
  }

  LoRa.write((uint8_t *)&data, sizeof(data));
  LoRa.endPacket();
  Serial.println("Data Successfully Sent!");
  Serial.print("Succes Data Size = "); Serial.println(sizeof(data));
  printDataLora(data);
  delay(100);

}

void printDataLora(const SensorData &data){
  Serial.println("===== Sensor Data Print =====");
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
  Serial.print("Size of data send: ");
  Serial.println(sizeof(SensorData));
}



void readData(SensorData &data){
  // soil moisture 
  readSoilMoisture();
  // soilMoisture soilMoistureValue;
  soilMoisture soilMoistureValue = readSoilMoisture();  // Ambil struct dari fungsi readSoilMoisture

  // npk 
  byte nitrogen_value, phosphorus_value, potassium_value;
  readNPKSensor(nitrogen_value, phosphorus_value, potassium_value);
  npk npkValue ; 
  // Automation 
  Automation automationValue;
  // DHT
  readTemp();
  readHum();
  //PH
  readPh();



  if (isnan(data.temperature) || isnan(data.humidity) || isnan(data.rainfall)) {
    Serial.println("Gagal membaca dari sensor !");
  }

  // Mengisi nilai untuk dikirim (NRF)
  static uint8_t counter = 0 ;
  data.counter = ++counter;                                               //  counter
  data.temperature = random(10);//readTemp();                             //  suhu
  data.humidity = random(20); //readHum();                                //  kelembaban
  data.rainfall = readRainfall();                                         //  raindfall
  // data.adc = soilMoistureValue.adc;                                    //  soil moisture 
  // data.tegangan = soilMoistureValue.tegangan;                          //  soil moisture 
  data.soilMoisturePercent = soilMoistureValue.soilMoisturePercent;       //  soil moisture
  data.automation = waterPinState;                                        // status pompa air
  data.nitrogen = npkValue.nitrogen;                                      // npk
  data.phosporus = npkValue.phosporus;                                    // npk
  data.potassium = npkValue.potassium;                                    // npk
  // data.nitrogen = nitrogen_value;
  // data.phosporus = phosphorus_value;
  // data.potassium = potassium_value;
  data.phTanah = phTanah;                                                 //ph sensor
  // data.phSensorValue =phSensorValue;                                   //ph sensor 



  // sx1278 dumy start
  // static uint8_t counter = 0 ;
  // data.counter = ++counter;
  // data.temperature = random(15, 35);
  // data.humidity = random(30, 70);
  // data.rainfall = random(0, 10);
  // data.soilMoisturePercent = random(40, 80);
  // data.automation = counter % 2;
  // data.nitrogen = random(10, 50);
  // data.phosporus = random(5, 25);
  // data.potassium = random(10, 40);
  // data.phTanah = random(5, 8);
}
