#include <Arduino.h>

// --- COSTANTI E CONFIGURAZIONE ---
// Definiamo il numero del pin a cui è collegato il LED.
// Usiamo 'const' perché questo valore non cambierà mai.
const int LED_GPIO = D3; 

// Definiamo il tempo di attesa in millisecondi (1000 ms = 1 secondo)
const int TEMPO_ATTESA = 1000;

/**
 * La funzione setup() viene eseguita una sola volta all'avvio.
 * Serve per inizializzare l'hardware e le comunicazioni.
 */
void setup() {
  // Inizializza la comunicazione seriale a 115200 bit per secondo.
  // Serve per inviare messaggi dalla scheda al Monitor Seriale del computer.
  Serial.begin(115200);

  // Configura il pin del LED come USCITA (OUTPUT).
  // Questo permette alla scheda di inviare tensione (Volt) verso il LED.
  pinMode(LED_GPIO, OUTPUT);
  
  Serial.println("Sistema avviato correttamente.");
}

/**
 * La funzione loop() viene eseguita all'infinito, 
 * ricominciando non appena arriva all'ultima riga.
 */
void loop() {
  // 1. Accendiamo il LED portando il pin a livello logico ALTO (5V o 3.3V)
  digitalWrite(LED_GPIO, HIGH);  
  Serial.println("LED Acceso");
  
  // 2. Mettiamo in pausa il microcontrollore per il tempo stabilito
  delay(TEMPO_ATTESA); 

  // 3. Spegniamo il LED portando il pin a livello logico BASSO (0V / Massa)
  digitalWrite(LED_GPIO, LOW);   
  Serial.println("LED Spento");
  
  // 4. Mettiamo in pausa di nuovo prima di ricominciare il ciclo
  delay(TEMPO_ATTESA); 
}