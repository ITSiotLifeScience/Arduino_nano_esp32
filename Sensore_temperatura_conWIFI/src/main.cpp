#include <Arduino.h>  // Libreria base del framework Arduino
#include <DHT.h>      // Libreria per gestire i sensori di temperatura e umidità DHT
#include <WiFi.h>     // Libreria per gestire la connessione WiFi (specifica per ESP32)

// --- CONFIGURAZIONE HARDWARE ---
#define DHTPIN D3      // Definiamo il pin digitale a cui è collegato il sensore DHT
#define DHTTYPE DHT11 // Specifichiamo il modello esatto del sensore (DHT11, DHT22, etc.)

// --- CREDENZIALI WIFI ---
// Inserisci qui il nome (SSID) e la password della tua rete domestica o hotspot
const char* ssid = "OPPO_MOB";
const char* password = "788d295e76aa";

// Inizializzazione dell'oggetto sensore DHT
DHT dht(DHTPIN, DHTTYPE);

// Variabile per gestire il tempo senza bloccare il processore (usata nel loop)
long lastMsg = 0;

// Dichiarazione della funzione (il codice vero e proprio è in fondo allo sketch)
void setup_wifi();

/**
 * SETUP: Questa funzione viene eseguita una sola volta all'accensione della scheda.
 */
void setup() {
  // Avvia la comunicazione seriale per visualizzare i dati sul PC (Monitor Seriale)
  Serial.begin(115200);
  
  // Avvia il sensore DHT
  dht.begin(); 
  
  // Chiama la funzione per connettersi alla rete WiFi definita sopra
  setup_wifi(); 
}

/**
 * LOOP: Questa funzione viene eseguita ciclicamente all'infinito.
 */
void loop() {
  // Acquisiamo il tempo corrente in millisecondi dall'accensione
  long now = millis();

  // Verifichiamo se è passato almeno 1 secondo (1000 ms) dall'ultimo invio.
  // Questo evita di sovraccaricare il sensore e la seriale con troppe letture.
  if (now - lastMsg > 1000) {
    lastMsg = now; // Aggiorniamo il timestamp dell'ultimo messaggio

    // Lettura dei dati dal sensore
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity(); 

    Serial.println("--- NUOVA LETTURA ---");

    // Controllo validità temperatura: isnan() significa "is Not a Number".
    // Se il sensore è scollegato o guasto, restituirebbe un errore; qui lo filtriamo.
    if (!isnan(temperature)) { 
      Serial.print("Temperatura: ");
      Serial.print(temperature);
      Serial.println(" °C");
    }

    // Stesso controllo per l'umidità
    if (!isnan(humidity)) { 
      Serial.print("Umidità: ");
      Serial.print(humidity);
      Serial.println("%");
    }
  }   
}

/**
 * FUNZIONE SUPPORTO: Gestisce la logica di connessione al WiFi
 */
void setup_wifi() {
  delay(1000);
  Serial.println();
  Serial.print("Tentativo di connessione a: ");
  Serial.println(ssid);

  // Inizia la procedura di autenticazione con il router
  WiFi.begin(ssid, password);

  // Ciclo "while": finché lo stato non è "WL_CONNECTED", continua a stampare puntini
  // Questa parte blocca l'esecuzione finché la connessione non va a buon fine.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Una volta usciti dal ciclo while, la connessione è riuscita
  Serial.println("");
  Serial.println("WiFi connesso!");
  Serial.print("Indirizzo IP assegnato: ");
  Serial.println(WiFi.localIP()); // Stampa l'IP della scheda nella rete locale

  delay(2000);
}
