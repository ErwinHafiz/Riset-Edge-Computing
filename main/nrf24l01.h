// #include <Wire.h>
// #include <SPI.h>
// #include <LoRa.h>
// #define ss 5
// #define rst 14
// #define dio0 2
// #define LORA_MAC_PRIVATE_SYNCWORD                   0x12
// #define LORA_MAC_PUBLIC_SYNCWORD                    0x34
// #define LORA_FREQUENCY 433E6



// // #include <SPI.h>
// // #include <nRF24L01.h>
// // #include <RF24.h>
// // ESP32 -> receiver
// // CE kabel orange , CSN kuning , CSK hijau  

// // const int ss = 5;
// // const int rst = 14;
// // const int dio0 = 2;


// // extern RF24 radio;  // CE, CSN 
// // const byte address[6] = "00001";


// // Struct untuk mengirimkan beberapa data sensor
// struct SensorData {
//   //dht
//   float temperature;
//   float humidity;
//   //rainfall
//   float rainfall;
//   //soilMoisture
//   // uint16_t adc;
//   // uint16_t tegangan;
//   float soilMoisturePercent; 

//   bool automation ; 
//   uint16_t counter;
//   uint16_t nitrogen ; 
//   uint16_t phosporus ; 
//   uint16_t potassium; 
//     // PH sensor
//   // uint16_t phSensorValue; 
//   float phTanah;

//   // counter

// } __attribute__((packed, aligned(1)));
// // #pragma pack() // Kembalikan pengaturan packing normal setelah struct

// void setup_esp_nrf24l01();
// void read_data_received();
// void checkLoRa();
// void printSensorData(const SensorData &data);

