

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

//void loop() {
//  if (sensorValues[6] == 1 && sensorValues[7] == 1){
//    do {
//      left();
//      getSensor();
//      break;
//    }while (!(
//        (sensorValues[5] == 1 || sensorValues[2] == 1) || 
//        (sensorValues[4] == 1 && sensorValues[3] ==1)
//      ));
//  } else if (
//         (sensorValues[5] == 1 || sensorValues[2] == 1) || 
//        (sensorValues[4] == 1 && sensorValues[3] ==1)
//  ){
//    forward();
//  }else {
//    do{
//      right();
//      getSensor();
//      break;
//    }while(!(
//          (sensorValues[5] == 1 || sensorValues[2] == 1) || 
//          (sensorValues[4] == 1 && sensorValues[3] ==1)
//      ));
//  }
//}

void loop() {
  getSensor();
  
  // Check if both outer sensors detect the black line
  if (sensorValues[6] == 1 && sensorValues[7] == 1) {
    // If both outer sensors detect the black line, turn left
    left();
  } 
  // Check if any of the middle sensors detect the black line
  else if (sensorValues[2] == 1 || sensorValues[3] == 1 || sensorValues[4] == 1 || sensorValues[5] == 1) {
    // If any middle sensor detects the black line, move forward
    forward();
  } 
  // If no black line is detected, turn right
  else {
    right();
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
    analogWrite(motorA1, 250); //480
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 250); //474
    analogWrite(motorB2, 0);
 }
void backward(){

    analogWrite(motorA1, 0);
    analogWrite(motorA2, 250); // 480
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 250); // 474

}
void stop() {
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
}

void left() {
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 250);
    analogWrite(motorB1, 250);
    analogWrite(motorB2, 0);
}

void right() {
    analogWrite(motorA1, 250);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 200);
}
