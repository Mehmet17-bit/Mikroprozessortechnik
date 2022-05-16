/**************************************************************************
  Datei blink1.c
  Ablauff�hig auf Hardware: MSP430-Education-Board mit MSP430F2274
  L�sst auf dem MSP430-Edu-Board eine LED blinken

  Kommentar zur Schaltung auf Board:
     P1.0 - P1.7              LED leuchtet wenn Ausgang=H (1)

   Autor  K.W�st, Stand Nov. 19
**************************************************************************/

#include <msp430.h>
#include <lcd_bib.c>        //die LCD Bibliothek ist verf�gbar
#include <lcd_bib.h>

unsigned char lcd[6];           //Pointer f�r die LCD puts Funktion
//unsigned char resulat;

// Funktions-Prototypen
void Warteschleife(unsigned long Anzahl);          // Software Warteschleife

int main(void) {

  WDTCTL = WDTPW + WDTHOLD;          // Watchdog timer anhalten
  //P1DIR = 0xFF;


 // lcd_gotoxy(0,0);                      //Curser Positionierung auf Koordinate (0,0)

  ADC10CTL1 = INCH_14;                           //Analogkanal 14 wird ausgew�hlt
  ADC10AE1 = ADC10AE1 | BIT6;                   //Analogeingang Kanal A14 freischalten

  P2DIR = BIT4;                                 // Lautsprecher aktiv

  /*
   * ADC10SHT_2 Sample and Hold time (16x)
   * Refernce Generator und ADC10 on
   * SREF_0 -> Vr+ = Vss
   * ENC -> Enable conversation
   */
  ADC10CTL0 = SREF_0 + ADC10SHT_2 + REFON + ADC10ON + ENC;

  //lcd_init(16);                         //LCD mit 16 Bit initialisiert

  while(1){
  //ADC10CTL0 = ADC10CTL0 | ENC;          // Enable Conversation

  ADC10CTL0 = ADC10CTL0 | ADC10SC;      // ADC10 Start of Conversation

  while((ADC10CTL0 & ADC10IFG) == 0);       // Warten auf Flag ADC10IFG wenn gesetzt ist und Wandlung fertig dann in ADC10MEM geladen wird

  unsigned int result = ADC10MEM;                        // Speicherung der Wandlung

  if(result <= 20){                         //wenn Absatnd kleiner gleich 20 ist soll es ein Warnsignal ausgeben
      int i = 0;
      while(i < 100){                       // F�r die Erzeugung der Schwingung
              P2OUT = BIT4;                 //lautsprecher anschalten
              Warteschleife(500);
              P2OUT = 0x00;                 //Lautsprecher ausschalten
              Warteschleife(500);
              i++;
              countdown_value_in_sec++;     //Abbruchbedingung !!Notiz: bei break ert�nt kein Piepen!!
          }
  }


  /*
   * Konvertiert die Ausgabe vom int zum String
   */
  uint2string(lcd,result);
  lcd_gotoxy(0,0);
  lcd_puts(lcd);
  //P1OUT = result;
  }
 
  return 0;    // Nur zur Sicherheit Statement wird aber niemals erreicht
}
 

void Warteschleife(unsigned long Anzahl){
volatile unsigned long i;
for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterz�hlen
}
