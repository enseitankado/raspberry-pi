void setup() {
  Serial.begin(115200);
  Serial.println("Arduino basladi!");
  pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // A0'a bagli LDR'nin degerini oku
  int LDR = analogRead(A0);
  Serial.println(LDR);

  digitalWrite(13, HIGH);
  delay(250);
  digitalWrite(13, LOW);
  delay(250);

  // Raspberry Pi'dan komut geldi mi?
  if (Serial.available() > 0) {

    String komut = Serial.readString();
    komut.trim();

    // Led'i yak
    if (String("ac") == komut) {
      digitalWrite(7, HIGH);
      Serial.println("Arduino: Led yakildi");      
    }

    // Led'i sondur
    if (String("kapat") == komut) {
      digitalWrite(7, LOW);
      Serial.println("Arduino: Led sonduruldu");    
    }
  }
}


