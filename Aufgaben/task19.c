// ****************************************************************************
//
//       intprob1.c
//       Uebungsdatei Stand Aug.20
//
// ****************************************************************************

#include  <msp430.h>
#include <lcd_bib.h>
#include <lcd_bib.c>

unsigned int Zaehler;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;  // Stop  Watchdog Timer

  TACTL = TASSEL_1 + TACLR;  // Beschreiben des TimerA-Controlregisters:
                             //   - TimerA Source Select = 0 (Eingangstakt ist AClock)
                             //   - Clear TimerA-Register    (Zählregister auf 0 setzen)
                             // Timer startet noch nicht

  TACCTL0 = CCIE;            // Capture/Compare-Unit0 Control-Register beschreiben:
                             //   - Interrupt-Auslösung durch Capture/Compare-Unit0 freischalten (CCR0)
  TACCR0 = 0x0500;           // Capture/Compare-Register 0 mit Zählwert belegen

  P1DIR = 0x01;             // P1.0 ist Ausgang

  TACTL |= MC_1;             // Start Timer_A im up mode (Mode Control = 1)

  Zaehler=0;
  lcd_init(16);
  //lcd_clear();

  lcd_gotoxy(0,0);
  lcd_puts("Zaehlerstand ist");
  __enable_interrupt();

  /*
   * Codestück unter __enable_interrupt(); ist unreachable
   */
  lcd_gotoxy(0,1);
  lcd_puts("aktuell:");

  while (1){
    }
}

/*
 * Die ISR benötigt viel Zeit in der LCD Ausgabe und es kommt zu einem "Stau"
 * Deshalb kann der TACCR0 jede beliebigen Wert annehmen, jedoch eine Änderung
 * der Sekunden bleibt unverändert
 */
// Timer A0 interrupt service routine
// wird jedesmal aufgerufen, wenn Interrupt CCR0 von TimerA kommt
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void)
{  unsigned char s[20];
  Zaehler++;          //  Zaehler inkrementieren
  uint2string(s, Zaehler);
  lcd_gotoxy(10,1);
  lcd_puts(s);
}
