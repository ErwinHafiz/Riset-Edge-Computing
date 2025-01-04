#ifndef DHHT_H
#define DHHT_H

#include <DHT.h> 
 
extern DHT dht;
extern float temperature;
extern float humidity;

void initDHT();

float readTemp();
float  readHum();
#endif