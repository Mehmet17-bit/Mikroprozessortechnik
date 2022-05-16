/*      intprob2.c
        Uebungsdatei Stand Aug.20     */


#include <msp430.h>
#include <lcd_bib.h>
#include <lcd_bib.c>


// globale Variablen
unsigned char Zaehler;
unsigned char Zaehlerveraendert;

int main(void){
// Variablen definieren
  unsigned char s1[10];

  // Hardware initialisieren
  WDTCTL = WDTPW + WDTHOLD;   // Stoppt den Watchdog-Timer
  P1DIR=0xFF;                 // Alle 8 Leitungen von Port 1 sind digitale Ausgänge

  P2DIR=0x00;                   // auf Eingang gesetzt
  P2IE=0x27;                    //XIN,SW3,SW2,SW1-> Interrupt enable
  P2IES=0x27;                   //Interrupt Edge Select -> falende Flanke

   __enable_interrupt();      // enable general interrupt (Interrupts global frei schalten)

  // Meldung auf LCD
  lcd_init(16);
  //lcd_clear();
  lcd_puts("Zahl der IRQs:");
  P1OUT=0;

  // Anzeigeschleife
  Zaehlerveraendert=0;
  while(1){
      // okay
    if (Zaehlerveraendert) {
        //problem
      Zaehlerveraendert=0;
      uchar2string(s1, Zaehler);
      //problem
      lcd_gotoxy(1,1);
      //problem
      lcd_puts(s1);
      //problem
      //Zaehlerveraendert=0;
      //okay
      P1OUT=Zaehler;
      //okay
    }
    //okay
  }
}


// Port P2 interrupt service routine
// wird jedesmal aufgerufen, wenn Interrupt von P2 kommt
#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR (void)
{
  P2IFG=0;              //in dem Fall richtig, da sonst Impulse Verlust eventuell
  Zaehler++;             // Interrupts zaehlen
  Zaehlerveraendert=1;
}

