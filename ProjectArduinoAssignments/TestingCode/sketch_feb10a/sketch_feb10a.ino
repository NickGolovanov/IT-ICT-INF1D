<<<<<<< HEAD


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
=======
const int MotorB = 3;
const int MotorA = 4;

const int One = A0;
const int Two = A1;
const int Three = A2;
const int Four = A3;
const int Five = A4;
const int Six = A5;
const int Seven = A6;
const int Eight = A7;

const uint8_t SensorCount = 8;

// Array to store sensor readings
uint16_t sensorValues[SensorCount];

void setup() {
  pinMode(MotorB, OUTPUT);
  pinMode(MotorA, OUTPUT);
  pinMode(One, INPUT);
  pinMode(Two, INPUT);
  pinMode(Three, INPUT);
  pinMode(Four, INPUT);
  pinMode(Five, INPUT);
  pinMode(Six, INPUT);
  pinMode(Seven, INPUT);
  pinMode(Eight, INPUT);
}

void loop() {
  maze(); // Call the maze function
}

void maze() {
  // Read sensor values
  sensorValues[0] = analogRead(One);
  sensorValues[1] = analogRead(Two);
  sensorValues[2] = analogRead(Three);
  sensorValues[3] = analogRead(Four);
  sensorValues[4] = analogRead(Five);
  sensorValues[5] = analogRead(Six);
  sensorValues[6] = analogRead(Seven);
  sensorValues[7] = analogRead(Eight);

  // Check if all sensors detect white surface (assuming white corresponds to high readings)
  bool allWhiteDetected = true;
  for (int i = 0; i < SensorCount; i++) {
    if (sensorValues[i] >= 800) { // Adjust the threshold as needed
      allWhiteDetected = false;
      break; // Exit loop early if any sensor detects black
    }
  }

  // If all sensors detect white surface, stop the robot
  if (allWhiteDetected) {
    digitalWrite(MotorA, LOW); // Deactivate Motor A
    digitalWrite(MotorB, LOW); // Deactivate Motor B
  } else {
    // If any sensor detects black line, move forward
    digitalWrite(MotorA, HIGH); // Activate Motor A
    digitalWrite(MotorB, HIGH); // Activate Motor B
  }
}
>>>>>>> 78d350fda26d92a80908daab224b20b9e1462a2f
