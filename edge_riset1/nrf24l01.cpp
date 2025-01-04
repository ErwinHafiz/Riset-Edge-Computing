// #include "nrf24l01.h"




// // Mosi 23, miso 19 , sck 18 

// unsigned long lastPacketTime = 0; // Waktu terakhir menerima paket
// const unsigned long timeoutDuration = 60000; // Waktu timeout restart LoRa


// // RF24 radio(CEpin, CSNpin); //ce, csn

// SensorData receivedData;

// /* ESP32 Pin 
// CE 22
// CSN 21
// SCK: 18
// MOSI: 23
// MISO: 19
// */ 


// void setup_esp_nrf24l01() {
//   Serial.begin(9600);
//   delay(250);
//   Serial.println("LoRa Receiver");

//   // Setup LoRa transceiver module
//   LoRa.setPins(ss, rst, dio0);
//   // param tambahan
//   LoRa.setSPIFrequency(10000000);
//   LoRa.setSignalBandwidth(125E3); // Bandwidth 125 kHz
//   LoRa.setCodingRate4(5);         // Coding rate 4/5
//   LoRa.setSpreadingFactor(7);     // Spreading factor 7
 
//   if (!LoRa.begin(LORA_FREQUENCY)) {
//     Serial.println("Starting LoRa failed!");
//     while (1);
//   }
  
//   Serial.println("LoRa Initializing OK!");
//   lastPacketTime = millis(); // Inisialisasi waktu awal

//   // End Setup LoRa


//   // radio.begin();
//   // if (!radio.begin()) {
//   //   Serial.println("NRF24L01 esp failed to initialize!");
//   //   while (1);
//   // } else { 
//   //   Serial.println("NRF24L01 esp succes to initialize!");
//   // }
//   // radio.setChannel(108);
//   // radio.openReadingPipe(1, address); // can read up to 6 pipe , 0 for writing 
//   // radio.setPALevel(RF24_PA_HIGH);
//   //   radio.setDataRate(RF24_250KBPS); // Set a lower data rate for more reliable communication
//   // Serial.println("NRF24L01 esp initialized successfully.");
//   // radio.printDetails();
//   // radio.startListening();
// }

// void read_data_received() {
//   if (LoRa.available()) {
//     LoRa.readBytes((uint8_t *)&receivedData, sizeof(receivedData));
//     printSensorData(receivedData);
//     lastPacketTime = millis(); 
//     delay(100);
//   } else {
//     Serial.println("Data tidak tersedia meskipun ada paket.");
//     delay(100);
    
//   }
// }


//   // if (radio.available()) {

//   //   radio.read(&receivedData, sizeof(receivedData));  // Baca data yang diterima
//   //   Serial.print("Counter = ");
//   //   Serial.println(receivedData.counter);
//   //   Serial.print("Temperature: ");
//   //   Serial.println(receivedData.temperature);
//   //   Serial.print("Humidity: ");
//   //   Serial.println(receivedData.humidity);
//   //   Serial.print("Rainfall: ");
//   //   Serial.println(receivedData.rainfall);
//   //   Serial.print("Adc: ");
//   //   Serial.println(receivedData.adc);
//   //   Serial.print("Tegangan: ");
//   //   Serial.println(receivedData.tegangan);
//   //   Serial.print("Soil Moisture Percentage: ");
//   //   Serial.println(receivedData.soilMoisturePercent);
//   //   Serial.print("Waterpump status : ");
//   //   Serial.println(receivedData.automation);
//   //   Serial.print("Nitrogen: ");
//   //   Serial.println(receivedData.nitrogen);
//   //   Serial.print("Phosporus: ");
//   //   Serial.println(receivedData.phosporus);
//   //   Serial.print("Potassium: ");
//   //   Serial.println(receivedData.potassium);
//   //   Serial.print("PH snesor value: ");
//   //   Serial.println(receivedData.phSensorValue);
//   //   Serial.print("PHtanah: ");
//   //   Serial.println(receivedData.phTanah);
//   //   Serial.print("Size of received data: ");
//   //   Serial.println(sizeof(receivedData));
    
//   //   // Serial.print(receivedMessage);

//   // } 
  
// // }

// void checkLoRa(){
//     // Jika tidak ada paket diterima dalam waktu tertentu, lakukan reset LoRa
//   if (millis() - lastPacketTime > timeoutDuration) {
//     Serial.println("No packet received for a while. Restarting LoRa...");
//     LoRa.end(); // Matikan LoRa
//     delay(100); // Tunggu sejenak
//     if (LoRa.begin(LORA_FREQUENCY)) {
//       Serial.println("LoRa restarted successfully.");
//     } else {
//       Serial.println("LoRa restart failed!");
//     }
//     lastPacketTime = millis(); // Perbarui waktu setelah restart
//   }
// }



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

