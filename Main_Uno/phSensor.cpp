#include "phSensor.h"

#define analogInPin A2 // di esp = 35 , arduino = A2 (Kuning DMS - A0), Hijau dms - 6 Uno, Kabel hitam-> orange dms, putih -> gnd board

int phSensorValue;        // Nilai ADC dari sensor
float phTanah;

void initPhSensor() {
  // Inisialisasi pin sensor pH tanah
  pinMode(analogInPin, INPUT);
}

void readPh() {
  phSensorValue = analogRead(analogInPin);
  phTanah = (-0.0693 * phSensorValue) + 7.3855;
  // phTanah = (-0.015 * phSensorValue) +16;

}