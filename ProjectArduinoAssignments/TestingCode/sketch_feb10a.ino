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

  // Check if any sensor detects the black line (assuming the black line corresponds to low readings)
  bool blackDetected = false;
  for (int i = 0; i < SensorCount; i++) {
    if (sensorValues[i] < 700) { // Adjust the threshold as needed
      blackDetected = true;
      break; // Exit loop early if black is detected
    }
  }

  // If black line is detected, adjust robot movement accordingly
  if (blackDetected) {
    // Adjust the robot's movement to follow the black line
    // For example, you might want to activate different motors depending on which sensors detect the black line
    // Below is just an example, you would need to adjust it based on your robot's configuration
    digitalWrite(MotorA, HIGH); // Activate Motor A
    digitalWrite(MotorB, HIGH); // Deactivate Motor B
    // You can adjust the logic further based on which sensors detect the black line
  } else {
    // If no black line is detected, stop the robot
        digitalWrite(MotorA, LOW); // Deactivate Motor A
    digitalWrite(MotorB, LOW); // Deactivate Motor B
  }
}
