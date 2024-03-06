const int motorA1 = 5;
const int motorA2 = 4;
const int motorB1 = 3;
const int motorB2 = 2;
const int EchoPin = 12;
const int TrigerPin = 13;
const int Gripper = 8;

int sensorValues[8];
int sensorPins[] = {A7, A6, A5, A4, A3, A2, A1, A0};

bool wait = true;
bool set = false;
bool solved = false;
bool victory = false;

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
    
    if (wait)
    {
       detectObject();
    }
    else if (!set)
    {
      entering();
    }
//    else if (!solved)
//    {
//      maze();
//    }
//    else if(!victory)
//    {
//      finish();
//    }
}




//================================================================================================//
void detectObject()
{
  int distance = getUltrasonicDistance();

  if(distance < 25)
  {
    wait = false;
  } 
}
//=========================================== CODE FOR THE GRABING THE BLOCK AND CALIBRATION ===================================================//
void entering()
{

        if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0){
            forward();
        }
        else if (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 1 && sensorValues[4] == 1 && sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1){
            forward();
        }
//    else 
    {
//      stop();  
//    }

//    int lines = 0;
//    
//    if (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 1 && sensorValues[4] == 1 && sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1)
//    {
//        forward();
//    } 
//    else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0)
//    {
//        adjustRight();
//    }
//    else if (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1)
//    {
//        adjustLeft();
//    }
        

//  set = true;
}
//================================================================================================//
//void maze()
//{
//  
//}
//================================================================================================//
//void finish(
//================================================================================================//
void activateGripper(int angle) {
  int pulseWidth = map(angle, 0, 180, 0, 255);
  digitalWrite(Gripper, HIGH);
  Serial.println(pulseWidth);
  delayMicroseconds(pulseWidth);
  digitalWrite(Gripper, LOW);
  delay(20);
}
//================================================================================================//
void getSensor() {
  for (int i = 0; i < 8; i++) {
    int sensorState = analogRead(sensorPins[i]);
    sensorValues[i] = sensorState >= 800 ? 1 : 0;

    Serial.print(sensorValues[i]);
    Serial.print(" ");
  }
  Serial.println("");
}
//================================================================================================//

//================================================================================================//

void forward() {
  analogWrite(motorA1, 200);
  analogWrite(motorA2, 0);
  analogWrite(motorB1, 200);
  analogWrite(motorB2, 0);
}

void backward() {
  analogWrite(motorA1, 0);
  analogWrite(motorA2, 200);
  analogWrite(motorB1, 0);
  analogWrite(motorB2, 200);
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
    analogWrite(motorA1, 200);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 200);
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
