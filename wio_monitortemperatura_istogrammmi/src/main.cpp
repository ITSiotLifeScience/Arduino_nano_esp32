#include <Arduino.h>
#include"TFT_eSPI.h"

TFT_eSPI tft;

// Dimensioni dello schermo 320x240
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
void drawUI();
void drawBar(int x, float value, String label, uint16_t color, float maxVal);

void setup() {
    tft.begin();
    tft.setRotation(3); // Orientamento orizzontale
    tft.fillScreen(TFT_BLACK);
    
    drawUI();
}

void loop() {
    // Simulazione dati (sostituisci con i dati dei tuoi sensori)
    float temp = random(18, 35); 
    float hum = random(30, 80);

    // Disegna gli istogrammi
    drawBar(60, temp, "TEMP", TFT_RED, 40);      // Barra Temperatura
    drawBar(180, hum, "HUM", TFT_BLUE, 100);    // Barra Umidità

    delay(2000); // Aggiorna ogni 2 secondi
}

void drawUI() {
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.drawCentreString("Monitor Ambiente", SCREEN_WIDTH / 2, 10, 1);
    
    // Linea di base per il grafico
    tft.drawLine(20, 200, 300, 200, TFT_WHITE);
}

void drawBar(int x, float value, String label, uint16_t color, float maxVal) {
    int barWidth = 60;
    int maxBarHeight = 150;
    
    // Mappa il valore sull'altezza della barra
    int barHeight = map(value, 0, maxVal, 0, maxBarHeight);
    
    // Pulisce l'area precedente (disegna un rettangolo nero sopra la vecchia barra)
    tft.fillRect(x, 200 - maxBarHeight, barWidth, maxBarHeight, TFT_BLACK);
    
    // Disegna la barra attuale
    tft.fillRect(x, 200 - barHeight, barWidth, barHeight, color);
    
    // Scrive il valore e l'etichetta
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(1);
    tft.setCursor(x + 5, 210);
    tft.print(label);
    
    tft.setCursor(x + 5, 225);
    tft.print(value, 1); // Una cifra decimale
    if(label == "TEMP") tft.print(" C"); else tft.print(" %");
}
