/*
  C++ Online Compiler Programmiz
  Analisi didattica delle strutture fondamentali
*/

#include <iostream> // Libreria standard per input/output (cin, cout)
#include <cmath>    // Libreria per funzioni matematiche (come pow)

using namespace std; // Permette di usare cout/cin senza scrivere ogni volta std::

int main() {
    // --- DICHIARAZIONE VARIABILI ---
    int variabile;                       // Numero intero (senza decimali)
    const double miaCostante = 3.14555;  // Costante: il suo valore non può cambiare dopo l'inizializzazione
    
    bool continua = true;                // Booleano: può essere solo true (vero) o false (falso)
    char risposta;                       // Singolo carattere (es. 'A', 'N', 'Y')
    float variabileDecimale;             // Decimale a singola precisione
    double variabileDecimaleMoltoPrecisa; // Decimale a doppia precisione (più capiente di float)
    
    // --- INPUT E OPERAZIONI BASE ---
    cout << "Inserisci un valore intero \n";
    cin >> variabile;                    // Legge l'input dell'utente e lo salva in 'variabile'
    
    variabile = variabile + 1;           // Incremento: aggiunge 1 al valore attuale
    
    cout << "la variabile incrementata è: \n";
    cout << variabile << "\n";

    // --- STRUTTURA DI CONTROLLO (IF/ELSE) ---
    if (variabile > 20) {
        cout << "il numero è maggiore di 20 \n";
    } else {
        cout << "il valore è minore o uguale di 20 \n"; // Nota: include anche il caso == 20
    }
    
    // --- CICLO WHILE ---
    // Esegue il blocco finché la condizione è vera. Se è falsa all'inizio, non entra mai.
    cout << "ciclo while \n";
    while(continua == true) {
        cout << " Ho aggiunto uno alla mia variabile \n";
        variabile = variabile + 1;
        
        cout << "vuoi continuare?(Y,N)\n";
        cin >> risposta;
        
        if(risposta == 'N') {
            continua = false; // Cambia la condizione per uscire dal ciclo al prossimo controllo
        }
    }
    
    cout << "il valore della variabile ora è: " << variabile << "\n";

    // --- CICLO DO-WHILE ---
    // Simile al while, ma garantisce che il codice venga eseguito ALMENO una volta,
    // perché il controllo avviene alla fine.
    do {
        cout << " Ho aggiunto uno alla mia variabile \n";
        variabile = variabile + 1;
        cout << "vuoi continuare?(Y,N)\n";
        cin >> risposta;
        if(risposta == 'N') {
            continua = false;
        }
    } while(continua == true);

    cout << "il valore della variabile ora è: " << variabile;
    cout << "\n ciclo for\n";
      
    // --- CICLO FOR ---
    // Ideale quando sappiamo esattamente quante volte ripetere l'azione.
    // Inizializzazione (i=0); Condizione (i<10); Incremento (i++)
    for(int i = 0; i < 10; i++) {
        cout << " Ho aggiunto uno alla mia variabile \n" << variabile << "\n";
        variabile = variabile + 1;       
    }
    
    cout << "il valore della variabile ora è: " << variabile << "\n";
    
    // --- FUNZIONI MATEMATICHE ---
    // pow(base, esponente) calcola la potenza. Ritorna solitamente un double.
    int valoreelevatoPotenza = pow(variabile, 2); 
    cout << "Variabile al quadrato: " << valoreelevatoPotenza << "\n";

    return 0; // Segnala al sistema operativo che il programma è terminato correttamente
}