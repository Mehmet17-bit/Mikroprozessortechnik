/**************************************************************************
  Datei blink1.c
  Ablauff�hig auf Hardware: MSP430-Education-Board mit MSP430F2274
  L�sst auf dem MSP430-Edu-Board eine LED blinken

  Kommentar zur Schaltung auf Board:
     P1.0 - P1.7              LED leuchtet wenn Ausgang=H (1)

   Autor  K.W�st, Stand Nov. 19
**************************************************************************/
  
#include <msp430.h>
#include <lcd_bib.c>        //die LCD Bibliothek ist verf�gbar
#include <lcd_bib.h>

// Funktions-Prototypen
void Warteschleife(unsigned long Anzahl);          // Software Warteschleife

int main(void) {

  WDTCTL = WDTPW + WDTHOLD;          // Watchdog timer anhalten

  // Hardware-Initialisierung
  P1DIR = 0xFF;           // Port 1 arbeitet mit allen Leitungen (P1.0-P1.7) als Ausgabeport
  P2DIR = 0;              // Port 2 ist verf�gbar

  unsigned char taste = 0x00;   // Tastenwert = hexa null
  int startwert = 0;        // Startwert = 0

  while(1)    // Endlosschleife
  {
      //P1OUT = P2IN;         // Test ob die Tasten funktionieren

      taste = ~P2IN;            // taste erh�lt den negierten Wert von Port 2

      if(taste & 0x01){         //F�r SW1 um 1 erh�hen
          startwert++;
          Warteschleife(25000);  //Warteschleife um Tastenprellung zu umgehen
      }

      if(taste & 0x02){         //F�r SW2 um 1 erniedrigen
          startwert--;
          Warteschleife(25000);  //Warteschleife um Tastenprellung zu umgehen
      }

      if(taste & 0x04){         //F�r SW3 verdoppeln
          startwert = startwert * 2;
          Warteschleife(25000);  //Warteschleife um Tastenprellung zu umgehen
      }

      if(taste & 0x20){         //F�r SW4 halbieren
          startwert = startwert / 2;
          Warteschleife(25000);  //Warteschleife um Tastenprellung zu umgehen
      }

      P1OUT = startwert;        //Ausgabe des ver�nderten Startwertes
      lcd_puts(startwert);
  } 
 
  return 0;    // Nur zur Sicherheit Statement wird aber niemals erreicht
}


void Warteschleife(unsigned long Anzahl){
volatile unsigned long i;
 for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterz�hlen
}
 
