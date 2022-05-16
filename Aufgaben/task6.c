/**************************************************************************
  Datei blink1.c
  Ablauffähig auf Hardware: MSP430-Education-Board mit MSP430F2274
  Lässt auf dem MSP430-Edu-Board eine LED blinken

  Kommentar zur Schaltung auf Board:
     P1.0 - P1.7              LED leuchtet wenn Ausgang=H (1)

   Autor  K.Wüst, Stand Nov. 19
**************************************************************************/
  
#include <msp430.h>
#include <lcd_bib.c>        //die LCD Bibliothek ist verfügbar
#include <lcd_bib.h>

// Funktions-Prototypen
void Warteschleife(unsigned long Anzahl);          // Software Warteschleife

int main(void) {

  WDTCTL = WDTPW + WDTHOLD;          // Watchdog timer anhalten

  // Hardware-Initialisierung
   P1DIR = 0xFF;           // Port 1 arbeitet mit allen Leitungen (P1.0-P1.7) als Ausgabeport
   P2DIR = 0;              // Port 2 ist verfügbar

   unsigned char taste = 0x00;          // Tastenwert = hexa null
   unsigned char startwert = 0;        // Startwert = 0
   unsigned char startwert1 = 0;        //zweiter Startwert
   unsigned char lcd[4];                //für die Funktion uchar2string
   lcd_init(16);                    //LC-Display initialisieren mit 16 Bit

   //void lcd_clrscr(void);         //Löscht LCD Display und setzt Cursor auf Startposition


   while(1)    // Endlosschleife
   {
       //P1OUT = P2IN;         // Test ob die Tasten funktionieren

       startwert1 = startwert;      //übergabe startwert auf startwert1 -> startwert1 = 0

       taste = ~P2IN;            // taste erhält den negierten Wert von Port 2

       if(taste & 0x01){         //Für SW1 um 1 erhöhen
           startwert++;
       }

       if(taste & 0x02){         //Für SW2 um 1 erniedrigen
           startwert--;
       }

       if(taste & 0x04){         //Für SW3 verdoppeln
           startwert = startwert * 2;
       }

       if(taste & 0x20){         //Für SW4 halbieren
           startwert = startwert / 2;
       }

       if(startwert != startwert1){         //schaut ob der startwert auch wirklich verändert wurde
           uchar2string(lcd,startwert);     //übersetzt den veränderten Startwert und speichert in lcd array ab
           lcd_gotoxy(0,0);
           lcd_puts(lcd);                   //gibt das array aus
           P1OUT = startwert;        //Ausgabe des veränderten Startwertes
           Warteschleife(25000);     //Warteschleife um Tastenprellung zu umgehen
       }



   }

   return 0;    // Nur zur Sicherheit Statement wird aber niemals erreicht
 }
 

void Warteschleife(unsigned long Anzahl){
volatile unsigned long i;
 for (i = Anzahl; i > 0; i--);   // Schleifenvariable herunterzählen
}
 
