const int motorLeftForw = 5;
const int motorLeftBack = 4;
const int motorRightForw = 3;
const int motorRightBack = 2;

volatile int countL = 0;
volatile int countR = 0;

int sensorValues[] = {0, 0, 0, 0, 0, 0, 0, 0};
int sensorPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};

void setup() {
  pinMode(motorLeftForw, OUTPUT);
  pinMode(motorLeftBack, OUTPUT);
  pinMode(motorRightForw, OUTPUT);
  pinMode(motorRightBack, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);

  Serial.begin(9600);
}

void rotationL() {
  countL++;
}

void rotationR() {
  countR++;
}

void loop() {
  getSensor();

  if (sensorValues[3] == 1 && sensorValues[4] == 1) {
    // Both sensors detecting the line, go forward
    forward();
  } else if (sensorValues[3] == 1 && sensorValues[4] == 0) {
    // Right sensor not detecting the line, turn slightly left
    adjustLeft();
  } else if (sensorValues[3] == 0 && sensorValues[4] == 1) {
    // Left sensor not detecting the line, turn slightly right
    adjustRight();
  } else {
    // No sensors detecting the line, stop
    stop();
  }
}

void getSensor() {
  for (int i = 0; i < sizeof(sensorPins) / sizeof(sensorPins[0]); i++) {
    int sensorState = analogRead(sensorPins[i]);
    sensorValues[i] = sensorState >= 800 ? 1 : 0;

    Serial.print(sensorValues[i]);
    Serial.print(" ");
  }
  Serial.println("");
}

void forward() {
  analogWrite(motorLeftForw, 250);
  analogWrite(motorLeftBack, 0);
  analogWrite(motorRightForw, 250);
  analogWrite(motorRightBack, 0);
}

void adjustLeft() {
  analogWrite(motorLeftForw, 0);
  analogWrite(motorLeftBack, 150);
  analogWrite(motorRightForw, 250);
  analogWrite(motorRightBack, 0);
}

void adjustRight() {
  analogWrite(motorLeftForw, 250);
  analogWrite(motorLeftBack, 0);
  analogWrite(motorRightForw, 0);
  analogWrite(motorRightBack, 150);
}

void stop() {
  analogWrite(motorLeftForw, 0);
  analogWrite(motorLeftBack, 0);
  analogWrite(motorRightForw, 0);
  analogWrite(motorRightBack, 0);
}
