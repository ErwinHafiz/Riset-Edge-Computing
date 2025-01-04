#ifndef PHSENSOR_H
#define PHSENSOR_H

#include <Arduino.h>

extern const int analogInPin;
extern int phSensorValue;
extern float phTanah;

void initPhSensor();
void readPh();

#endif