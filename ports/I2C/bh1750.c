#include <wiringPiI2C.h>
#include <stdio.h>
int main (void) {
  int handle = wiringPiI2CSetup(0x23) ;
  wiringPiI2CWrite(handle,0x10);
  sleep(1);
  int word=wiringPiI2CReadReg16(handle,0x00);
  int lux=((word & 0xff00)>>8) | ((word & 0x00ff)<<8);
  printf("Isik seviyesi: %d Lux\n",lux);
  return 0 ;
}
