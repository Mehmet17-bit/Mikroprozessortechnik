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

  BCSCTL1 = XT2OFF + RSEL0 + RSEL3;         // XT2OFF = 1, Rang Select beliebig ändern RSEL0,RSEL1,RSEL2, RSEL3
                                           //   -> Ändert die Taktfrequenz zwischen min. 100 kHz und max. 16000 kHz bei DCO = 3

  // Hardware-Initialisierung
  P1DIR = 0xFF;           // Port 1 arbeitet mit allen Leitungen (P1.0-P1.7) als Ausgabeport

  while(1)    // Endlosschleife
  {
    P1OUT=0x00;             // Ausgabevorgang: Alle LEDs dunkel
    Warteschleife(50000);   // In Warteschleife gehen
    P1OUT=0x01;             // Ausgabevorgang: LED an Port1.1 leuchtet
    Warteschleife(50000);   // In Warteschleife gehen
  }

  return 0;    // Nur zur Sicherheit Statement wird aber niemals erreicht
}


void Warteschleife(unsigned long Anzahl){
volatile unsigned long i;
for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterzählen
}
