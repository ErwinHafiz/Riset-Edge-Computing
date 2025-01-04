#include "LoraSX1278.h"
// #include "nrf24l01.h"
#include "dhht.h"
#include "soilMoisture.h"
#include "automation.h"
#include "rtc3231.h"
#include "npk.h"
#include "phSensor.h"
#include "rainfall.h"

unsigned long currentTime ; 
unsigned long startTime ; 
unsigned long intervalTime = 12000; // interval for sending nrf24l01

unsigned long previousDhtMillis = 0; 
const unsigned long dhtInterval = 2000; // Interval waktu untuk membaca DHT

void setup() {
  Serial.begin(9600);
  delay(100);
  // setupNrf24l01();
  setupLora();
  setupRTC();
  initDHT();
  initRainfallSensor();
  initSoilMoistureSensor();
  initAutomation();
  initNPKSensor();
  initPhSensor();


}

void loop() {
  // SensorData data;
  // readData(data);
  // sendDataLora(data);
  currentTime = millis(); 
  
  
  // turnOnWaterPump();
  
  // Serial.println(AutomationStatus.waterPinStatus);

  // Membaca sensor DHT setiap 2 detik
  if (currentTime - previousDhtMillis >= dhtInterval) {
    previousDhtMillis = currentTime;
    readTemp();
    readHum();
  }


  if(currentTime - startTime >= intervalTime){
    // readAndSend();
    SensorData data;
    readData(data);
    sendDataLora(data);
    startTime = currentTime;
  }
  //  cekIntervalTime();
  byte second , minute , hour , dayOfWeek, dayOfMonth, month, year;
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  time timeToDisplay; 
  timeToDisplay.hour1 = hour;
  timeToDisplay.minute1 = minute;
  timeToDisplay.seconds1 = second;

  if (timeToDisplay.hour1 ==21 && timeToDisplay.minute1 == 25 && timeToDisplay.seconds1 == 10  && !waterPinState){
    Serial.println("Jadwal water pump hidup");
    turnOnWaterPump();
    Serial.println("ini dari struct  --> ");
    Serial.println(timeToDisplay.hour1);
    Serial.println(timeToDisplay.minute1);
    Serial.println(timeToDisplay.seconds1);
  }

  if (timeToDisplay.hour1 ==21 && timeToDisplay.minute1 == 27 && timeToDisplay.seconds1 == 00  && !waterPinState){
    Serial.println("Jadwal water pump hidup");
    turnOnWaterPump();
    Serial.println("ini dari struct  --> ");
    Serial.println(timeToDisplay.hour1);
    Serial.println(timeToDisplay.minute1);
    Serial.println(timeToDisplay.seconds1);
  }

  displayTime(); // digunakan untuk menampilkan &  mengset waktu yang dikirim ke NRF

  // Serial.println("ini dari struct  --> ");
  // Serial.println(timeToDisplay.hour1);
  // Serial.println(timeToDisplay.minute1);
  // Serial.println(timeToDisplay.seconds1);
  // Serial.println("---end---");
  // delay(3000);
  // cek time interval dari water pump 
  cekIntervalTime();

}
