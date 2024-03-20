const int motorA1 = 7;
const int motorA2 = 6;
const int motorB1 = 5;
const int motorB2 = 4;
const int MotorR1 = 3;
const int MotorR2 = 2;

const int EchoPin = 8;
const int TrigerPin = 9;
const int Gripper = 12;
#define GRIPPER_TIME_OUT 20
#define GRIPPER_CLOSE 950
#define GRIPPER_OPEN 1600

int sensorValues[8];
int sensorPins[] = {A7, A6, A5, A4, A3, A2, A1, A0};

volatile int L = 0;
volatile int R = 0;

bool check = true;
bool first = false;
bool second = false;
bool success = false;

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

  attachInterrupt(digitalPinToInterrupt(MotorR1), ISR_L, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorR2), ISR_R, CHANGE);
}



void loop() {
    
    if (check)
    {
       detectObject();
    }
    else if (!first)
    {
      enter();
    }
   else if (!second)
   {
     maze();
   }
   else if(!success)
   {
     finish();
   }
}


//===========================================CHECK THE OBJECT===================================================//
void detectObject()
{
  int distance = getUltrasonicDistance();

  if(distance < 25)
  {
    check = false;
  } 
}
//===========================================START===================================================//
void enter() {
  delay(1000);

  int lines = 0;

  forwardSlow();

  while (true) {
    getSensor();

    forward();

    if (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 1 &&
        sensorValues[4] == 1 && sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1) {

      lines += 1;
      delay(200);
    }
    if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 &&
        sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0)
    {
      forward();
    }
    if (lines > 2)
    {
      int distance = getUltrasonicDistance();

      stop();
      delay(1000);
      activateGripper(1000);
      delay(1000);
      turnLeft(35);
      break;
    }
  }
  first = true;
}
//===========================================MAZE===================================================//

void maze() {
  getSensor();
    
  if ((sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1) || (sensorValues[6] == 1 && sensorValues[7] == 1)) {
      forward();
      delay(50);
      stop();
      delay(200);
      getSensor();

      if(sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 1 &&
         sensorValues[4] == 1 && sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1)
       {
            second = true;
       }
       else 
       {        
          turnLeft(37);
          delay(100);
       }
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
}
//===========================================FINISH===================================================//

void finish() {
      stop();
      activateGripper(1700);
      delay(500);
      back(20);
      stop();

  success = true;

}
//===========================================SENSOR===================================================//


void getSensor() {
  for (int i = 0; i < 8; i++) {
    int sensorState = analogRead(sensorPins[i]);
    sensorValues[i] = sensorState >= 800 ? 1 : 0;

    Serial.print(sensorValues[i]);
    Serial.print(" ");
  }
  Serial.println("");
}
//===============================================TURN LEFT, RIGHT, BACK [R-Motor]=================================================//

void ISR_L() {
  L++;
}

void ISR_R() {
  R++;
}
//=-=-=-=-=-=-=-=-=-=-//
void turnLeft(int d){
  L=0;
  R=0;
  
  while(L < d){
    digitalWrite(motorA1, LOW); //480
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH); //474
    digitalWrite(motorB2, LOW);

    Serial.println(L);
  }
  stop();
}
//=-=-=-=-=-=-=-=-=-=-//
void turnRight(int d){
  L=0;
  R=0;
  
  while(R < d){
    digitalWrite(motorA1, 0); //480
    digitalWrite(motorA2, 0);
    digitalWrite(motorB1, 0); //474
    digitalWrite(motorB2, 0);

    Serial.println(R);
  }
  stop();
}
//=-=-=-=-=-=-=-=-=-=-//
void back(int d) {
  L = 0;
  R = 0;

  while (R < d) {
    digitalWrite(motorA1, LOW); //480
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW); //474
    digitalWrite(motorB2, HIGH);
  }
  stop();
}
//===============================================GRIPPER=================================================//
void activateGripper(int pulse) {
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(Gripper, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(Gripper, LOW);
    delay(20);
  }
}
//===============================================DISTANCE=================================================//

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
//===============================================MOTTOR A1-A2-B1-B2=================================================//

void forward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void forwardSlow() {
  analogWrite(motorA1, 0);
  analogWrite(motorA2, 100);
  analogWrite(motorB1, 0);
  analogWrite(motorB2, 100);

}
void backward() {

  analogWrite(motorA1, 0);
  analogWrite(motorA2, 100);
  analogWrite(motorB1, 0);
  analogWrite(motorB2, 100);

}
void stop() {
  analogWrite(motorA1, 0);
  analogWrite(motorA2, 0);
  analogWrite(motorB1, 0);
  analogWrite(motorB2, 0);
}

void left() {
  analogWrite(motorA1, 0);
  analogWrite(motorA2, 150);
  analogWrite(motorB1, 150);
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
void adjustRight() {
  analogWrite(motorA1, 150);
  analogWrite(motorA2, 0);
  analogWrite(motorB1, 0);
  analogWrite(motorB2, 100);
}
void turnAround() {
  analogWrite(motorA1, 150);
  analogWrite(motorA2, 0);
  analogWrite(motorB1, 0);
  analogWrite(motorB2, 150);
}
