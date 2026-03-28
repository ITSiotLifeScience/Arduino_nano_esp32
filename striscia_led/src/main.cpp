#include <Arduino.h>
#include <Adafruit_NeoPixel.h> // Importa la libreria per gestire i LED WS2812B (NeoPixel)

#define PIN_LED D2   // Definisce il pin di controllo (D2 su schede tipo ESP8266/NodeMCU)
#define NUM_LED 30   // Numero totale di LED nella tua striscia

// Crea l'oggetto "striscia" configurando numero di LED, pin e tipo di segnale (GRB a 800Khz)
Adafruit_NeoPixel striscia(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
    striscia.begin(); // Inizializza la comunicazione con la striscia
    striscia.show();  // Spegne tutti i LED all'avvio (invia uno stato "vuoto")
}

void loop() {
    // Inizia un ciclo che conta da 0 a 29 (per ognuno dei 30 LED)
    for (int i = 0; i < NUM_LED; i++) {
        
        striscia.clear(); // Spegne tutti i LED nel buffer (per far sì che se ne accenda solo uno alla volta)
        
        // Imposta il colore del LED in posizione "i" (i parametri sono: Rosso, Verde, Blu)
        // In questo caso: 0 Rosso, 0 Verde, 255 Blu (Blu puro)
        striscia.setPixelColor(i, striscia.Color(0, 0, 255));
        
        striscia.show();  // Invia il comando alla striscia fisica per aggiornare i colori
        
        delay(200);       // Pausa di 200ms: determina la velocità del movimento
    }
    // Una volta finito il ciclo (arrivato all'ultimo LED), il loop ricomincia da capo
}