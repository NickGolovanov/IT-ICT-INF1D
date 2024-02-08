int L1 = 3;
int L2 = 5;
int B1 = 6;
int B2 = 7;
int B3 = 8;
int timer = 0;
bool state;

void setup() {
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(Button_B1, INPUT);
  pinMode(Button_B2, INPUT);
  pinMode(Button_B3, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (millis() >= timer) {
    timer = 1000 + millis();
    state = !state;
    digitalWrite(L1, state);
  }
  if (digitalRead(Button_B1) || digitalRead(Button_B2) || digitalRead(Button_B3)) {
    digitalWrite(L2, HIGH);
    Serial.println("On");
  } else {
    digitalWrite(L2, LOW);
    Serial.println("Off");
  }
  delay(100);
}
