#ifndef NPKSENSOR_H
#define NPKSENSOR_H

#include <Arduino.h>

extern const byte nitro[];
extern const byte phos[];
extern const byte pota[];
extern byte values[];

struct npk{
  uint16_t nitrogen;
  uint16_t phosporus;
  uint16_t potassium;
};

void initNPKSensor();
void readNPKSensor(byte &nitrogen_value, byte &phosphorus_value, byte &potassium_value);
byte nitrogen();
byte phosphorous();
byte potassium();

#endif // NPKSENSOR_H