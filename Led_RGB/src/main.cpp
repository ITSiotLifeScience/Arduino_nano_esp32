#include <Arduino.h>

// Definizione dei pin collegati ai tre colori del LED RGB.
// Ogni colore ha il suo pin dedicato.
// Il pin comune del LED va collegato a GND (catodo comune).
#define PIN_R D2   // Pin per il LED Rosso
#define PIN_G D3   // Pin per il LED Verde
#define PIN_B D4   // Pin per il LED Blu

// Funzione che imposta il colore del LED RGB.
// I valori r, g, b vanno da 0 a 255:
//   0   = spento
//   255 = luminosità massima
// Poiché il LED è a catodo comune, NON serve invertire la logica.
void setColor(uint8_t r, uint8_t g, uint8_t b) {
    analogWrite(PIN_R, r);  // Imposta intensità del rosso
    analogWrite(PIN_G, g);  // Imposta intensità del verde
    analogWrite(PIN_B, b);  // Imposta intensità del blu
}

void setup() {
    // Impostiamo i tre pin come uscite digitali.
    pinMode(PIN_R, OUTPUT);
    pinMode(PIN_G, OUTPUT);
    pinMode(PIN_B, OUTPUT);

    // All'avvio spegniamo il LED.
    setColor(0, 0, 0);
}

void loop() {
    // Accende il LED di ROSSO per 1 secondo
    setColor(255, 0, 0);
    delay(1000);

    // Accende il LED di VERDE per 1 secondo
    setColor(0, 255, 0);
    delay(1000);

    // Accende il LED di BLU per 1 secondo
    setColor(0, 0, 255);
    delay(1000);

    // Accende il LED di BIANCO (tutti i colori al massimo)
    setColor(255, 255, 255);
    delay(1000);
}