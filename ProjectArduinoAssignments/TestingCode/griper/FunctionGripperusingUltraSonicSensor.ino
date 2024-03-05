#include <Servo.h>

const int Gripperservo = 8;
const int echoPin = 12;
const int TriggerPin = 13;

Servo gripperServo;

void setup() {
  pinMode(TriggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  gripperServo.attach(Gripperservo);
}

void loop() {
  // Trigger the sensor
  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  // Measure the distance
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2; //Ditsance in centimeters bruh


  if (distance < 20) { 
  
    moveGripper(0);
  } 

  delay(1300); 
}

void moveGripper(int angle) {
  int pwmValue = map(angle, 0, 180, 0, 255);
  gripperServo.write(pwmValue);
}
