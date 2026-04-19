#include <Arduino.h>     // Libreria base del framework Arduino
#include <DHT.h>         // Libreria per gestire i sensori di temperatura e umidità DHT
#include <WiFi.h>        // Libreria per gestire la connessione WiFi (specifica per ESP32)
#include <PubSubClient.h> // Libreria per il protocollo MQTT (Publish/Subscribe)

// --- CONFIGURAZIONE HARDWARE ---
#define DHTPIN D3      // Definiamo il pin digitale a cui è collegato il sensore DHT
#define DHTTYPE DHT11  // Specifichiamo il modello esatto del sensore (DHT11, DHT22, etc.)

// --- CREDENZIALI WIFI ---
// const char* indica un puntatore a una stringa costante (non modificabile in runtime)
const char* ssid = "OPPO_MOB";
const char* password = "788d295e76aa";

// --- CONFIGURAZIONE MQTT ---
WiFiClient espClient;           // Crea un client che può connettersi a un indirizzo IP
PubSubClient client(espClient); // Inizializza il client MQTT usando il client WiFi sopra
const char* mqtt_server = "broker.hivemq.com"; // Indirizzo del broker pubblico
const int mqtt_port = 1883;                    // Porta standard MQTT (non criptata)
const char* mqtt_topic = "its_biotecnologie_dati"; // Il "canale" su cui pubblicheremo i dati

// Definiamo l'ID del client come array di char (modificabile e sicuro in memoria)
// Ricorda: il terminatore '\0' viene aggiunto automaticamente dal compilatore
char MQTT_CLIENT[18] = "sensore_uno";

// Inizializzazione dell'oggetto sensore DHT (passiamo pin e tipo)
DHT dht(DHTPIN, DHTTYPE);

// Variabile 'long' per memorizzare il tempo (millisecondi). 
// Usiamo long perché il valore di millis() cresce molto rapidamente.
long lastMsg = 0;

// Prototipi delle funzioni: informano il compilatore che queste funzioni esistono
void setup_wifi();
void reconnect();

/**
 * SETUP: Eseguita una sola volta all'avvio.
 */
void setup() {
  // Inizializza la comunicazione seriale a 115200 baud (velocità bit/secondo)
  Serial.begin(115200);
  
  // Avvia la logica interna del sensore DHT
  dht.begin(); 
  
  // Esegue la connessione al WiFi
  setup_wifi(); 

  // Configura i dettagli del server MQTT
  client.setServer(mqtt_server, mqtt_port); 
}

/**
 * LOOP: Eseguita ciclicamente. Controlla connessione e legge i sensori.
 */
void loop() {
  // Se il client MQTT perde la connessione, prova a riconnettersi
  if (!client.connected()) {
    reconnect();
  }
  
  // Gestisce i pacchetti MQTT in arrivo e mantiene vivo il "keep-alive" con il broker
  client.loop();

  // Acquisiamo il tempo attuale (millisecondi da quando la scheda è accesa)
  long now = millis();

  // Tecnica del "Blink Without Delay": esegue il codice ogni 1000ms senza bloccare il processore
  if (now - lastMsg > 1000) {
    lastMsg = now; 

    // Lettura dei dati (restituiscono un tipo 'float' per avere i decimali)
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity(); 

    Serial.println("--- NUOVA LETTURA ---");

    // Array di char (buffer) per convertire i numeri in testo prima dell'invio MQTT
    char tempString[8];
    char tempHumidity[8];

    // Controllo validità: se il sensore non risponde, la funzione restituisce NaN (Not a Number)
    if (!isnan(temperature)) { 
      Serial.print("Temperatura: ");
      Serial.print(temperature);
      Serial.println(" °C");

      // dtostrf(valore, larghezza_min, precisione, destinazione)
      // Converte il float 'temperature' in una stringa di caratteri dentro 'tempString'
      dtostrf(temperature, 1, 2, tempString);
      
      // Invia la stringa al broker sul topic specificato
      client.publish(mqtt_topic, tempString);
    }

    if (!isnan(humidity)) { 
      Serial.print("Umidità: ");
      Serial.print(humidity);
      Serial.println("%");

      // Conversione e pubblicazione dell'umidità
      dtostrf(humidity, 1, 2, tempHumidity);      
      client.publish(mqtt_topic, tempHumidity);
    }
  }   
}

/**
 * Gestisce la connessione fisica alla rete WiFi locale.
 */
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connessione a: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Rimane in questo ciclo finché lo stato non diventa WL_CONNECTED
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connesso!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP()); 
}

/**
 * Gestisce la logica di protocollo per connettersi (o riconnettersi) al Broker MQTT.
 */
void reconnect() {
  // Ciclo finché non siamo di nuovo online sul broker
  while (!client.connected()) {
    Serial.print("Tentativo connessione MQTT...");
    
    // Prova a connettersi usando l'ID univoco definito sopra
    if (client.connect(MQTT_CLIENT)) {
      Serial.println("CONNESSO");
      // Una volta connessi, ci iscriviamo al topic per ricevere eventuali comandi
      client.subscribe(mqtt_topic);
    } else {
      // Se fallisce, stampa il codice d'errore (state) e aspetta
      Serial.print("FALLITO, rc=");
      Serial.print(client.state());
      Serial.println(" nuovo tentativo tra 5 secondi");
      // Aspetta 5 secondi prima di riprovare per non intasare la rete
      delay(5000);    
    }
  }
}