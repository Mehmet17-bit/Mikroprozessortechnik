#include <msp430.h>
#include <lcd_bib.h>
#include <lcd_bib.c>

unsigned char lcd[4];


void Warteschleife(unsigned long Anzahl);

int main(void){
    unsigned int value;
    unsigned int oldValue = 0;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR = 0xFF;

    lcd_init(16);
    lcd_puts("Impulse");

    P1OUT = 0;
    P4SEL = BIT7; // 4.7 an leitung 4 altern. leitungsfunktion

    TBCTL = TBSSEL_0 + TBCLR + MC_2; // B Timer FamilyUsersGuide und Seite (391) Externer Timer clear timer und contionous mode Continuous mode: the timer counts up to to the end 0xFFFF 65535.



    while(1){

        value = TBR;

        if(value != oldValue){
            oldValue = value;
            uint2string(lcd, value);
            lcd_gotoxy(0,1);
            lcd_puts(lcd);


           P1OUT = oldValue; // AUSGABE AUF LEUCHTDIODEN Timer B Register
        }
    }
}

void Warteschleife(unsigned long Anzahl)
   {
       volatile unsigned long i;
       for (i = Anzahl; i > 0; i--){
       }// Schleifenvariable herunterzählen
   }
