int checklock1 = D2;

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(lock1, INPUT_PULLUP);
}

int value = 0;
void loop() {
  digitalWrite(checklock1, HIGH);
  value = digitalRead(checklock1);
  if (value == 0) {
    Serial.println("locked");
  }
  else {
    Serial.println("unlocked");
  }
  delay(500);
}
