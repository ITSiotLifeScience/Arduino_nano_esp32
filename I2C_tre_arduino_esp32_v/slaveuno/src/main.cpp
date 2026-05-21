#include <Arduino.h>
#include <Wire.h>

// Definisci l'indirizzo di questo specifico Target (es. 0x08 o 0x09)
#define TARGET_ADDRESS 0x08 

// Funzioni di callback per gli eventi I2C
void recvCallback(int numBytes);
void reqCallback();

void setup() {
  Serial.begin(115200);
  delay(2000);

  // Inizializza I2C come Target passando l'indirizzo
  // Nota: Su ESP32 è consigliato esplicitare i pin anche se sono quelli di default
  Wire.begin(TARGET_ADDRESS, A4, A5, 100000); 
  
  // Registra i gestori degli eventi
  Wire.onReceive(recvCallback);
  Wire.onRequest(reqCallback);

  Serial.printf("I2C Target iniziato all'indirizzo: 0x%02X\n", TARGET_ADDRESS);
}

void loop() {
  // Il loop rimane vuoto o gestisce altre logiche.
  // La comunicazione I2C avviene via Interrupt nelle callback.
  delay(1);
}

// Funzione eseguita quando il Master invia dati al Target
void recvCallback(int numBytes) {
  Serial.print("Ricevuti byte dal Master: ");
  while (Wire.available()) {
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
}

// Funzione eseguita quando il Master richiede dati al Target
void reqCallback() {
  // Rispondi al master (es. invia "OK!!" che sono esattamente 4 byte)
  Wire.write("OK!!"); 
}