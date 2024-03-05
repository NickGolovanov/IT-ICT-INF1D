## Overview
This project involves creating a simple line-following robot using an Arduino board. The robot utilizes infrared sensors to detect lines on the ground and adjust its movement accordingly to stay on the track. Additionally, a new function has been added to the robot, allowing it to use an ultrasonic sensor to grab objects using a gripper mechanism.

## Components
- Arduino board (Arduino Uno, Nano, etc.)
- Infrared sensors (8x)
- LED Lights
- Clipper
- Motor driver module
- DC motors (2x)
- Chassis
- Wheels (2x)
- Battery pack
- Ultrasonic sensor
- Gripper mechanism

## Setup
### Connections:
1. Connect the motor driver module to the Arduino board.
2. Connect the motors to the motor driver outputs.
3. Connect the infrared sensors to analog pins on the Arduino board.
4. Connect the ultrasonic sensor to designated pins on the Arduino board.
5. Connect the LED Lights to the analog pins.
6. Connect the gripper mechanism to a designated pin on the Arduino board.

### Code:
1. Copy and paste the provided Arduino code into your Arduino IDE.
2. Upload the code to your Arduino board.

## Assemble the Robot
1. Mount the motors and wheels onto the chassis.
2. Attach the infrared sensors to the front of the robot, facing downwards to detect lines on the ground.
3. Install the ultrasonic sensor and gripper mechanism as per their respective instructions.

## Operation
1. Power on the robot.
2. Place it on a surface with a line to follow.
3. The robot will use its infrared sensors to detect the line and adjust its movement accordingly.
4. The robot can now also grab objects using the ultrasonic sensor and gripper mechanism.
5. Refer to the code comments for understanding the logic behind the robot's movements and gripper operation.
6. The robot will continue following the line until manually turned off or encountering a specific condition (e.g., all sensors off the line).

## Code Explanation
### setup():
- Initializes pins for motor control, sensor reading, ultrasonic sensor, and gripper mechanism.

### loop():
- Continuously reads sensor values and adjusts the robot's movement based on the detected line or lack thereof.
- Checks ultrasonic sensor for object detection and triggers gripper mechanism accordingly.

### getSensor():
- Reads sensor values and updates the sensorValues array.

### Movement Functions:
- `forward()`, `backward()`, `stop()`: Control the robot's movement.
- `left()`, `right()`: Turn the robot left or right.
- `adjustLeft()`, `adjustRight()`: Slightly adjust the robot's direction when only one sensor detects the line.
- `turnAround()`: Perform a 180-degree turn when all sensors are off the line.

### activateGripper():
- Controls the gripper mechanism based on the specified angle.

## Notes
1. Adjust the threshold value in the `getSensor()` function according to your environment and sensor characteristics.
2. Ensure proper calibration of the sensors, motors, ultrasonic sensor, and gripper mechanism for optimal performance.
3. Experiment with different track designs and sensor placements for better line-following capabilities and gripper operation.

---
