#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

int SPI_SPEED = 1000*10000; // Hz
int SPI_PORT = 0;
int STCP = 3;		// Latch islevi icin wPi3 (GPIO.3) kullaniliyor

/*
	74HC595'in latch islevi icin STCP (Store Clock Pulse) 
	saat sinyali veriliyor. 
	Not: 74HC595 tarafindan yapilan store islemi sinyalin 
	yukselen kenarinda gerceklestirilir.
*/	
int latch(int latch_pin, int delay)
{
digitalWrite(latch_pin, HIGH);  
    usleep(delay);
    digitalWrite(latch_pin, LOW); 
    usleep(delay);	
}

int main(int argc, char *argv[])
{
	int i;
	unsigned char buff[2];
			
	if (wiringPiSPISetup (SPI_PORT, SPI_SPEED) < 0) 
	{
		printf ("SPI initilize edilemedi. Return(-1)\n") ;
		return -1;
	}
	
	wiringPiSetup();
	pinMode (STCP, OUTPUT);
	printf ("SPI %d test ediliyor...\n", SPI_PORT) ;

	for(i = 0; i <= 255; i++) 
	{
		printf ("Gonderilecek: %03d \n", i);
		
		// 1 byte'lık mevcut <i> degeri 2 bytelık SPI tamponuna yaziliyor		//int wiringPiSPIDataRW (int channel, unsigned char *data, int len) ;
		buff[0] = i;
		buff[1] = i;
		wiringPiSPIDataRW(SPI_PORT, buff, 2);
		latch(STCP, 1000*50);	
	}

	printf ("\nBitti.\n");	
	return 0 ;
}
