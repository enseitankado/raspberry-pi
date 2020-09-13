#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>

int main(int argc, char *argv[]) {

  int file, count;
  if(argc!=2){
    printf("Lutfen bir metin girin!\n");
    return -2;
  }

  if ((file = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY))<0) {
    perror("UART: Failed to open the device.\n");
    return -1;
  }

  struct termios options;
  tcgetattr(file, &options);
  options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
  options.c_iflag = IGNPAR | ICRNL;
  tcflush(file, TCIFLUSH);
  tcsetattr(file, TCSANOW, &options);

  if ((count = write(file, argv[1], strlen(argv[1])))<0){
    perror("UART: Ciktiya yazarken hata olustu.\n");
    return -1;
   }

   write(file, "\n\r", 2); // new line and carriage return
   close(file);

   return 0;
}
