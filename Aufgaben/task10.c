// ************************************************************************
//
//       IntTimerA.c
//       Autor K.Wüst,  Nov. 19
//
// ************************************************************************

#include  <msp430.h>

void main(void){
  WDTCTL = WDTPW + WDTHOLD;  // Stop  Watchdog Timer

  TACCTL0 = CCIE;            // Capture/Compare-Unit0 Control-Register beschreiben:
                             //   - Interrupt-Auslösung durch Capture/Compare-Unit0 freischalten (CCR0)
  /*
   * TACCR0 ist der Wert der vom Zählregister erreicht wird bis zur Auslösung
   * verdoppeln durch /2
   * verkürzen durch *2-1
   */
  TACCR0 = 32768;            // Endwert in Capture/Compare-Register 0 eintragen

  P1DIR = 0x01;              // P1.0 ist Ausgang, die anderen Pins sind Eingänge

  /*
   * Timer control Register ist im AClock und UP Mode sowie zurücksetzen des TAR wenn TACCR0 erreicht wurde
   */
  TACTL = TASSEL_1 + TACLR + MC_1;  // Beschreiben des TimerA-Controlregisters
                             //   - TimerA Source Select = 1 (Eingangstakt ist AClock)
                             //   - Clear TimerA-Register    (Zählregister auf 0 setzen)
                             //   - Start Timer_A im up mode (Mode Control = 1)

  __enable_interrupt();      // Interrupts global frei schalten

  /*
   * schaltet in den Energiesparmodus. !! Wichtig !! Den Takt des Timers nicht auschalten
   * CPU wird gestoppt in den ISR gegangen nach Beendigung durch einen Tastendruck wieder "aufgeweckt"
   */
  __low_power_mode_0();      // low power mode 0:  CPU wird gestoppt

}

// Timer A0 interrupt service routine
// wird jedesmal aufgerufen, wenn Interrupt CCR0 von TimerA kommt
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void)
{
  P1OUT ^= 0x01;          // Leitung 0 von Port 1 toggeln
}
