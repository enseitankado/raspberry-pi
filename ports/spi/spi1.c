#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>

int SPI_SPEED = 1000;
int SPI_PORT = 0;

int main(int argc, char *argv[])
{
	int i;
	printf ("SPI test ediliyor...\n") ;
	
	if (wiringPiSPISetup (SPI_PORT, SPI_SPEED) < 0) 
	{
		printf ("SPI initilize edilemedi. Return(-1)\n") ;
		return -1;
	}
	
	uint8_t leds_buff[3];	
	leds_buff[0] = 0xff;	
	leds_buff[1] = 0x00;
	leds_buff[2] = 0xff;
	
	/*
		Yazılacak SPI buffer içeriği
	*/
	printf ("\nYazılacak SPI buffer içeriği:\n");
	for(i = 0; i < sizeof(leds_buff); i++) {
		printf ("leds_buff[%d]=%02X\n", i, leds_buff[i]) ;
	}
	printf ("\n");
	
	/*			
		SPI veri yolunu veri yazar yazar 
            daha sonra da veri yolunu okur.
Yazma isleminden sonra tampon içine
		çırak aygıttan okunan veri yazılır.
Çırak aygıt herhangi bir cevap göndermemiş ise
0 ile doldurulur.	
		
		int wiringPiSPIDataRW (int channel, unsigned char *data, int len) ;
	*/
	printf ("Tampon porta yaziliyor...\n");
	wiringPiSPIDataRW(SPI_PORT, leds_buff, sizeof(leds_buff));

	
	/*
		SPI buffer dan okunan değer.
	*/	
	printf ("\nDönen tampon içeriği:\n");
	for(i = 0; i < sizeof(leds_buff); i++) {
		printf ("leds_buff[%d]=%02X\n", i, leds_buff[i]) ;
	}
	printf ("\n");
	
	return 0 ;
}
