#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_LED D2
#define NUM_LED 30

Adafruit_NeoPixel strip(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
    strip.begin();
    strip.show();
}

void loop() {
    for (int i = 0; i < NUM_LED; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 255));
    }
    strip.show();
    delay(1000);
}