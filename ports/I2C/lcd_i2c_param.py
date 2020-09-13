#!/usr/bin/python
import smbus
import time
import sys

# Aygitlarin adresleri
I2C_ADDR1  = 0x3e # 1. ekranin adresi
I2C_ADDR2  = 0x3f # 2. ekranin adresi
LCD_WIDTH = 16   # Maximum characters per line

# Bazi ekran sabitleri
LCD_CHR = 1 # Mode - Sending data
LCD_CMD = 0 # Mode - Sending command

LCD_LINE_1 = 0x80 # 1. satirin LCD RAM adresi
LCD_LINE_2 = 0xC0 # 2. satirin LCD RAM adresi

LCD_BACKLIGHT  = 0x08  # Acik
#LCD_BACKLIGHT = 0x00  # Kapali

ENABLE = 0b00000100 # Etkinlestirme biti

# Zamanlama sabitleri
E_PULSE = 0.0005
E_DELAY = 0.0005

#I2C arabirimini ac
#bus = smbus.SMBus(0)  # Rev 1 Pi icin 0
bus = smbus.SMBus(1) # Rev 2 Pi icin 1

def lcd_init(lcd_adr):
  # Ekrani ayarla
  lcd_byte(lcd_adr, 0x33,LCD_CMD) # 110011 Onyukle
  lcd_byte(lcd_adr, 0x32,LCD_CMD) # 110010 Onyukle
  lcd_byte(lcd_adr, 0x06,LCD_CMD) # 000110 Imlec hareket yonu
  lcd_byte(lcd_adr, 0x0C,LCD_CMD) # 001100 Ekran acik, imlec kapali
  lcd_byte(lcd_adr, 0x28,LCD_CMD) # 101000 Veri uz, satir sayisi
  lcd_byte(lcd_adr, 0x01,LCD_CMD) # 000001 Ekrani temizle
  time.sleep(E_DELAY)

def lcd_byte(lcd_adr, bits, mode):
  bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT
  bits_low = mode | ((bits<<4) & 0xF0) | LCD_BACKLIGHT

  # Yuksek degerlikli bitler
  bus.write_byte(lcd_adr, bits_high)
  lcd_toggle_enable(lcd_adr, bits_high)

  # Dusuk degerlikli bitler
  bus.write_byte(lcd_adr, bits_low)
  lcd_toggle_enable(lcd_adr, bits_low)

def lcd_toggle_enable(lcd_adr, bits):
  time.sleep(E_DELAY)
  bus.write_byte(lcd_adr, (bits | ENABLE))
  time.sleep(E_PULSE)
  bus.write_byte(lcd_adr,(bits & ~ENABLE))
  time.sleep(E_DELAY)

def lcd_string(lcd_adr, message, line):
  message = message.ljust(LCD_WIDTH," ")
  lcd_byte(lcd_adr, line, LCD_CMD)
  for i in range(LCD_WIDTH):
    lcd_byte(lcd_adr, ord(message[i]),LCD_CHR)

def main():
  # Ana program blogu
  lcd_init(I2C_ADDR1)
  lcd_init(I2C_ADDR2)

  # Seçenekleri yazdir
  lcd_string(I2C_ADDR1, sys.argv[1], LCD_LINE_1)
  lcd_string(I2C_ADDR1, sys.argv[2], LCD_LINE_2)

  lcd_string(I2C_ADDR2, sys.argv[3], LCD_LINE_1)
  lcd_string(I2C_ADDR2, sys.argv[4], LCD_LINE_2)

main()
