#include <stdio.h>
#include <wiringPi.h>

#define LED 15

int main (void)
{
  printf ("Raspberry Pi wPi.15 pininde calisiyor...\n");
  printf("Cikis icin Ctrl+C tuslarina basin.\n");

  wiringPiSetup () ;
  pinMode (LED, OUTPUT);

  for (;;)
  {
    digitalWrite (LED, HIGH) ;  // Aç
    delay (500) ;               // milisaniye
    digitalWrite (LED, LOW) ;   // Kapat
    delay (500) ;
  }
  return 0 ;
}
