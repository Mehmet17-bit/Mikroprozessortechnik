/**************************************************************************
  Datei blink1.c
  Ablauffähig auf Hardware: MSP430-Education-Board mit MSP430F2274
  Lässt auf dem MSP430-Edu-Board eine LED blinken

  Kommentar zur Schaltung auf Board:
     P1.0 - P1.7              LED leuchtet wenn Ausgang=H (1)

   Autor  K.Wüst, Stand Nov. 19
**************************************************************************/

#include <msp430.h>
#include <lcd_bib.c>        //die LCD Bibliothek ist verfügbar
#include <lcd_bib.h>

// Funktions-Prototypen
void Warteschleife(unsigned long Anzahl);          // Software Warteschleife
unsigned char lcd[4];                 //Pointer für die LCD Ausgabe
unsigned char startwert = 0;        // Startwert = 0

int main(void) {

  WDTCTL = WDTPW + WDTHOLD;          // Watchdog timer anhalten

  // Hardware-Initialisierung
  P1DIR = 0xFF;           // Port 1 arbeitet mit allen Leitungen (P1.0-P1.7) als Ausgabeport
  P2DIR = 0;              // Port 2 ist verfügbar

  P2IE = BIT0 + BIT1 + BIT2 + BIT5;     //mögliche Interrupts für die Taster SW1-SW4 ist aktiviert
  P2IES = BIT0 + BIT1 + BIT2 + BIT5;    //über welche Leitung das Interrupt ausgelöst werden kann
  P1OUT = 0x00;                         //Port 1 Outpunt gleich null

  lcd_init(16);             //LCD initialisieren mit 16 Bit
  lcd_gotoxy(0,0);          //LCD Cursor Positieonierung auf Koordinate (0,0)

  __enable_interrupt();      // Interrupts global frei schalten
  while(1)    // Endlosschleife
  {
  return 0;    // Nur zur Sicherheit Statement wird aber niemals erreicht
  }
}
#pragma vector=PORT2_VECTOR
__interrupt void Port2ISR (void){


    if(P2IFG & BIT0){         //Für SW1 um 1 erhöhen
        startwert++;
    }

    if(P2IFG & BIT1){         //Für SW2 um 1 erniedrigen
        startwert--;
    }

    if(P2IFG & BIT2){         //Für SW3 verdoppeln
        startwert = startwert * 2;
    }

    if(P2IFG & BIT5){         //Für SW4 halbieren
        startwert = startwert / 2;
    }


    uchar2string(lcd,startwert);    //umkonvertierung
    lcd_gotoxy(0,0);
    lcd_puts(lcd);              //LCD Ausgabe
    P1OUT = startwert;        //Ausgabe des veränderten Startwertes
    Warteschleife(25000);       //Warteschleife zwischen den Aktionen
  P2IFG=0;                          // Interupt ist bearbeitet, Interrupt-Flag-Register löschen!!
}

void Warteschleife(unsigned long Anzahl){
volatile unsigned long i;
 for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterzählen
}
 
