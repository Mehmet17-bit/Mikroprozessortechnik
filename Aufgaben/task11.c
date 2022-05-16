// ************************************************************************
//
//       IntTimerA.c
//       Autor K.Wüst,  Nov. 19
//
// ************************************************************************

#include  <msp430.h>
#include <lcd_bib.c>        //die LCD Bibliothek ist verfügbar
#include <lcd_bib.h>

unsigned char countdown_value_in_sec = 30;          //Countdown für den Alarm beträgt 30 Sekunden - globale Variable
unsigned char lcd[4];                               //Pointer für den LCD puts Funktion

void Warteschleife(unsigned long Anzahl);          // Software Warteschleife

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
  P2DIR = BIT4;             //Lautsprecher ist aktiviert an Port 2.4

  P1OUT = 0x00;                 // Output über Port 1

  lcd_init(16);                 //LCD mit 16 Bit initialisieren
  lcd_gotoxy(0,0);              //Cursor Positionierung auf Koordinate (0,0)

  /*
   * Timer control Register ist im AClock und UP Mode sowie zurücksetzen des TAR wenn TACCR0 erreicht wurde
   */
  TACTL = TASSEL_1 + TACLR + MC_1;  // Beschreiben des TimerA-Controlregisters
                             //   - TimerA Source Select = 1 (Eingangstakt ist AClock)
                             //   - Clear TimerA-Register    (Zählregister auf 0 setzen)
                             //   - Start Timer_A im up mode (Mode Control = 1)

  __enable_interrupt();      // Interrupts global freischalten

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
    countdown_value_in_sec--;               // dekrementieren des Countdown in der ISR

    /*
     * LCD Konvertierung, Cursor Positionierung, Output
     */
    uchar2string(lcd,countdown_value_in_sec);
    lcd_gotoxy(0,0);
    lcd_puts(lcd);

    if(countdown_value_in_sec == 0){
        int i = 0;
        while(i < 100){                 // Für die Erzeugung der Schwingung
            P2OUT = BIT4;               //lautsprecher anschalten
            Warteschleife(500);
            P2OUT = 0x00;               //Lautsprecher ausschalten
            Warteschleife(500);
            i++;
            countdown_value_in_sec++;   //Abbruchbedingung !!Notiz: bei break ertönt kein Piepen!!
        }
    }
}

void Warteschleife(unsigned long Anzahl){
volatile unsigned long i;
 for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterzählen
}
