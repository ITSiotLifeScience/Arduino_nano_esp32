#include <Arduino.h>
#include <DHT.h> // Importa la libreria per i sensori di temperatura e umidità

#define DHTPIN 3     // Definisce il pin digitale a cui è collegato il sensore
#define DHTTYPE DHT11 // Specifica il modello del sensore (DHT11, più comune del DHT22)

// Crea l'istanza del sensore chiamata "mioSensore" con i parametri definiti sopra
DHT mioSensore(DHTPIN, DHTTYPE);

// Variabile per memorizzare l'ultimo momento in cui abbiamo letto i dati
long int prima = 0;

void setup() {
  mioSensore.begin();      // Inizializza il sensore DHT
  Serial.begin(115200);    // Avvia la comunicazione seriale (imposta 115200 sul monitor seriale)
  delay(1000);             // Piccola attesa per stabilizzare il sistema all'avvio
}

void loop() {
  // Memorizza il tempo corrente in millisecondi dall'avvio della scheda
  long int ora = millis();

  // Controlla se sono passati più di 2000 millisecondi (2 secondi) dall'ultima lettura
  // Questa tecnica "non bloccante" permette ad Arduino di fare altro nel frattempo
  if (ora - prima > 2000) {
    prima = ora; // Aggiorna il timestamp dell'ultima lettura effettuata

    // Legge i dati dal sensore e li salva in variabili di tipo float (numeri con virgola)
    float temperatura = mioSensore.readTemperature();
    float umidita = mioSensore.readHumidity();

    // Invia i risultati al Monitor Seriale del computer
    Serial.println("il valore della temperatura e' ");
    Serial.println(temperatura);
    
    Serial.println("il valore dell'umidita e' ");
    Serial.println(umidita);
  }
}

