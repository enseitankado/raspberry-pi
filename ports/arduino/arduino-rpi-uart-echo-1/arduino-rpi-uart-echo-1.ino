int sayac = 0;
void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print(sayac++);
  Serial.println(" Merhaba!");
  delay(500);
}
