void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int incoming = Serial.parseInt();

    if (incoming == 5) {
      digitalWrite(D5, HIGH);
      delay(2000);
      digitalWrite(D5, LOW);
    }
    else if (incoming == 6) {
      digitalWrite(D6, HIGH);
      delay(2000);
      digitalWrite(D6, LOW);
    }
    else if (incoming == 7) {
      digitalWrite(D7, HIGH);
      delay(2000);
      digitalWrite(D7, LOW);
    }
  }
}
