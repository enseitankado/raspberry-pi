void setup() {
  Serial.begin(115200);
  // Karsilama mesajini yaz
  Serial.println("Serial arabirimi 115200 baud da basladi.");
}

void loop() {
  // Raspberry Pi'a yaz
  Serial.println("Bana adini soyler misin?");

  // Raspberry Pi'dan geleni oku
  while (Serial.available() == 0);
  String isim = Serial.readString();

  // Raspberry Pi'a yaz
  Serial.println("Merhaba " + isim + " memnun oldum!");
  Serial.println("Bitti.");
}
