/**************************************************************************
  Datei blink1.c
  Ablauffähig auf Hardware: MSP430-Education-Board mit MSP430F2274
  Lässt auf dem MSP430-Edu-Board eine LED blinken

  Kommentar zur Schaltung auf Board:
     P1.0 - P1.7              LED leuchtet wenn Ausgang=H (1)

   Autor  K.Wüst, Stand Nov. 19
**************************************************************************/
  
#include <msp430.h>

// Funktions-Prototypen
void Warteschleife(unsigned long Anzahl);          // Software Warteschleife

int main(void) {

  WDTCTL = WDTPW + WDTHOLD;          // Watchdog timer anhalten

  // Hardware-Initialisierung
  P1DIR = 0xFF;           // Port 1 arbeitet mit allen Leitungen (P1.0-P1.7) als Ausgabeport

  while(1)    // Endlosschleife
  {
    int i = 1;
    while(i <= 128){           //lässt Diode von 1.1 - 1.7 laufen
        P1OUT = i;            // Ausgabevorgang: LED an Port1.x leuchtet
        Warteschleife(50000/2);   // In Warteschleife gehen und doppelte Geschwindigkeit
        i = i * 2;                //rechnet das i entsprechend für Binary (1, 2, 4,..., 128)
    }

    int j = 64;
    while(j >= 2){             //Lässt Diode von 1.6 - 1.2 laufen
        P1OUT = j;              //Ausgabevorgang: LED an Port 1.x leuchtet
        Warteschleife(50000/2); // In Warteschleife gehen und doppelte Geschwindigkeit
        j = j / 2;               //rechnet das j entsprechend für Binary (64,32,..,2)
    }
  } 


  return 0;    // Nur zur Sicherheit Statement wird aber niemals erreicht
}


void Warteschleife(unsigned long Anzahl){
volatile unsigned long i;
 for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterzählen
}
 
