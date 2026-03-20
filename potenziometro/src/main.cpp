#include <Arduino.h>

/* Progetto: Blink variabile con Potenziometro
   Scheda: Arduino Nano ESP32 (o compatibili)
*/

// --- Definizione dei Pin ---
// Usiamo 'const' perché i numeri dei pin non cambieranno durante l'esecuzione
const int ledPin = D3;   // Pin digitale a cui è collegato il LED
const int potPin = A0;   // Pin analogico a cui è collegato il cursore del potenziometro

// Variabile per memorizzare il valore letto (sarà compreso tra 0 e 1023 o 4095)
int durata = 0;

void setup() {
  // Configura il pin del LED come uscita per poter inviare corrente
  pinMode(ledPin, OUTPUT);
  
  // Configura il pin del potenziometro come ingresso per leggere la tensione
  pinMode(potPin, INPUT);
  
  // Inizializza la comunicazione Serial a 115200 baud per il monitoraggio a PC
  Serial.begin(115200);
}

void loop() {
  // 1. LETTURA ANALOGICA
  // Legge la tensione sul pin A0 e la converte in un numero intero.
  // Su molte schede il valore va da 0 (0V) a 1023 (3.3V o 5V).
  durata = analogRead(potPin);

  // 2. AZIONE (Blink)
  // Accende il LED
  digitalWrite(ledPin, HIGH);
  // Aspetta un numero di millisecondi pari al valore letto dal potenziometro
  delay(durata);
  
  // Spegne il LED
  digitalWrite(ledPin, LOW);
  // Aspetta lo stesso intervallo di tempo
  delay(durata);

  // 3. DEBUG
  // Invia il valore della variabile 'durata' al computer tramite il cavo USB
  // Utile per capire se il potenziometro sta funzionando correttamente
  Serial.println(durata); 
}