#include <wiringPi.h> // WiringPi kutuphanesi
#include <lcd.h>      // WiringPi LCD fonksiyonlari
#include <stdio.h>    // Printf fonksiyonlari

// GPIO numaralandirmasina gore pin’ler

#define LCD_RS  18   // Kaydedici secme pin’i
#define LCD_E   23   // Enable pin’i
#define LCD_D4  7    // Veri biti  4
#define LCD_D5  8    // Veri biti  5
#define LCD_D6  12   // Veri biti  6
#define LCD_D7  16   // Veri biti  7

int main(int argc, char *argv [])
{
    int lcd; // lcd nesnesi
    wiringPiSetupGpio () ; // GPIO(BCM) numaralandirmasini kullan

    //LCD'yi hazirla LCD(int rows, int cols, int bits, int rs, int enable, int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7)
    if (lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7,0,0,0,0)){
            printf ("lcd yuklenirken hata olustu! \n");
            return -1 ;
    }
   if (argc > 1)
   {
      lcdPosition(lcd, 0, 0);
      lcdPuts(lcd, argv[1]);
      lcdPosition(lcd, 0, 1);
      lcdPuts(lcd, argv[2]);
   }
}
