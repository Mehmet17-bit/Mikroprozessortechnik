#include <msp430.h>
#include <lcd_bib.h>
#include <lcd_bib.c>

unsigned char lcd[4];
unsigned int impuls;
unsigned int dz;
int taste;

void Warteschleife(unsigned long Anzahl);

int main(void){

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    TACCTL0 = CCIE;            // Capture/Compare-Unit0 Control-Register beschreiben:
                               //   - Interrupt-Auslösung durch Capture/Compare-Unit0 freischalten (CCR0)

    TACCR0 = 32768/10;             // in der sekunde ein Interrupt

    P1DIR = 0xFF;
    P2DIR = 0x00;                   // Port 2 alle Eingänge
    P4DIR = P4DIR | BIT4 | BIT6;

    P2IE = BIT5 + BIT1 + BIT2;      // Tasten SW1-SW3 ansprechen
    P2IES = BIT5 + BIT1 + BIT2;     // Edge Select --> fallende Flanke

    lcd_init(16); 
    lcd_clear();
    P4SEL = BIT7; // 4.7 an leitung 4 altern. leitungsfunktion
    P4OUT = P4OUT & (~(BIT4 + BIT6));

    TACTL = TASSEL_1 + TACLR + MC_1;
    TBCTL = TBSSEL_0 + TBCLR + MC_2; // B Timer FamilyUsersGuide und Seite (391) Externer Timer clear timer und contionous mode Continuous mode: the timer counts up to to the end 0xFFFF 65535.

    __enable_interrupt();           // global interrupt freischalten

    while(1);

    return 0;
}

void Warteschleife(unsigned long Anzahl){
volatile unsigned long i;
 for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterzählen
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2ISR (void){

    taste = P2IFG;

    if(taste == BIT5){                  //Stopp
        P4OUT = P4OUT & (~(BIT4 + BIT6));

    }

    else if(taste == BIT1){                  //linksslauf
        P4OUT = P4OUT | BIT6;

    }

    else if(taste == BIT2){                  //rechtslauf

        P4OUT = P4OUT | BIT4;
    }
    Warteschleife(10000);       // für Entprellung der Tastens

    P2IFG = 0;
}


#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0 (void){
    /*
     * Drezahl Ausgabe Umdrehungen pro Minute
     */
    impuls = TBR;
    TBR = 0;
    dz = impuls * 25;
    uint2string(lcd, impuls);
    lcd_gotoxy(0,0);
    lcd_puts(lcd);

    if(dz > 1000){
        P4OUT = P4OUT & (~(BIT4 + BIT6));
    } else if(dz < 1000){
        P4OUT = P4OUT | BIT4;
    } /*else if(dz < 1000){
        P4OUT = P4OUT | BIT6;
    }*/

}
