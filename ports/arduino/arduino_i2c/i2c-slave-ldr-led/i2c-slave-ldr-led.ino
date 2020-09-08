#include <Wire.h>
#define ARDUINO_ADR 0x5E 

byte cevap[1];
short LDR_deger;
const int LDR_pin = A0; 
const int LED_pin = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("Program basladi.");
  Wire.begin(ARDUINO_ADR); 
  Wire.onRequest(veriGonder);
  Wire.onReceive(veriAl);
  pinMode(LDR_pin, INPUT);
  pinMode(LED_pin, OUTPUT);
}

void veriGonder() {
  Serial.println("\r\nonRequest tetiklendi.");  
  LDR_deger = analogRead(LDR_pin);  
  LDR_deger = map(LDR_deger, 0, 1023, 0, 255);
  cevap[0]= (byte) LDR_deger;
  Wire.write(cevap, 1);
  Serial.println( "0x" + String(cevap[0] ,HEX) + " gonderildi.");
}

void veriAl(int gelenByteSayisi) {
  Serial.println("\r\nonReceive tetiklendi.");
  while (Wire.available()) {
    int deger = Wire.read();
    Serial.print("Gelen deger: " + String(deger));    
    if (deger == 1) {
      Serial.println(" > LED Acik");
      digitalWrite(LED_pin, HIGH);
    } else {
      Serial.println(" > LED Kapali");
      digitalWrite(LED_pin, LOW);
    }
  }
}

void loop() {
  delay(1000);
}


