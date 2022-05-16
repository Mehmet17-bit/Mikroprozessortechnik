// ************************************************************************
//
//       IntTestPort2LPM.c
//       Autor K.Wüst , Stand Okt. 20
//
//       Zeigt wie der Prozessor in den Low Power Mode versetzt wird und
//       trotzdem noch Interrupts (von Port 2) abarbeitet
//
// ************************************************************************

#include  <msp430.h>

 int j;   // Globale Variable; auf diese Variable kann in allen
          // Programmteilen zugegriffen werden
          // über diese Variable kann das Hauptprogramm Information
          // mit der Interrupt Service Routine austauschen

void main(void){
  WDTCTL = WDTPW + WDTHOLD;  // Stop  Watchdog Timer

  P1DIR = 0xFF;       // P1.0 - P1.3 ist Ausgang
  j = 0;              // Nach Start
  P1OUT = 1;          // LED0 einschalten

  P2IE = BIT0;        // Port 2 Interrupt Enable an Leitung 0
  P2IES = BIT0;       // Interrupt Edge Select -> fallende Flanke

  __enable_interrupt();      // Interrupts global frei schalten

  // CPU in low Power Mode versetzen; bedeutet CPU bleibt stehen
  __low_power_mode_4();      // low power mode 4:
}


// Interrupt Service Routine für Port 2
// wird jedesmal aufgerufen, wenn Interrupt von Port 2 kommt
#pragma vector=PORT2_VECTOR
__interrupt void Port2ISR (void){
volatile unsigned int i;
  j = (j+1) % 8 ;     // Nummer der LED erhöhen, und nach 7 wieder 0
  P1OUT = (1<<j);     // zugehörige LED einschalten
  for (i=0; i<10000; i++);   // Warteschleife
  P2IFG=0;            // Interupt bearbeitet, Interrupt-Flag-Register löschen
}
