#include <Arduino.h>

// Definizione dei Pin
const int trigPin = D2;
const int echoPin = D3;
const int buzzerPin = D4; // Pin per il Buzzer

// Variabili per il calcolo
long durata;
float distanza;

// Soglia di attivazione (in cm)
const int sogliaAllarme = 30; 

void setup() {
  Serial.begin(115200);
  
  // Impostazione dei pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT); // Il buzzer è un output
  
  Serial.println("Sistema avviato con Buzzer");
}

void loop() {
  // 1. Invio impulso
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 2. Lettura eco
  durata = pulseIn(echoPin, HIGH);

  // 3. Calcolo distanza
  distanza = (durata * 0.0343) / 2;

  // 4. Logica del Buzzer e Stampa
  if (distanza > 0 && distanza <= sogliaAllarme) {
    // Più sei vicino, più il suono è acuto (frequenza alta)
    // Mappiamo la distanza (2-30cm) su una frequenza (1000Hz-200Hz)
    int frequenza = map(distanza, 2, sogliaAllarme, 1000, 200);
    tone(buzzerPin, frequenza); 
    
    Serial.print("ALLARME! Distanza: ");
  } else {
    noTone(buzzerPin); // Spegne il suono se siamo fuori soglia
    Serial.print("Distanza: ");
  }

  if (distanza >= 400 || distanza <= 2) {
    Serial.println("Fuori portata");
  } else {
    Serial.print(distanza);
    Serial.println(" cm");
  }

  delay(100); // Ridotto il delay per rendere il buzzer più reattivo
}