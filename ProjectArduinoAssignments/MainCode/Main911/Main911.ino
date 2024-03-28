#include <Adafruit_NeoPixel.h>

// Define motor pins
const int motorA1 = 7;      //Left Forward
const int motorA2 = 6;      //Left Backwards
const int motorB1 = 5;      //Right Forward
const int motorB2 = 4;      //Right Backwards
const int MotorR1 = 3;      //Rotation motor
const int MotorR2 = 2;      //Rotation motor

#define MOTOR_SLOW 100
#define MOTOR_STOP 0
#define MOTOR_AVARAGE 150

// Define ultrasonic sensor pins
const int EchoPin = 8;      //Recieve
const int TrigerPin = 9;    //Send

// Define gripper pin and constants
const int Gripper = 12;     //Gripper
#define GRIPPER_TIME_OUT 20
#define GRIPPER_CLOSE 950
#define GRIPPER_OPEN 1600

// Array to hold sensor values and sensor pins
int sensorValues[] = {0, 0, 0, 0, 0, 0, 0, 0};
int sensorPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};

// Variables to track motor interrupts
volatile int L = 0;
volatile int R = 0;

// Boolean flags for different stages of operation
bool wait = true;
bool set = false;
bool solved = false;
bool ending = false;

// Define the number of NeoPixel LEDs and the pin they are connected to
#define NUM_PIXELS 4
#define NEOPIN 10

// Define RGB colors using Adafruit_NeoPixel library
#define YELLOW pixels.Color(255, 255, 0)
#define WHITE pixels.Color(255, 255, 255)
#define GREEN pixels.Color(0, 255, 0)
#define RED pixels.Color(255, 0, 0)
#define OFF pixels.Color(0, 0, 0)
#define BLUE pixels.Color(0, 0, 255)

int colorValues[] = {0, 0, 0, 0, 0, 0};

// Initialize NeoPixel object with defined number of pixels and pin
Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIN, NEO_RGB + NEO_KHZ800);
//===========================================SET UP===================================================//

void setup() {
  // Initialize motor pins
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  // Initialize sensor pins
  for (int i = 0; i < 8; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  // Initialize ultrasonic sensor pins
  pinMode(EchoPin, INPUT);
  pinMode(TrigerPin, OUTPUT);

  // Initialize gripper pin
  pinMode(Gripper, OUTPUT);

  // Attach interrupts for motor tracking
  attachInterrupt(digitalPinToInterrupt(MotorR1), ISR_L, CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorR2), ISR_R, CHANGE);

  pixels.begin();

  lightsOff();
}
//===========================================LOOP===================================================//
void loop() {

  if (wait) {
    detectObject();
  }
  else if (!set) {
    enter();
  }
  else if (!solved) {
    maze();
  }
  else if (!ending) {
    finish();
  }
}
//===========================================CHECK THE OBJECT===================================================//
// Function to check if an object is detected

void detectObject() {
  // Change all lights to green
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, GREEN);
  }
  pixels.show();

  int distance = getUltrasonicDistance();

  if (distance < 25) {
    wait = false;
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

    if (allBlackSensors()) {
      lines += 1;
      delay(200);
    }
    if (allWhiteSensors()) {
      forward();
    }
    if (lines > 2) {
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
//===========================================MAZE===================================================//
void maze() {
  getSensor();

  if (leftSensors()) {
    forward();
    delay(50);
    stop();
    delay(200);
    getSensor();

    if (allBlackSensors()) {
      solved = true;
    }
    else {
      turnLeft(37);
      delay(100);
    }
  }
  else if (allWhiteSensors()) {
    turnAround();
  }
  else if (adjustRightSensors()) {
    adjustRight();
  }
  else if (adjustLeftSensors()) {
    adjustLeft();
  }
  else {
    forward();
  }
}
//===========================================FINISH===================================================//
// Function for the finishing stage
void finish() {
  stop();
  activateGripper(1700);
  delay(500);
  back(30);
  stop();
  ending = true;
  noInterrupts();
  while (true) {
    turnAroundLight();
    delay(200);
    forwardLights();
    delay(200);
  }
}
//===============================================BOOL=================================================//

bool allBlackSensors() {
  return (sensorValues[0] == 1 && sensorValues[1] == 1 && sensorValues[2] == 1 && sensorValues[3] == 1 &&
          sensorValues[4] == 1 && sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1);
}

bool leftSensors() {
  return ((sensorValues[5] == 1 && sensorValues[6] == 1 && sensorValues[7] == 1) || (sensorValues[6] == 1 && sensorValues[7] == 1));
}

bool allWhiteSensors() {
  return (sensorValues[0] == 0 && sensorValues[1] == 0 && sensorValues[2] == 0 && sensorValues[3] == 0 &&
          sensorValues[4] == 0 && sensorValues[5] == 0 && sensorValues[6] == 0 && sensorValues[7] == 0);
}

bool adjustRightSensors() {
  return (sensorValues[2] == 1);
}

bool adjustLeftSensors() {
  return (sensorValues[5] == 1);
}
//===========================================SENSOR===================================================//
// Function to read sensor values

void getSensor() {
  for (int i = 0; i < 8; i++) {
    int sensorState = analogRead(sensorPins[i]);
    sensorValues[i] = sensorState >= 800 ? 1 : 0;
  }
}
//===============================================TURN LEFT, RIGHT, BACK [R-Motor]=================================================//
// Interrupt service routine
void ISR_L() {
  L++;
}

void ISR_R() {
  R++;
}

//=-=-=-=-=-=-=-=-=-=-//
// Function to turn left by a certain degree
void turnLeft(int d) {
  L = 0;
  R = 0;

  while (L < d) {
    leftLights();
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
  }
  stop();
}
//=-=-=-=-=-=-=-=-=-=-//
// Function to turn right by a certain degree
void turnRight(int d) {
  L = 0;
  R = 0;

  while (R < d) {
    rightLights();
    digitalWrite(motorA1, 0);
    digitalWrite(motorA2, 0);
    digitalWrite(motorB1, 0);
    digitalWrite(motorB2, 0);
  }
  stop();
}
//=-=-=-=-=-=-=-=-=-=-//
// Function to go back by a certain degree
void back(int d) {
  L = 0;
  R = 0;

  while (R < d) {
    normalLights();
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
  }
  stop();
}
//===============================================GRIPPER=================================================//
// Function that activates the gripper

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
//function that gett the distanse

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
  forwardLights();
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void forwardSlow() {
  StartLights(NUM_PIXELS);
  analogWrite(motorA1, MOTOR_SLOW);
  analogWrite(motorA2, MOTOR_STOP);
  analogWrite(motorB1, MOTOR_SLOW);
  analogWrite(motorB2, MOTOR_STOP);

}
void backward() {
  normalLights();
  analogWrite(motorA1, MOTOR_STOP);
  analogWrite(motorA2, MOTOR_SLOW);
  analogWrite(motorB1, MOTOR_STOP);
  analogWrite(motorB2, MOTOR_SLOW);

}
void stop() {
  stopLights();
  analogWrite(motorA1, MOTOR_STOP);
  analogWrite(motorA2, MOTOR_STOP);
  analogWrite(motorB1, MOTOR_STOP);
  analogWrite(motorB2, MOTOR_STOP);
}

void left() {
  leftLights();
  analogWrite(motorA1, MOTOR_STOP);
  analogWrite(motorA2, MOTOR_AVARAGE);
  analogWrite(motorB1, MOTOR_AVARAGE);
  analogWrite(motorB2, MOTOR_STOP);
}

void right() {
  rightLights();
  analogWrite(motorA1, MOTOR_SLOW);
  analogWrite(motorA2, MOTOR_STOP);
  analogWrite(motorB1, MOTOR_STOP);
  analogWrite(motorB2, MOTOR_SLOW);
}

void adjustLeft() {
  analogWrite(motorA1, MOTOR_STOP);
  analogWrite(motorA2, MOTOR_SLOW);
  analogWrite(motorB1, MOTOR_AVARAGE);
  analogWrite(motorB2, MOTOR_STOP);
}
void adjustRight() {
  analogWrite(motorA1, MOTOR_AVARAGE);
  analogWrite(motorA2, MOTOR_STOP);
  analogWrite(motorB1, MOTOR_STOP);
  analogWrite(motorB2, MOTOR_SLOW);
}
void turnAround() {
  turnAroundLight();
  analogWrite(motorA1, MOTOR_AVARAGE);
  analogWrite(motorA2, MOTOR_STOP);
  analogWrite(motorB1, MOTOR_STOP);
  analogWrite(motorB2, MOTOR_AVARAGE);
}

//===============================================MOTTOR LIGHTS=================================================//
// Function to set specific LEDs to represent left movement
void leftLights() {
  pixels.setPixelColor(0, YELLOW); // Yellow
  pixels.setPixelColor(1, WHITE); // Yellow
  pixels.setPixelColor(2, WHITE);  // White
  pixels.setPixelColor(3, YELLOW);  // White
  pixels.show();
}

// Function to set all LEDs to represent turning movement
void rightLights() {
  pixels.setPixelColor(0, WHITE); // Yellow
  pixels.setPixelColor(1, YELLOW); // Yellow
  pixels.setPixelColor(2, YELLOW); // Yellow
  pixels.setPixelColor(3, WHITE); // Yellow
  pixels.show();
}

// Function to set all LEDs to represent stopped movement
void stopLights() {
  pixels.setPixelColor(0, GREEN); // Green
  pixels.setPixelColor(1, GREEN); // Green
  pixels.setPixelColor(2, WHITE); // White
  pixels.setPixelColor(3, WHITE); // White
  pixels.show(); // Update LEDs with new colors
}

// Function to set specific LED to represent starting movement
void StartLights(int lightNR) {
  pixels.setPixelColor(lightNR, BLUE); // Blue
  pixels.show(); // Update LEDs with new colors
}

// Function to set all LEDs to represent forward movement
void forwardLights() {
  pixels.setPixelColor(0, GREEN); // Green
  pixels.setPixelColor(1, GREEN); // Green
  pixels.setPixelColor(2, GREEN); // Green
  pixels.setPixelColor(3, GREEN); // Green
  pixels.show(); // Update LEDs with new colors
}

// Function to set all LEDs to represent normal state
void normalLights() {
  pixels.setPixelColor(0, WHITE); // White
  pixels.setPixelColor(1, WHITE); // White
  pixels.setPixelColor(2, WHITE); // White
  pixels.setPixelColor(3, WHITE); // White
  pixels.show(); // Update LEDs with new colors
}

// Function to set all LEDs to represent turning around movement
void turnAroundLight() {
  pixels.setPixelColor(0, RED); // Red
  pixels.setPixelColor(1, RED); // Red
  pixels.setPixelColor(2, RED); // Red
  pixels.setPixelColor(3, RED); // Red
  pixels.show(); // Update LEDs with new colors
}

// Function to set all LEDs to be turned off
void lightsOff() {
  pixels.setPixelColor(0, OFF); // Off
  pixels.setPixelColor(1, OFF); // Off
  pixels.setPixelColor(2, OFF); // Off
  pixels.setPixelColor(3, OFF); // Off
  pixels.show(); // Update LEDs with new colors
}
void detectLights() {
  pixels.setPixelColor(0, GREEN);
  pixels.setPixelColor(1, GREEN);
  pixels.setPixelColor(2, GREEN);
  pixels.setPixelColor(3, GREEN);
  pixels.show();
}
