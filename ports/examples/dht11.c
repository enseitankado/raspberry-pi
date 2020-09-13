/*
 *  dht11.c:
 *  Basit bir DTH11 sınama programı
 */

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAXTIMINGS  85
#define DHTPIN    7
int dht11_dat[5] = { 0, 0, 0, 0, 0 };

void read_dht11_dat()
{
  uint8_t laststate   = HIGH;
  uint8_t counter   = 0;
  uint8_t j     = 0, i;
  float   f; /* fahrenheit */

  dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

  /* Pini 18 milisaniyeligine 0 yap */
  pinMode( DHTPIN, OUTPUT );
  digitalWrite( DHTPIN, LOW );
  delay( 18 );

/* Pini 40 mikrosaniyeligine 1 yap */
  digitalWrite( DHTPIN, HIGH );
  delayMicroseconds( 40 );

/* Pini okumaya hazirlan */
  pinMode( DHTPIN, INPUT );

  /* Degisikligi algila ve veriyi oku */
  for ( i = 0; i < MAXTIMINGS; i++ )
  {
    counter = 0;
    while ( digitalRead( DHTPIN ) == laststate )
    {
      counter++;
      /* CPU’nun gucune gore bu degeri artirin */
      /* Detaylı bilgi uygulamanin sonunda verilmistir */
      delayMicroseconds( 4 );
      if ( counter == 255 )
      {
        break;
      }
    }
    laststate = digitalRead( DHTPIN );

    if ( counter == 255 )
      break;

    /* Ilk 3 biti atla */
    if ( (i >= 4) && (i % 2 == 0) )
    {
      /* Okunan her bir biti byte dizisine depola */
      dht11_dat[j / 8] <<= 1;
      if ( counter > 48 )
        dht11_dat[j / 8] |= 1;
      j++;
    }
  }

  /*
   * 40 bit (8bit x 5) veri okundugunu ve saglama toplamini dogrula.
   * Dogrulama basariliysa ekrana yaz.
   */
  if ( (j >= 40) &&
     (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
  {
    f = dht11_dat[2] * 9. / 5. + 32;
    printf( "Sicaklik = %d.%d *C  Nem = %d.%d %% (%.1f *F)\n",
      dht11_dat[2], dht11_dat[3], dht11_dat[0], dht11_dat[1], f );
  }else  {
    printf( "Veri hatali, geciyor\n" );
  }
}

int main( void )
{
  printf( "Raspberry Pi WiringPi DHT11 Sicaklik ve Nem okuma programi\n" );

  if ( wiringPiSetup() == -1 )
    exit( 1 );

  while ( 1 )
  {
    read_dht11_dat();
    delay( 250 ); /* Yeniden okuma icin 250ms bekle */
  }

return(0);
}
