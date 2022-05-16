// ************************************************************************
//
//       TestTimerA.c
//       Autor K.W�st, Nov. 19
//
//      Demonstriert den Lauf des Timers mit ACLK als Taktquelle
//
// ************************************************************************

/*
 * Der Timer ist so konfiguriert, dass er im AClock und Mode2 (continous mode) l�uft.
 * Der Z�hlregister TAR l�uft bis 0xFFFFh und dann wird er zur�ckgesetzt auf 0x0000
 */
#include  <msp430.h>

void main(void){

  WDTCTL = WDTPW + WDTHOLD;  // Stop  Watchdog Timer

  TACTL = TASSEL_1 + TACLR + MC_2;
  // Beschreiben des TimerA-Controlregisters, folgende Steuerbits setzen:
  //   - TimerA Source Select = 1 (Eingangstakt ist AClock)
  //   - TimerA-Register Clear    (Z�hlregister auf 0 setzen)
  //   - Mode Control = 2         (Start Timer_A im continous mode)

  // Timer l�uft jetzt; im Debugger kann das Programm angehalten werden
  // und der aktuelle Stand des Timer A-Registers (TAR) ausgelesen werden:
  // Anhalten - View - Register - Timer A3 - TAR

    while (1) {
  }
}

