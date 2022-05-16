#include <msp430.h>
#include <lcd_bib.h>
#include <lcd_bib.c>

unsigned char lcd[4];
unsigned int value;
unsigned int dz;

void Warteschleife(unsigned long Anzahl);

int main(void){

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    TACCTL0 = CCIE;            // Capture/Compare-Unit0 Control-Register beschreiben:
                               //   - Interrupt-Auslösung durch Capture/Compare-Unit0 freischalten (CCR0)

    TACCR0 = 32768;             // in der sekunde ein Interrupt
    P2DIR = 0x00; // Port 2 alle Eingänge

    P1DIR = 0xFF;

    lcd_init(16);
    lcd_puts("Impulse pro/U");

    P1OUT = 0;
    P4SEL = BIT7; // 4.7 an leitung 4 altern. leitungsfunktion

    TACTL = TASSEL_1 + TACLR + MC_1;

    TBCTL = TBSSEL_0 + TBCLR + MC_2; // B Timer FamilyUsersGuide und Seite (391) Externer Timer clear timer und contionous mode Continuous mode: the timer counts up to to the end 0xFFFF 65535.


    //TACTL |= MC_1;
    //TBCTL |= MC_2;

    __enable_interrupt();           // global interrupt freischalten

    while(1){
    }
}

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void){
    value = TBR;
    TBR = 0;
    dz = (value * 5) /2;
    uint2string(lcd, value);
    lcd_gotoxy(0,0);
    lcd_puts(lcd);

    uint2string(lcd, dz);
    lcd_gotoxy(0,1);
    lcd_puts(lcd);
    //TACTL = MC_0; // hält Timer an
}
