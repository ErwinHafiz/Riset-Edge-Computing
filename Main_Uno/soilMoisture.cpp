#include "soilMoisture.h"

const int soilMoisturePin = A0;



void initSoilMoistureSensor() {
  pinMode(soilMoisturePin, INPUT);
  Serial.println("Soil Moisture Sensor initialized.");
}

soilMoisture readSoilMoisture() {
  soilMoisture soilMoistureValue; 
  // soilMoistureValue.adc = (analogRead(soilMoisturePin) + 1)/4; //esp
  soilMoistureValue.adc = analogRead(soilMoisturePin); //uno 
  soilMoistureValue.tegangan = soilMoistureValue.adc * (5.0 / 1023.0);
  soilMoistureValue.soilMoisturePercent = (100 - ((soilMoistureValue.adc/1023.00)*100));
  // soilMoistureValue.soilMoisturePercent = 100 - ((soilMoistureValue.adc / 1023.0) * 100);



  

   // Debugging: lihat nilai di serial monitor
  Serial.print("ADC Value: ");
  Serial.println(soilMoistureValue.adc);
  Serial.print("Soil Moisture Voltage: ");
  Serial.println(soilMoistureValue.tegangan);
  Serial.print("Soil Moisture Percentage: ");
  Serial.println(soilMoistureValue.soilMoisturePercent);
  return soilMoistureValue;

}