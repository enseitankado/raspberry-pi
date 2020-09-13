#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#define LCD_CHR  1 // Veri gonderme kipi
#define LCD_CMD  0 // Komut gonderme kipi

#define LINE1  0x80 // 1. satir
#define LINE2  0xC0 // 2. satir

#define LCD_BACKLIGHT   0x08  // Acik
// LCD_BACKLIGHT = 0x00  # Kapali

#define ENABLE  0b00000100 // Etkinlestirme biti

// Metni ekrana yaz
void print_lcd(int fd, const char *s, int line) {
  lcd_byte(fd, line, LCD_CMD);
  while ( *s ) lcd_byte(fd, *(s++), LCD_CHR);
}

void lcd_byte(int fd, int bits, int mode)   {

  int bits_high, bits_low;
  bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
  bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

  wiringPiI2CReadReg8(fd, bits_high);
  lcd_toggle_enable(fd, bits_high);

  wiringPiI2CReadReg8(fd, bits_low);
  lcd_toggle_enable(fd, bits_low);
}

void lcd_toggle_enable(int fd, int bits)   {
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits | ENABLE));
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
  delayMicroseconds(500);
}

void lcd_init(int fd)   {
  lcd_byte(fd, 0x33, LCD_CMD); // Hazirla
  lcd_byte(fd, 0x32, LCD_CMD); // Hazirla
  lcd_byte(fd, 0x06, LCD_CMD); // Imlec hareket yonu
  lcd_byte(fd, 0x0C, LCD_CMD); // LCD acik, imlec kapali
  lcd_byte(fd, 0x28, LCD_CMD); // Satir sayisi ve uzunlugu, punto
  lcd_byte(fd, 0x01, LCD_CMD); // Ekrani temizle
  delayMicroseconds(500);
}

int main(int argc, char *argv []) {

  if (wiringPiSetup () == -1) exit (1);

  int lcd1, lcd2;
  lcd1 = wiringPiI2CSetup(0x3e);
  lcd_init(lcd1);
  print_lcd(lcd1, argv[1], LINE1);
  print_lcd(lcd1, argv[2], LINE2);

  lcd2 = wiringPiI2CSetup(0x3f);
  lcd_init(lcd2);
  print_lcd(lcd2, argv[3], LINE1);
  print_lcd(lcd2, argv[4], LINE2);

  return 0;
}
