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
