#!/usr/bin/python
import spidev # SPI kutuphanesini ekle
import RPi.GPIO as GPIO # GPIO kutuphanesini ekle
import time

GPIO.setmode(GPIO.BOARD) # board pin numara sistemini kullan
GPIO.setup(12, GPIO.OUT) # GPIO 7. pin’i cikis olarak ayarla

spi = spidev.SpiDev() # SPI nesnesini olustur
spi.open(0, 1) # 0. SPI port’unu ac 

try:
	while True:			
		
		resp = spi.xfer2([0xFF]) # 1 byte veriyi seri olarak aktar		
		GPIO.output(12, True)  # latch enable
		GPIO.output(12, False) # latch disable
		time.sleep(0.5) # yarim saniye bekle
		
		resp = spi.xfer2([0x00]) # 1 byte veriyi seri olarak aktar		
		GPIO.output(12, True)  # latch enable
		GPIO.output(12, False) # latch disable
		time.sleep(0.5) # yarim saniye bekle
		
	#end while

except KeyboardInterrupt: # Ctrl+C tusuna basilmis ise
	spi.close() # SPI port’unu kapat ve cik
#end try
