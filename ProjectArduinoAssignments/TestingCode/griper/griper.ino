const int motorA1 = 5;
const int motorA2 = 4;
const int motorB1 = 3;
const int motorB2 = 2;
const int EchoPin = 12; // Assuming you have defined these pins
const int TrigerPin = 13; // Assuming you have defined these pins
const int Gripper = 8; // Assuming you have defined these pins

int sensorValues[] = {0,0,0,0,0,0,0,0};
int sensorPins[] = {A7, A6, A5, A4, A3, A2, A1, A0};

void setup() {
  Serial.begin(9600);
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

  pinMode(EchoPin, INPUT);
  pinMode(TrigerPin, OUTPUT);
  pinMode(Gripper, OUTPUT);
}

void loop() {
  getSensor();

  // Check ultrasonic sensor
  int distance = getUltrasonicDistance();
//  if (distance >= 21 && distance <= 26) {
//    // Robot behavior when ultrasonic sensor detects an object within range
//
//    // Check if all line sensors detect the black line
//    bool allSensorsOnLine = true;
//    for (int i = 0; i < 8; i++) {
//      if (sensorValues[i] == 0) {
//        allSensorsOnLine = false;
//        break;
//      }
//    }
//
//    // If all line sensors detect the black line, go forward
//    if (allSensorsOnLine) {
//      forward();
//    } else {
//      // If not all line sensors detect the black line, stop
//      stop();
//    }
//
//    // Wait for a moment
//    delay(500);
//
//    // Check again if all line sensors detect the black line
//    allSensorsOnLine = true;
//    for (int i = 0; i < 8; i++) {
//      if (sensorValues[i] == 0) {
//        allSensorsOnLine = false;
//        break;
//      }
//    }
//
//    // If still all line sensors detect the black line, proceed
//    if (allSensorsOnLine) {
//      // Check ultrasonic sensor again
//      distance = getUltrasonicDistance();
//      if (distance < 10) {
//        // Activate gripper
//        activateGripper();
//        
//        // Turn left
//        left();
//        delay(600); // Adjust this delay according to your robot's turning behavior
//        stop();
//      }
//    }
//  }
  
  
  if (distance < 20) {
        if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0){
            forward();
        }
        else if (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 1 && sensorValues[4] == 1 && sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1){
            forward();
        }
        
//    Serial.println(distance);
//    activateGripper(0);
  }
 }

void getSensor() {
   for(int i = 0; i < sizeof(sensorPins) / sizeof(sensorPins[0]); i++) {
    int sensorState = analogRead(sensorPins[i]);
    sensorValues[i] = sensorState >= 800 ? 1 : 0;

    Serial.print(sensorValues[i]);
    Serial.print(" ");
    
   }
   Serial.println("");
}

void forward() {
    analogWrite(motorA1, 200); //480
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 200); //474
    analogWrite(motorB2, 0);
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

int getUltrasonicDistance() {
  digitalWrite(TrigerPin, LOW);
  delayMicroseconds(5);
  digitalWrite(TrigerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigerPin, LOW);

  long duration = pulseIn(EchoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

void activateGripper(int angle) {
  int pulseWidth = map(angle, 0, 180, 0, 255);
  digitalWrite(Gripper, HIGH);
  Serial.println(pulseWidth);
  delayMicroseconds(pulseWidth);
  digitalWrite(Gripper, LOW);
  delay(20);
}
