// ****************************************************************************
//
//       intprob3.c
//       Uebungsdatei Nov. 19
//
// ****************************************************************************

#include  <msp430.h>
#include <lcd_bib.h>
#include <lcd_bib.c>

int Zaehler, oldZaehler;

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;  // Stop  Watchdog Timer

  TACCTL0 = CCIE;            // Capture/Compare-Unit0 Control-Register beschreiben:
                             //   - Interrupt-Auslösung durch Capture/Compare-Unit0 freischalten (CCR0)
  TACCR0 = 0x0005;           // Capture/Compare-Register 0 mit Zählwert belegen

  P1DIR = 0x01;             // P1.0 ist Ausgang

  TACTL = TASSEL_1 + TACLR + MC_1;  // Beschreiben des TimerA-Controlregisters:
                             //   - TimerA Source Select = 1 (Eingangstakt ist AClock)
                             //   - Clear TimerA-Register    (Zählregister auf 0 setzen)
                             //   - Start Timer_A im up mode (Mode Control = 1)

  __enable_interrupt();      // enable general interrupt (Interrupts global frei schalten)

  Zaehler=0;
  oldZaehler=0;
  lcd_init(16);
  //lcd_clear();
  lcd_puts("Einfach abwarten");

  while (1){
    if (Zaehler>oldZaehler) {
        oldZaehler = Zaehler;
      }
      if ((Zaehler>(oldZaehler+100))||(Zaehler<(oldZaehler-100))) {
      TACTL=MC_0;        // Timer stoppen
      lcd_gotoxy(0,1);
      lcd_puts("Seltsam, oder?!");
      }
    }
}

// Timer A0 interrupt service routine
// wird jedesmal aufgerufen, wenn Interrupt CCR0 von TimerA kommt
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void)
{
  Zaehler++;          //  Zaehler inkrementieren
}
