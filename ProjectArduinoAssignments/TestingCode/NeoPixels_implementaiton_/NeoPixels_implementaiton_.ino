#include <Adafruit_NeoPixel.h>

const int motorA1 = 7;
const int motorA2 = 6;
const int motorB1 = 5;
const int motorB2 = 4;
const int MotorR1 = 3;
const int MotorR2 = 2;

#define NUM_PIXELS 4
#define NEOPIN 10

#define YELLOW pixels.Color(255, 255, 0)
#define WHITE pixels.Color(255, 255, 255)
#define GREEN pixels.Color(0, 255, 0)
#define RED pixels.Color(255, 0, 0)
#define OFF pixels.Color(0, 0, 0)
#define BLUE pixels.Color(0, 0, 255)


int colorValues[] = {0, 0, 0, 0, 0, 0};

const int EchoPin = 8; 
const int TrigerPin = 9; 
const int Gripper = 12; 
#define GRIPPER_TIME_OUT 20
#define GRIPPER_CLOSE 950
#define GRIPPER_OPEN 1600

Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

int sensorValues[] = {0,0,0,0,0,0,0,0};
int sensorPins[] = {A0,A1,A2,A3,A4,A5,A6,A7};

bool wait = true;
bool set = false;
bool solved = false;

volatile int L = 0;
volatile int R = 0;

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

  pinMode(EchoPin, INPUT);
  pinMode(TrigerPin, OUTPUT);
  pinMode(Gripper, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(MotorR1), ISR_L, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorR2), ISR_R, CHANGE);

  pixels.begin();

  lightsOff();
}

void loop() {

  if(wait){
    detec();
  }
  else if(!set){
    enter();
  }
  else if (!solved){
    maze();
  }
}

void enter(){
  delay(1000);

  int lines = 0;

  forwardSlow();

  while(true){
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
//        else if (sensorValues[2] == 1) {
//          adjustRight();
//        }  
//        else if (sensorValues[5] == 1) {
//          adjustLeft();
//        }
//      else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[5] == 1 || sensorValues[6] == 1 || sensorValues[7] == 1)
//      {
//        adjustRight();
//      }
//      else if (sensorValues[0] == 1 || sensorValues[1] == 1 || sensorValues[2] == 1 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0)
//      {
//        adjustLeft();
//      }

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
  set = true;
}

void maze(){
  getSensor();
  
//  if (sensorValues[3] == 1 || sensorValues[4] == 1) {
//    forward();
//  }
//  else if ((sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1) || (sensorValues[0] == 1 && sensorValues[1] == 1)){
//    right();
//  }
  if ((sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1) || (sensorValues[6] == 1 && sensorValues[7] == 1)){
    turnLeft(37);
    delay(600);
  }
  else if (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 && 
        sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0) {
      // If all sensors are off the line, turn around
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


void getSensor(){
   for(int i = 0; i < sizeof(sensorPins) / sizeof(sensorPins[0]); i++) {
    int sensorState = analogRead(sensorPins[i]);
    sensorValues[i] = sensorState >= 800 ? 1 : 0;

    Serial.print(sensorValues[i]);
    Serial.print(" ");
    
   }
   Serial.println("");
}

void ISR_L() {
  L++;
}

void ISR_R() {
  R++;
}

void turnLeft(int d){
  L=0;
  R=0;
  
  while(L < d){
    turnLights();
    digitalWrite(motorA1, LOW); //480
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH); //474
    digitalWrite(motorB2, LOW);

    Serial.println(L);
  }
  stop();
}

void turnRight(int d){
  L=0;
  R=0;
  
  while(R < d){
    turnLights();
    digitalWrite(motorA1, HIGH); //480
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, LOW); //474
    digitalWrite(motorB2, LOW);

    Serial.println(R);
  }
  stop();
}

void forward(){
    forwardLights();
    digitalWrite(motorA1, HIGH); //480
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH); //474
    digitalWrite(motorB2, LOW);
 }

void forwardSlow(){
    StartLights(NUM_PIXELS);
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 100); // 480
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 100); // 474
  
}
void backward(){
    normalLights();
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 200); // 480
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 200); // 474

}
void stop() {
    stopLights();
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
}

void left() {
    turnLights();
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 200);
    analogWrite(motorB1, 200);
    analogWrite(motorB2, 0);
}

void right() {
    turnLights();
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
void adjustRight(){;
    turnLights();
    analogWrite(motorA1, 150);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 100);
}
void turnAround(){
    turnAroundLight();
    analogWrite(motorA1, 150);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 150);
}

//void activateGripper(int angle) {
//  int pulseWidth = map(angle, 0, 180, 0, 255);
//    digitalWrite(Gripper, HIGH);
//    Serial.println(pulseWidth);
//    delayMicroseconds(pulseWidth);
//    digitalWrite(Gripper, LOW);
//    delay(20);
//  }

void activateGripper(int pulse) {
  for (int i = 0; i < 10; i++)
  {
    digitalWrite(Gripper, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(Gripper, LOW);
    delay(20);
  }

} 

//void gripperToggle() {
//  if (millis() > timer) {
//    if (state == false) {
//      gripper(GRIPPER_OPEN);
//      state = true;
//    } else {
//      gripper(GRIPPER_CLOSE);
//      state = false;
//    }
//    timer = millis() + GRIPPER_TOGGLE;
//  }
//}

void leftLights()
{
    pixels.setPixelColor(0, YELLOW); // Yellow
    pixels.setPixelColor(1, YELLOW); // Yellow
    pixels.setPixelColor(2, WHITE);  // White
    pixels.setPixelColor(3, WHITE);  // White
    pixels.show();
}

void turnLights()
{
   pixels.setPixelColor(0, YELLOW); // Yellow
   pixels.setPixelColor(1, YELLOW); // Yellow
   pixels.setPixelColor(2, YELLOW); // Yellow
   pixels.setPixelColor(3, YELLOW); // Yellow
   pixels.show();
}

void stopLights()
{
  pixels.setPixelColor(0, GREEN);
  pixels.setPixelColor(1, GREEN);
  pixels.setPixelColor(2, WHITE);
  pixels.setPixelColor(3, WHITE);
  pixels.show();
}

void StartLights(int lightNR)
{
  pixels.setPixelColor(lightNR, BLUE);
  pixels.show();
}

void forwardLights()
{
  pixels.setPixelColor(0, GREEN);
  pixels.setPixelColor(1, GREEN); 
  pixels.setPixelColor(2, GREEN);  
  pixels.setPixelColor(3, GREEN);
  pixels.show();
}

void normalLights() 
{
  pixels.setPixelColor(0, WHITE);
  pixels.setPixelColor(1, WHITE);
  pixels.setPixelColor(2, WHITE);
  pixels.setPixelColor(3, WHITE);
  pixels.show();
}

void turnAroundLight() 
{
  pixels.setPixelColor(0, RED);
  pixels.setPixelColor(1, RED);
  pixels.setPixelColor(2, RED); 
  pixels.setPixelColor(3, RED);  
  pixels.show();
}
void lightsOff()
{
  pixels.setPixelColor(0, OFF);
  pixels.setPixelColor(1, OFF);
  pixels.setPixelColor(2, OFF);
  pixels.setPixelColor(3, OFF);
  pixels.show();
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

void detec(){

  int distcance = getUltrasonicDistance();

   if(distcance < 25)
  {
    wait = false;
  } 
}
