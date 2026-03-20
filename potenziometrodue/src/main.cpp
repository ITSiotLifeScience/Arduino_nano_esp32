#include <Arduino.h>

// --- Definizione dei Pin ---
const int ledPin = D3;    // Pin che supporta il PWM (Pulse Width Modulation)
const int potPin = A0;    // Pin analogico per la lettura del potenziometro

// --- Variabili di appoggio ---
int lettura = 0;          // Memorizza il valore grezzo (0-4095)
int luminosita;           // Memorizza il valore convertito per il LED (0-255)

void setup() {
  // Configura il LED come uscita
  pinMode(ledPin, OUTPUT);
  // Configura il potenziometro come ingresso
  pinMode(potPin, INPUT);

  // NOTA: Su Arduino Nano ESP32, la risoluzione predefinita di analogRead è 12 bit.
  // Questo significa che i valori letti vanno da 0 a 4095, non più 0-1023.
  
  // Inizializza il monitor seriale
  Serial.begin(115200);
}

void loop() {
  // 1. LETTURA ANALOGICA (Risoluzione 12-bit)
  // Legge il valore di tensione sul pin A0. 
  // 0V -> 0 | 3.3V -> 4095
  lettura = analogRead(potPin);

  // 2. MAPPATURA (Conversione di scala)
  // Trasforma il range della lettura (0-4095) nel range del PWM (0-255).
  // Questo passaggio è fondamentale perché analogWrite accetta valori max di 8 bit (255).
  luminosita = map(lettura, 0, 4095, 0, 255);

  // 3. DEBUG SERIALE
  // Mostra i valori sul computer per verificare che la conversione sia corretta
  Serial.print("Pot: ");      
  Serial.print(lettura);      
  Serial.print("  PWM: ");    
  Serial.println(luminosita); 
  
  // 4. CONTROLLO LUMINOSITÀ
  // Applica il segnale PWM al LED. Più alto è il valore, più il LED appare luminoso.
  analogWrite(ledPin, luminosita);
  
  // Breve pausa per evitare di saturare la comunicazione seriale
  delay(100);
}