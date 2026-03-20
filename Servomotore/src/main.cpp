#include <Arduino.h>
#include <Servo.h> // Include la libreria per il controllo dei servomotori

// Creazione dell'oggetto 'mio_servo' per gestire il componente fisico
Servo mio_servo;

// Definizione del pin di collegamento (D3 su Arduino Nano ESP32)
int pin_servo = D3;

void setup()
{
  // Associa l'oggetto mio_servo al pin fisico D3
  mio_servo.attach(pin_servo);
  
  // Inizializza la comunicazione seriale per il debug
  Serial.begin(115200);
  
  // Messaggio di avvio (attenzione: il commento dice 0 ma il comando imposta 90)
  Serial.println("posizione iniziale: 90 gradi");
  
  // Porta il servo a 90 gradi (posizione centrale standard) all'accensione
  mio_servo.write(90);
}

void loop()
{
  // 1. Sposta il braccetto del servo a 0 gradi
  mio_servo.write(0);
  // Attende 3 secondi (3000 millisecondi) nella posizione 0
  delay(3000);
  
  // 2. Sposta il servo a 45 gradi
  Serial.println("posizione 45");
  mio_servo.write(45);
  // Resta fermo per 3 secondi
  delay(3000); 
  
  // 3. Sposta il servo a 90 gradi
  Serial.println("posizione 90");
  mio_servo.write(90);
  // Resta fermo per 3 secondi prima di ricominciare il loop da 0 gradi
  delay(3000);   
}