#include "automation.h"

// Inisialisasi variabel global
unsigned long StartTime = 0;            // Waktu mulai penyiraman
unsigned long timeInterval = 60000;     // Interval waktu penyiraman (60 detik)
bool waterPinState ;             // Status pompa air (nyala/mati)

Automation AutomationStatus ;

void initAutomation() {
    pinMode(RELAY_WATER_PUMP, OUTPUT);
    Serial.println("Water pump relay 4 initialized !");
    digitalWrite(RELAY_WATER_PUMP, HIGH); // Matikan semua relay pada awalnya
    waterPinState = false;

}

void turnOnWaterPump() {
    // unsigned long currentMilliss = millis();
    
    waterPinState = true;

    digitalWrite(RELAY_WATER_PUMP, LOW); // Menghidupkan relay water pump
    Serial.println("Menghidupkan water pump");
    Serial.print("Current millis: ");
    Serial.println(millis());
    Serial.print("Start time: ");
    Serial.println(StartTime);

    StartTime = millis();;           // Waktu mulai

    AutomationStatus.waterPinStatus = waterPinState;
      bool tes; 
  tes = digitalRead(RELAY_WATER_PUMP);
  Serial.print("nilai readnya = " );
  Serial.println(tes);
  Serial.print("nilai waterpinstate from turn on = " );
  Serial.println(waterPinState);
}

void cekIntervalTime() {
    unsigned long currentMilliss = millis();
    // Serial.print("Cek interval - Current millis: ");
    // Serial.println(currentMilliss);
    if ((waterPinState) && (currentMilliss - StartTime >= timeInterval)) {
        Serial.println("Mematikan semua pompa");
        digitalWrite(RELAY_WATER_PUMP, HIGH);          // Matikan relay water pump
        waterPinState = false;
        AutomationStatus.waterPinStatus = waterPinState;
        Serial.print("nilai waterpinstate from cek = " );
        Serial.println(waterPinState);
    }

}
