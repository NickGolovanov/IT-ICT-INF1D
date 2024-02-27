const int motorA1 = 5;
const int motorA2 = 4;
const int motorB1 = 3;
const int motorB2 = 2;

int sensorValues[] = {0,0,0,0,0,0,0,0};
int sensorPins[] = {A0,A1,A2,A3,A4,A5,A6,A7};

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
}

void loop() {
  getSensor();
  
  if (sensorValues[3] == 1 || sensorValues[4] == 1) {
    forward();
  }
  else if (sensorValues[0] == 1 || sensorValues[1] == 1 || sensorValues[2] == 1) {
    adjustRight();
  }  
  else if (sensorValues[5] == 1 || sensorValues[6] == 1 || sensorValues[7] == 1) {
    adjustLeft();
  }
  else if (sensorValues[0] == 1 || sensorValues[1] == 1 || sensorValues[2] == 1 || sensorValues[3] == 1 || sensorValues[4] == 1){
    right();
  }
  else if (sensorValues[4] == 1 || sensorValues[5] == 1 || sensorValues[6] == 1 || sensorValues[7] == 1){
    left();
  }
  else {
    // No sensor detects the line, stop or turn around
    if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && 
        sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) {
      // If all sensors are off the line, turn around
      turnAround();
    } else {
      // Otherwise, stop
      stop();
    }
  }
}





void getSensor(){
   for(int i = 0; i < sizeof(sensorPins) / sizeof(sensorPins[0]); i++) {
    int sensorState = analogRead(sensorPins[i]);
    sensorValues[i] = sensorState >= 800 ? 1 : 0;

    Serial.print(sensorValues[i]);
    Serial.print(" ");
    
   }
   Serial.println("");
}


void forward(){
    analogWrite(motorA1, 200); //480
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 200); //474
    analogWrite(motorB2, 0);
 }
void backward(){

    analogWrite(motorA1, 0);
    analogWrite(motorA2, 200); // 480
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 200); // 474

}
void stop() {
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
}

void left() {
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 200);
    analogWrite(motorB1, 200);
    analogWrite(motorB2, 0);
}

void right() {
    analogWrite(motorA1, 100);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 100);
}

void adjustLeft() {
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 100);
    analogWrite(motorB1, 150);
    analogWrite(motorB2, 0);
}
void adjustRight(){
    analogWrite(motorA1, 150);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 100);
}
void turnAround(){
    analogWrite(motorA1, 150);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 150);
}
