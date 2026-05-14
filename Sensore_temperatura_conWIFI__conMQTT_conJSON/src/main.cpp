#include <Arduino.h>

// Importiamo le librerie necessarie: sensore di temperatura DHT, WiFi, MQTT e gestione JSON
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Definiamo il pin a cui è collegato il sensore DHT11
#define DHTPIN 3
#define DHTTYPE DHT11

// Inserisci qui le tue credenziali per la rete WiFi
const char* ssid = "OPPO_MOB";
const char* password = "788d295e76aa";

// Impostiamo l'indirizzo del server MQTT (Broker) e la porta utilizzata
// const char* mqtt_server = "test.mosquitto.org";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// Definiamo l'identificativo del sensore e il "topic" (argomento) MQTT
const char* sensor = "s001";
const char* mqtt_topic = "its_biotecnologie_dati";

char MQTT_CLIENT[18];  // Buffer per memorizzare il nome univoco del client MQTT
 
// Creiamo gli oggetti per la connessione di rete e il client MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Creiamo l'oggetto per gestire il sensore DHT
DHT dht(DHTPIN, DHTTYPE);

long lastMsg = 0; // Variabile per gestire l'invio temporizzato dei messaggi

// Dichiarazione delle funzioni (prototipi)
void setup_wifi();
void reconnect();

void setup() {
  Serial.begin(9600); // Inizializziamo la comunicazione seriale per il debug
  dht.begin();        // Inizializziamo il sensore DHT 

  setup_wifi();       // Avviamo la connessione WiFi
  
  // Configuriamo il server MQTT
  client.setServer(mqtt_server, mqtt_port); 
}

void loop() {
  // Se perdiamo la connessione al broker MQTT, proviamo a riconnetterci
  if (!client.connected())
  {
    reconnect();
  }
  
  // Questa funzione mantiene attiva la comunicazione con il broker (heartbeat)
  client.loop();

  // Verifichiamo se sono passati almeno 5 secondi dall'ultimo invio (5000 ms)
  long now = millis();
  if (now - lastMsg > 5000)
  {
    lastMsg = now;

    // Lettura dei valori di temperatura e umidità dal sensore
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Creiamo un documento JSON per organizzare i dati
    StaticJsonDocument<200> doc;
    doc["sensor"] = sensor;

    // Verifichiamo che la lettura sia valida (isnan controlla se il valore è "Not A Number")
    if (!isnan(temperature)) { 
        
        // Aggiungiamo i dati letti al documento JSON
        doc["temperature"] = temperature;
        doc["humidity"] = humidity;

        // Serializzazione: trasformiamo l'oggetto JSON in una stringa di testo
        char jsonBuffer[512];
        serializeJson(doc, jsonBuffer);

        // Stampiamo il JSON sul monitor seriale per verifica
        Serial.print("Dati inviati: ");
        Serial.println(jsonBuffer);

        // Pubblichiamo il messaggio JSON sul topic MQTT definito
        client.publish(mqtt_topic, jsonBuffer);
    } else {
        Serial.println("Errore nella lettura dal sensore DHT!");
    }
  }
}

// Funzione per stabilire la connessione alla rete WiFi
void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connessione a ");
  Serial.println(ssid);

  // Avviamo il tentativo di connessione
  WiFi.begin(ssid, password);

  // Attendiamo finché non siamo connessi correttamente
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connesso!");
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());

  // Generiamo un ID univoco per il client MQTT usando l'indirizzo MAC della scheda
  WiFi.macAddress().toCharArray(MQTT_CLIENT, sizeof(MQTT_CLIENT));
  Serial.print("Client ID MQTT: ");
  Serial.println(MQTT_CLIENT);
}

// Funzione per gestire la riconnessione al broker MQTT in caso di caduta
void reconnect()
{
  // Ciclo finché non viene stabilita la connessione
  while (!client.connected())
  {
    Serial.print("Tentativo di connessione MQTT...");
    
    // Proviamo a connetterci usando l'ID univoco creato nel setup_wifi
    if (client.connect(MQTT_CLIENT))
    {
      Serial.println("connesso!");
      // Una volta connessi, ci iscriviamo al topic per ricevere eventuali comandi
      client.subscribe(mqtt_topic);
    }
    else
    {
      // Se fallisce, stampiamo il codice errore e riproviamo dopo 1 secondo
      Serial.print("fallito, rc=");
      Serial.print(client.state());
      Serial.println(" riprovo tra 1 secondo");
      delay(1000);    
    }
  }
}
