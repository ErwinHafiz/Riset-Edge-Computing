#ifndef SOILMOISTURE_H
#define SOILMOISTURE_H

#include <Arduino.h>

extern const int soilMoisturePin;

struct soilMoisture {
  uint16_t adc;
  float tegangan;
  float soilMoisturePercent; 
};

void initSoilMoistureSensor();
soilMoisture readSoilMoisture();

#endif