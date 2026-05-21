#include <Arduino.h>
#include <Wire.h>

#define TARGET1_ADDRESS 0x08

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  // Inizializza come Master usando i pin nativi della Nano ESP32 (A4/A5)
  Wire.begin(); 
  Serial.println("I2C Master Pronto sui pin A4 (SDA) e A5 (SCL).");
}

void loop() {
  // --- ESEMPIO 1: Invio dati al Target 1 ---
  Wire.beginTransmission(TARGET1_ADDRESS);
  Wire.write("Hello T1"); 
  byte errore = Wire.endTransmission();

  if (errore == 0) {
    Serial.println("Dati inviati con successo al Target 1");
  } else {
    Serial.printf("Errore comunicazione Target 1: %d\n", errore);
  }

  delay(500);
/*
  // --- ESEMPIO 2: Richiesta dati dal Target 1 ---
  Wire.requestFrom(TARGET1_ADDRESS, 4);
  
  Serial.print("Risposta dal Target 1: ");
  if (Wire.available()) {
    while (Wire.available()) {
      char c = Wire.read();
      Serial.print(c);
    }
    Serial.println();
  } else {
    Serial.println("[Nessuna risposta]");
  }

  delay(2000); 
  */
}