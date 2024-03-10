const int motorA1 = 7;
const int motorA2 = 6;
const int motorB1 = 5;
const int motorB2 = 4;

int sensorValues[] = {0,0,0,0,0,0,0,0};
int sensorPins[] = {A0,A1,A2,A3,A4,A5,A6,A7};
unsigned long startTime = 0; 
bool operationComplete = false; 
bool startSequenceCompleted = false;

void setup() {
  Serial.begin(9600); // Start serial communication
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  for(int i = 0; i < 8; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  startSequence(); // Begin the start sequence
}


void loop() {
  if (!startSequenceCompleted) {
    return; 
  }

  if (operationComplete) {
    return; 
  }
  
  if (operationComplete || startTime == 0) {
    return; 
  }
  
  getSensor();
  if ((sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1) || (sensorValues[6] == 1 && sensorValues[7] == 1)){
    left();
  }
  else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && 
        sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) {
    turnAround();
  }
  else if (sensorValues[2] == 1) {
    adjustRight();
  }  
  else if (sensorValues[5] == 1) {
    adjustLeft();
  }
  else {
    forward();
  }
  
  if (millis() - startTime > 10000) {
    bool allBlack = true;
    for (int i = 0; i < 8; i++) {
      if (sensorValues[i] == 0) { 
        allBlack = false;
        break;
      }
    }

    if (allBlack) {
      dropObject(); 
      backward(); 
      delay(1000); 
      stop(); 
      operationComplete = true; 
      return;
    }
  }
}

void getSensor() {
   for(int i = 0; i < 8; i++) {
    int sensorState = analogRead(sensorPins[i]);
    sensorValues[i] = sensorState >= 700 ? 1 : 0; 
    Serial.print(sensorValues[i]);
    Serial.print(" ");
   }
   Serial.println("");
}

void startSequence() {
    int whiteLineCount = 0;
    bool isOnLine = false;

    while(whiteLineCount < 2) {
        getSensor();
        bool onWhiteLine = false;
        for(int i = 0; i < 8; i++) {
            if(sensorValues[i] == 0) {
                onWhiteLine = true;
                break;
            }
        }

        if(onWhiteLine && !isOnLine) {
            whiteLineCount++;
            isOnLine = true;
        } else if(!onWhiteLine) {
            isOnLine = false;
        }

        forward();
        delay(100); 
    }

    stop(); 
    grabObject(); 
    startTime = millis(); 
    startSequenceCompleted = true; 
}



void dropObject() {
    
}

void grabObject() {
   
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
