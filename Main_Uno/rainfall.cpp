#include "rainfall.h"

const int rainfall_data_pin = A3;        // PIN ANALOG
float rainfall_value;

void initRainfallSensor() {
  pinMode(rainfall_data_pin, INPUT);
  Serial.println("Rain Fall Sensor initialized.");
}

float readRainfall() {
  rainfall_value = analogRead(rainfall_data_pin);
  return rainfall_value;
  
}