#!/usr/bin/Python
# -*- coding: utf-8 -*-
#import
import RPi.GPIO as GPIO
import time

# GPIO ile LCD pin’lerini iliskilendir
LCD_RS = 7
LCD_E  = 8
LCD_D4 = 25
LCD_D5 = 24
LCD_D6 = 23
LCD_D7 = 18

# Bazi sabitler tanimlaniyor
LCD_WIDTH = 16  # Satir basina karakter sayisi
LCD_CHR = True	# Karakter LCD kipi etkin
LCD_CMD = False

LCD_LINE_1 = 0x80 # 1. satirin LCD RAM addresi
LCD_LINE_2 = 0xC0 # 2. satirin LCD RAM addresi

# Zamanlama sabitleri
E_PULSE = 0.0005
E_DELAY = 0.0005

def main():
  # Ana program blogu

  GPIO.setwarnings(False)
  GPIO.setmode(GPIO.BCM)       # BCM GPIO numaralandirmasini kullan
  GPIO.setup(LCD_E, GPIO.OUT)  # E
  GPIO.setup(LCD_RS, GPIO.OUT) # RS
  GPIO.setup(LCD_D4, GPIO.OUT) # DB4
  GPIO.setup(LCD_D5, GPIO.OUT) # DB5
  GPIO.setup(LCD_D6, GPIO.OUT) # DB6
  GPIO.setup(LCD_D7, GPIO.OUT) # DB7


  # LCD gostergeyi hazirla
  lcd_init()

  while True:

    # LCD'ye metni yaz
    lcd_string("Rasbperry Pi",LCD_LINE_1)
    lcd_string("16x2 LCD Kontrol",LCD_LINE_2)

    time.sleep(3) # 3 saniye bekle

    # Send some text
    lcd_string("1234567890123456",LCD_LINE_1)
    lcd_string("abcdefghijklmnop",LCD_LINE_2)

    time.sleep(3) # 3 saniye bekle

def lcd_init():
  # LCD yi hazirla
  lcd_byte(0x33,LCD_CMD) # 110011 Hazirlan
  lcd_byte(0x32,LCD_CMD) # 110010 Hazirlan
  lcd_byte(0x06,LCD_CMD) # 000110 Imlec hareket yonu
  lcd_byte(0x0C,LCD_CMD) # 001100 LCD acik, imlec kapali
  lcd_byte(0x28,LCD_CMD) # 101000 Veri uzunlugu, satir sayisi,punto
  lcd_byte(0x01,LCD_CMD) # 000001 LCD'yi temizle
  time.sleep(E_DELAY)

def lcd_byte(bits, mode):

  GPIO.output(LCD_RS, mode) # RS

  # Yuksek degerlikli bitler
  GPIO.output(LCD_D4, False)
  GPIO.output(LCD_D5, False)
  GPIO.output(LCD_D6, False)
  GPIO.output(LCD_D7, False)
  if bits&0x10==0x10:
    GPIO.output(LCD_D4, True)
  if bits&0x20==0x20:
    GPIO.output(LCD_D5, True)
  if bits&0x40==0x40:
    GPIO.output(LCD_D6, True)
  if bits&0x80==0x80:
    GPIO.output(LCD_D7, True)

  # Enable bitini degistir
  lcd_toggle_enable()

  # Dusuk degerlikli bitler
  GPIO.output(LCD_D4, False)
  GPIO.output(LCD_D5, False)
  GPIO.output(LCD_D6, False)
  GPIO.output(LCD_D7, False)
  if bits&0x01==0x01:
    GPIO.output(LCD_D4, True)
  if bits&0x02==0x02:
    GPIO.output(LCD_D5, True)
  if bits&0x04==0x04:
    GPIO.output(LCD_D6, True)
  if bits&0x08==0x08:
    GPIO.output(LCD_D7, True)

  # Enable bitini degistir
  lcd_toggle_enable()

def lcd_toggle_enable():
  time.sleep(E_DELAY)
  GPIO.output(LCD_E, True)
  time.sleep(E_PULSE)
  GPIO.output(LCD_E, False)
  time.sleep(E_DELAY)

def lcd_string(message,line):
  # Metni LCD'ye gonder

  message = message.ljust(LCD_WIDTH," ")

  lcd_byte(line, LCD_CMD)

  for i in range(LCD_WIDTH):
    lcd_byte(ord(message[i]),LCD_CHR)

if __name__ == '__main__':

  try:
    main()
  except KeyboardInterrupt:
    pass
  finally:
    lcd_byte(0x01, LCD_CMD)
    lcd_string("Hosca kal!",LCD_LINE_1)
    GPIO.cleanup()
