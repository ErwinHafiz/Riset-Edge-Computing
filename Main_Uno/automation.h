#ifndef AUTOMATION_H
#define AUTOMATION_H

#include <Arduino.h>

const int RELAY_WATER_PUMP = 8;

// Variabel global untuk status pin dan waktu
extern unsigned long StartTime;
extern unsigned long timeInterval;
extern bool waterPinState ;


struct Automation{
  bool waterPinStatus; 
};

// Deklarasi fungsi
void initAutomation();
void turnOnWaterPump();
void cekIntervalTime();



#endif 