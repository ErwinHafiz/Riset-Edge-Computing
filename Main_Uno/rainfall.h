#ifndef RAINFALL_H
#define RAINFALL_H

#include <Arduino.h>

extern const int rainfall_data_pin;        // PIN ANALOG
extern float rainfall_value;

void initRainfallSensor();
float readRainfall();

#endif