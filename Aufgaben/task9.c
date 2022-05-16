// ************************************************************************
//
//       TestTimerA.c
//       Autor K.Wüst, Nov. 19
//
//      Demonstriert den Lauf des Timers mit ACLK als Taktquelle
//
// ************************************************************************

/*
 * Der Timer ist so konfiguriert, dass er im AClock und Mode2 (continous mode) läuft.
 * Der Zählregister TAR läuft bis 0xFFFFh und dann wird er zurückgesetzt auf 0x0000
 */
#include  <msp430.h>

void main(void){

  WDTCTL = WDTPW + WDTHOLD;  // Stop  Watchdog Timer

  TACTL = TASSEL_1 + TACLR + MC_2;
  // Beschreiben des TimerA-Controlregisters, folgende Steuerbits setzen:
  //   - TimerA Source Select = 1 (Eingangstakt ist AClock)
  //   - TimerA-Register Clear    (Zählregister auf 0 setzen)
  //   - Mode Control = 2         (Start Timer_A im continous mode)

  // Timer läuft jetzt; im Debugger kann das Programm angehalten werden
  // und der aktuelle Stand des Timer A-Registers (TAR) ausgelesen werden:
  // Anhalten - View - Register - Timer A3 - TAR

    while (1) {
  }
}

