String isim = "";

void setup() {
  Serial.begin(115200);
  Serial.println("Serial arabirimi 115200 baud da basladi.");
}

void loop() {  
  Serial.println("Bana adini soyler misin? ");  
  while (Serial.available() == 0);
  isim = Serial.readString();
  Serial.println("Merhaba: " + isim + " memnun oldum\n");
}






