#include <stdio.h>
#include <wiringPi.h>

int main (void)
{
  printf("wPi.0 pinine bagli buton okunacak.\nCikisi icin Ctrl+C basin.\n");
  wiringPiSetup();

  pinMode(1, INPUT);
  pullUpDnControl (1, PUD_DOWN) ;

  for (;;)
  {
        int buton  = digitalRead(1);
        if (HIGH == buton)
                printf("Butona basildi.\n");
        else
                printf("Buton okunuyor...\n");
        delay(500);
  }
}
