#include <Arduino.h>     // Libreria base del framework Arduino
#include <PubSubClient.h> // Libreria per il protocollo MQTT (Publish/Subscribe)
#include "TFT_eSPI.h"
#include <rpcWiFi.h>
#include <ArduinoJson.h>

// --- CREDENZIALI WIFI ---
// const char* indica un puntatore a una stringa costante (non modificabile in runtime)
const char* ssid = "OPPO_MOB";
const char* password = "788d295e76aa";

TFT_eSPI tft;
// --- CONFIGURAZIONE MQTT ---

WiFiClient espClient;           // Crea un client che puÃƒÂ² connettersi a un indirizzo IP
PubSubClient client(espClient); // Inizializza il client MQTT usando il client WiFi sopra
const char* mqtt_server = "broker.hivemq.com"; // Indirizzo del broker pubblico
const int mqtt_port = 1883;                    // Porta standard MQTT (non criptata)
const char* mqtt_topic = "its_biotecnologie_dati"; // Il "canale" su cui pubblicheremo i dati

// Definiamo l'ID del client come array di char (modificabile e sicuro in memoria)
// Ricorda: il terminatore '\0' viene aggiunto automaticamente dal compilatore
char MQTT_CLIENT[18] = "wio_uno";



// Variabile 'long' per memorizzare il tempo (millisecondi). 
// Usiamo long perchÃƒÂ© il valore di millis() cresce molto rapidamente.
long lastMsg = 0;

// Prototipi delle funzioni: informano il compilatore che queste funzioni esistono
void setup_wifi();
void reconnect();
void callback(char* , byte* , unsigned int );

/**
 * SETUP: Eseguita una sola volta all'avvio.
 */
void setup() {
  // Inizializza la comunicazione seriale a 115200 baud (velocitÃƒÂ  bit/secondo)
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(3); // Ruota lo schermo in modalitÃƒÂ  landscape (orizzontale)
  
  // Sfondo blu e testo bianco
  tft.fillScreen(TFT_BLUE);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  
  // Scrittura al centro dello schermo
  tft.drawCentreString("Wio Terminal", 160, 100, 1);
  tft.drawCentreString("Lettura dati sensori", 160, 140, 1);
  
  // Esegue la connessione al WiFi
  setup_wifi(); 

  // Configura i dettagli del server MQTT
  client.setServer(mqtt_server, mqtt_port); 
  client.setCallback(callback);
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


}

/**
 * Gestisce la connessione fisica alla rete WiFi locale.
 */
void setup_wifi() {
  delay(10);
  // stampo sul display
  tft.fillScreen(TFT_BLUE);
  tft.setCursor(0, 0);
  tft.print("Connessione a: ");
  tft.println(ssid);

  WiFi.begin(ssid, password);

  // Rimane in questo ciclo finchÃƒÂ© lo stato non diventa WL_CONNECTED
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.print(".");
  }

  tft.println("\nWiFi Connesso!");
  tft.print("IP: ");
  tft.println(WiFi.localIP());
  delay(2000);
}

/**
 * Gestisce la logica di protocollo per connettersi (o riconnettersi) al Broker MQTT.
 */
void reconnect() {
  // Ciclo finchÃƒÂ© non siamo di nuovo online sul broker
  while (!client.connected()) {
      tft.fillScreen(TFT_RED);
      tft.setCursor(0, 0);
      tft.print("Connessione MQTT...");
    
    // Prova a connettersi usando l'ID univoco definito sopra
    if (client.connect(MQTT_CLIENT)) {
      tft.println("Connesso!");
      // Una volta connessi, ci iscriviamo al topic per ricevere eventuali comandi
      client.subscribe(mqtt_topic);
    } else {
      // Se fallisce, stampa il codice d'errore (state) e aspetta
      tft.print("Fallito, rc=");
      tft.print(client.state());
      tft.println(" riprovo tra 5s");
      // Aspetta 5 secondi prima di riprovare per non intasare la rete
      delay(5000);    
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
    // 1. Pulizia dello schermo e intestazione
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    tft.setTextColor(TFT_GREEN);
    tft.println("Dati Ricevuti:");
    tft.println("----------------");
    
    // 2. Creazione del documento JSON per la decodifica
    // Usiamo DynamicJsonDocument o StaticJsonDocument a seconda della versione della libreria
    StaticJsonDocument<200> doc;

    // 3. Deserializzazione del payload ricevuto
    DeserializationError error = deserializeJson(doc, payload, length);

    // Controllo se la decodifica è andata a buon fine
    if (error) {
        tft.setTextColor(TFT_RED);
        tft.print("Errore JSON: ");
        tft.println(error.c_str());
        return;
    }

    // 4. Estrazione dei dati dal JSON
    // Usiamo i nomi delle chiavi che hai definito nell'invio ("sensor", "temperature", "humidity")
    const char* sensorName = doc["sensor"];
    float temp = doc["temperature"];
    float hum = doc["humidity"];

    // 5. Visualizzazione formattata sul display TFT
    tft.setTextColor(TFT_YELLOW);
    tft.print("Sensore: ");
    tft.setTextColor(TFT_WHITE);
    tft.println(sensorName);

    tft.println(); // Riga vuota

    tft.setTextColor(TFT_CYAN);
    tft.print("Temp: ");
    tft.setTextSize(3);
    tft.setTextColor(TFT_WHITE);
    tft.print(temp, 1); // 1 cifra decimale
    tft.println(" C");

    tft.setTextSize(2);
    tft.setTextColor(TFT_MAGENTA);
    tft.print("Umid: ");
    tft.setTextSize(3);
    tft.setTextColor(TFT_WHITE);
    tft.print(hum, 0); // 0 cifre decimali
    tft.println(" %");

    tft.setTextSize(2); // Ripristina dimensione base
}