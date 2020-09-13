import RPi.GPIO as GPIO # GPIO kutuphanesini ekle
import time # 'sleep' komutu icin kutuphaneyi ekle

GPIO.setmode(GPIO.BOARD) # board pin numara sistemini kullan
GPIO.setup(12, GPIO.OUT) # GPIO 12. pin’i cikis olarak ayarla

#YakSon() adinda bir alt program tanimla
def YakSon(kackez,bekleme):
	for i in range(0,kackez): # donguyu kackez kadar tekrarla
		print "Adim " + str(i+1) # dongunun mevcut degerini yaz
		GPIO.output(12, True) # Pin 7'yi enerjilendir
		time.sleep(bekleme) # Bekle
		GPIO.output(12,False) # Pin 7'nin enerjisini kes
		time.sleep(bekleme)# Bekle
	print "Bitti" # Dongu tamamlandiginda 'Bitti' mesajini yaz
	GPIO.cleanup()

# Kullaniciya dongu sayisi ve bekleme suresini sor
kackez = raw_input("Kac kez yanip sonsun: ")
bekleme = raw_input("Her yanip sonmede ne kadar beklesin(saniye): ")

# Led'i yakip sonduren alt programi cagir
YakSon(int(kackez),float(bekleme))
