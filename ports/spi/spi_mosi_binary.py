#!/usr/bin/python
import RPi.GPIO as GPIO # GPIO kutuphanesini ekle
import spidev
import time

spi = spidev.SpiDev() # spi nesnesini olustur
spi.open(0, 1) # 0. SPI port’unu ac

GPIO.setmode(GPIO.BOARD) # board pin numara sistemini kullan
GPIO.setup(12, GPIO.OUT) # GPIO 7. pin’i cikis olarak ayarla

try:
	while True:
		
		for x in range(0, 255):		
			resp = spi.xfer2([x]) # 1 byte'lik x degerini gonder
			GPIO.output(12, True)  # latch enable
			GPIO.output(12, False) # latch disable
			time.sleep(0.2) # yarim saniye bekle
		
	#end while

except KeyboardInterrupt: # Ctrl+C tusuna  basilmis ise
	spi.close() # SPI port’unu kapat ve cik
#end try
