// ************************************************************************
//
//       inttestPort2.c
//       Autor K.Wüst,  Nov. 19
//
//       Programm demonstriert, wie ein Interrupt an einem digitalen Port
//       aktiviert und mit einer Interrupt Service Routine behandelt wird
//
// ************************************************************************

#include  <msp430.h>

int j;
// Globale Variable, auf diese Variable kann in allen Programmteilen
// zugegriffen werden; über diese Variable kann das Hauptprogramm
// Information mit der Interrupt Service Routine austauschen

void main(void){
  WDTCTL = WDTPW + WDTHOLD;  // Stop  Watchdog Timer

  P1DIR = 0xFF;       // P1.0 - P1.3 ist Ausgang
  j = 0;              // Nach Start LED0 einschalten

  P2IE = BIT0;        // Port 2 Interrupt Enable an Leitung 0
  P2IES = BIT0;       // Interrupt Edge Select -> fallende Flanke
  
  __enable_interrupt();      // Interrupts global frei schalten
  while (1){
    P1OUT = (1<<j);         // Leitung j = HIGH
  }
}

// Interrupt Service Routine für Port 2
// wird jedesmal aufgerufen, wenn Interrupt von Port 2 kommt
#pragma vector=PORT2_VECTOR
__interrupt void Port2ISR (void){
volatile unsigned int i;
  j = (j+1) % 8 ;           // Nummer der LED erhöhen, und nach 7 wieder 0
  for (i=0; i<10000; i++);   // Warteschleife
  P2IFG=0;                          // Interupt ist bearbeitet, Interrupt-Flag-Register löschen!!
}
