#include <Arduino.h>
#include <Servo.h> // Include la libreria per gestire i servomotori

// Creazione di due oggetti "Servo" che rappresentano i motori fisici
Servo mio_servo;
Servo mio_servo2;

// Definizione dei pin PWM a cui sono collegati i cavi di segnale dei servo
int pin_servo = D3;
int pin_servo2 = D6;

/**
 * Funzione personalizzata per muovere un servo in modo fluido.
 * @param s: Riferimento all'oggetto Servo da muovere
 * @param pos: Angolo massimo di arrivo (0-180 gradi)
 */
void muoviservo(Servo &s, int pos){
      // Ciclo FOR per andare da 0 all'angolo desiderato (pos)
      for(int i = 0; i < pos; i++){
        s.write(i);      // Imposta l'angolo del servo a 'i'
        delay(50);       // Piccola pausa per controllare la velocità del movimento
      }
 
      // Ciclo FOR inverso per tornare dall'angolo 'pos' a 0
      for(int i = pos; i >= 0; i--){
        s.write(i);      // Imposta l'angolo
        delay(50);       // Pausa
      }  
}

void setup()
{
  // Collega (attach) l'oggetto servo al pin fisico corrispondente
  mio_servo.attach(pin_servo);
  mio_servo.write(0);           // Posiziona il servo a 0 gradi all'avvio
  
  mio_servo2.attach(pin_servo2);
  mio_servo2.write(0);          // Posiziona il secondo servo a 0 gradi
}

void loop()
{
  // Chiama la funzione muoviservo passando il primo motore e l'ampiezza di 180 gradi
  // Nota: il secondo motore (mio_servo2) in questo loop raggiunge l'ampiezza di 90 gradi
  muoviservo(mio_servo, 180);
  muoviservo(mio_servo2, 90);
    
  // Attesa di 100ms prima di ricominciare il ciclo
  delay(100);
}