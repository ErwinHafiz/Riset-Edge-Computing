// #include "dhht.h"
// #include "nrf24l01.h"
// #include "rainfall.h"
// #include "soilMoisture.h"
// #include "automation.h"
// #include "npk.h"
// #include "phSensor.h"
// #include "soilMoisture.h"

// // Define the pins used by the transceiver module
// #define ss 10
// #define rst 9
// #define dio0 4
// #define LORA_MAC_PRIVATE_SYNCWORD                   0x12
// #define LORA_MAC_PUBLIC_SYNCWORD                    0x34
// #define LORA_FREQUENCY 433E6
// // sck 13, miso 12, mosi11

// const int retries = 3; // Maksimal pengiriman ulang
// const int timeout = 1000; // Waktu tunggu untuk ACK (ms)

// // RF24 radio(CePin, CsnPin);  //ce, csn --> radio object

// uint16_t indeks = 0; // indeks penampung counter


// void setupNrf24l01() {
//   // Serial.begin(9600);
//   // while (!Serial);
//   // delay(250);
//   // Setup LoRa transceiver module
//   Serial.println("LoRa Sender");
//   LoRa.setPins(ss, rst, dio0);
//   // Parameter tambahan 
//   LoRa.setSPIFrequency (10000000); // cuman bisa 10 kalo 20 ga jalan
//   LoRa.setTxPower(20);
//   LoRa.setSignalBandwidth(125E3); // Bandwidth 125 kHz
//   LoRa.setCodingRate4(5);         // Coding rate 4/5
//   LoRa.setSpreadingFactor(7);     // Spreading factor 7

//   // Set the LoRa frequency
//   while (!LoRa.begin(433E6)) {
//     Serial.println("Initializing LoRa...");
//     delay(500);
//   }
//   Serial.println("LoRa Initializing OK!");

//   // radio.begin();
//   // if (!radio.begin()) {
//   //   Serial.println("NRF24L01 uno failed to initialize!");
//   //   Serial.println("Trying to connect ... ");
//   //   radio.printDetails();
//   //   // delay(300);
//   //   while (1)
//   //     ;
//   // } else {
//   //   Serial.println("NRF24L01 initialized successfully.");
//   // }

//   // radio.setChannel(108);  // 0-124 channel
//   // radio.openWritingPipe(address);

//   // radio.setPALevel(RF24_PA_HIGH);  //RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
//   // radio.setDataRate(RF24_250KBPS); // Set a lower data rate for more reliable communication

//   // // radio.setDataRate (RF24_2MBPS); //exchange rate. To choose RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
//   // // radio.setRetries(0, 15); //(time between attempts to reach out, number of attempts)

//   // radio.printDetails();
//   // radio.stopListening();


// }

// void readData(SensorData &data) {
//   indeks ++;
//   static uint16_t counter = 0;
//   data.counter = ++counter;
//   data.temperature = random(15, 35);
//   data.humidity = random(30, 70);
//   data.rainfall = random(0, 10);
//   data.soilMoisturePercent = random(40, 80);
//   data.automation = counter % 2;
//   data.nitrogen = random(10, 50);
//   data.phosporus = random(5, 25);
//   data.potassium = random(10, 40);
//   data.phTanah = random(5, 8);
//   // SensorData dataToSend;



//   // // soil moisture 
//   // // readSoilMoisture();
//   // // soilMoisture soilMoistureValue;
//   //  soilMoisture soilMoistureValue = readSoilMoisture();  // Ambil struct dari fungsi readSoilMoisture

//   // // npk 
//   // byte nitrogen_value, phosphorus_value, potassium_value;
//   // readNPKSensor(nitrogen_value, phosphorus_value, potassium_value);
//   // npk npkValue ; 

  
//   // // Automation 
//   // Automation automationValue;

//   // // DHT
//   // readTemp();
//   // readHum();

//   // //PH
//   // readPh();

//   // // Mengisi nilai untuk dikirim (NRF)
//   // dataToSend.counter = indeks;                        //  counter
//   // dataToSend.temperature = random(10);//readTemp();  //  suhu
//   // dataToSend.humidity = random(20); //readHum();        //  kelembaban
//   // dataToSend.rainfall = readRainfall();             //  raindfall

//   // // dataToSend.adc = soilMoistureValue.adc;             //  soil moisture // ga dipake buat save nrf byte maximum
//   // // dataToSend.tegangan = soilMoistureValue.tegangan;             //  soil moisture// ga dipake buat save nrf byte maximum
//   // dataToSend.soilMoisturePercent = soilMoistureValue.soilMoisturePercent;             //  soil moisture

//   // dataToSend.automation = waterPinState;             // status pompa air
//   // //npk
//   //   dataToSend.nitrogen = npkValue.nitrogen;
//   // dataToSend.phosporus = npkValue.phosporus;
//   // dataToSend.potassium = npkValue.potassium;
//   // // dataToSend.nitrogen = nitrogen_value;
//   // // dataToSend.phosporus = phosphorus_value;
//   // // dataToSend.potassium = potassium_value;
//   // //ph sensor
//   // // dataToSend.phSensorValue =phSensorValue; // ga dipake buat save nrf byte maximum
//   // dataToSend.phTanah = phTanah;


//   // if (isnan(dataToSend.temperature) || isnan(dataToSend.humidity) || isnan(dataToSend.rainfall)) {
//   //   Serial.println("Gagal membaca dari sensor !");
//   // }

//   // bool ok = false;
//   // ok = radio.write(&dataToSend, sizeof(dataToSend));



//   // bool ok = LoRa.beginPacket();
//   // if (ok) {
//   //   LoRa.write((uint8_t *)&dataToSend, sizeof(dataToSend));
//   //   Serial.print("Data Size: "); Serial.println(sizeof(dataToSend));
//   //   Serial.print("Data Sent: "); 
//   //   Serial.write((uint8_t *)&dataToSend, sizeof(dataToSend));
//   //   Serial.println();
//   //   LoRa.endPacket();

//   //   Serial.println("Data Successfully Sent!");
//   //   printSensorData(dataToSend);
//   // } else {
//   //   Serial.println("Failed to send data via NRF24L01!");
//   //   printSensorData(dataToSend);
//   // }
//   // delay(12000); // Optional delay



//   // if (!isnan(dataToSend.temperature) && !isnan(dataToSend.humidity)&& !isnan(dataToSend.rainfall) &&  ok) {  // data dikirim ke nrf jika data sensor tidak = nan dan nrf receiver tersedia
//   //   Serial.println("Data Berhasil Dikirim dari NRF24L01");
//   //   Serial.print("data send counter = ");
//   //   Serial.println(dataToSend.counter);
//   //   Serial.print("data send temperature = ");
//   //   Serial.println(dataToSend.temperature);
//   //   Serial.print("data send humidity = ");
//   //   Serial.println(dataToSend.humidity);
//   //   Serial.print("data send rainfal = ");
//   //   Serial.println(dataToSend.rainfall);
//   //   // Serial.print("Soil Moisture ADC: ");
//   //   // Serial.println(dataToSend.adc);
//   //   // Serial.print("Soil Moisture Tegangan (Voltage): ");
//   //   // Serial.println(dataToSend.tegangan);
//   //   Serial.print("Soil Moisture Percentage: ");
//   //   Serial.println(dataToSend.soilMoisturePercent);
//   //   Serial.print("Waterpum Status : ");
//   //   Serial.println(dataToSend.automation);
//   //   Serial.print("Nitrogen : ");
//   //   Serial.println(dataToSend.nitrogen);
//   //   Serial.print("Phosporus : ");
//   //   Serial.println(dataToSend.phosporus);
//   //   Serial.print("Potassium : ");
//   //   Serial.println(dataToSend.potassium);
//   //   // Serial.print("PH Sensor Value : ");
//   //   // Serial.println(dataToSend.phSensorValue);
//   //   Serial.print("PH Tanah : ");
//   //   Serial.println(dataToSend.phTanah);
//   //   Serial.print("Size of data being sent: ");
//   //   Serial.println(sizeof(dataToSend));
    

//   // }

//   // else {
//   //   Serial.println("Gagal mengirim data dari NRF24L01 oioioi");
//   //   // // Serial.println(dataToSend.phSensorValue);
//   //   // // Serial.println(dataToSend.phTanah);
//   //   // // Serial.println(dataToSend.phosporus);
//   //   // // Serial.println(dataToSend.nitrogen);
//   //   // // Serial.println(dataToSend.potassium);
//   //   // Serial.println(dataToSend.automation);

//   //   //debuging :
//   //   Serial.print("data send counter = ");
//   //   Serial.println(dataToSend.counter);
//   //   Serial.print("data send temperature = ");
//   //   Serial.println(dataToSend.temperature);
//   //   Serial.print("data send humidity = ");
//   //   Serial.println(dataToSend.humidity);
//   //   Serial.print("data send rainfal = ");
//   //   Serial.println(dataToSend.rainfall);
//   //   // Serial.print("Soil Moisture ADC: ");
//   //   // Serial.println(dataToSend.adc);
//   //   // Serial.print("Soil Moisture Tegangan (Voltage): ");
//   //   // Serial.println(dataToSend.tegangan);
//   //   Serial.print("Soil Moisture Percentage: ");
//   //   Serial.println(dataToSend.soilMoisturePercent);
//   //   Serial.print("Waterpum Status : ");
//   //   Serial.println(dataToSend.automation);
//   //   Serial.print("Nitrogen : ");
//   //   Serial.println(dataToSend.nitrogen);
//   //   Serial.print("Phosporus : ");
//   //   Serial.println(dataToSend.phosporus);
//   //   Serial.print("Potassium : ");
//   //   Serial.println(dataToSend.potassium);
//   //   // Serial.print("PH Sensor Value : ");
//   //   // Serial.println(dataToSend.phSensorValue);
//   //   Serial.print("PH Tanah : ");
//   //   Serial.println(dataToSend.phTanah);

//   //   Serial.print("Size of data being sent: ");
//   //   Serial.println(sizeof(dataToSend));
//   //   delay(200);  // delay


//   // } 

// }
// void sendData(const SensorData &data){
//   LoRa.beginPacket();
//   LoRa.write((uint8_t *)&data, sizeof(data));
//   LoRa.endPacket();
//   Serial.println("Data Successfully Sent!");
//   printSensorData(data);
//   delay(100);
// }


// void printSensorData(const SensorData &data) {
//   Serial.println("===== Sensor Data =====");
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
//   Serial.print("Size of data send: ");
//   Serial.println(sizeof(SensorData));
// }
