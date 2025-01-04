#include "dhht.h"

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
float temperature ;
float humidity ;

void initDHT() {
  dht.begin();
  Serial.println("DHT Sensor initialized.");
}

float readTemp(){
  temperature = dht.readTemperature();
  return temperature;
}

float readHum(){
  humidity = dht.readHumidity();
  return humidity;  
}
  // if (isnan(temperature) || isnan(humidity)) {
  //   Serial.println("Failed to read from DHT sensor!");
  // } else {
  //   Serial.print("Temperature: ");
  //   Serial.println(temperature);
  //   Serial.print("Humidity: ");
  //   Serial.println(humidity);
  // }