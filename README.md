# Arduino Robot Project

## Overview
This project involves creating a simple line-following robot using an Arduino board. The robot utilizes infrared sensors to detect lines on the ground and adjust its movement accordingly to stay on the track.

## Components
- Arduino board (Arduino Uno, Nano, etc.)
- Infrared sensors (8x)
- LED Lights
- Cliper
- Motor driver module
- DC motors (2x)
- Chassis
- Wheels (2x)
- Battery pack
- Sensor

## Setup
1. **Connections**:
   - Connect the motor driver module to the Arduino board.
   - Connect the motors to the motor driver outputs.
   - Connect the infrared sensors to analog pins on the Arduino board.
   - Connect the Sensor to the analog pins.
   - Connect the LED Lights to the analog pins.
   
2. **Code**:
   - Copy and paste the provided Arduino code into your Arduino IDE.
   - Upload the code to your Arduino board.

3. **Assemble the Robot**:
   - Mount the motors and wheels onto the chassis.
   - Attach the infrared sensors to the front of the robot, facing downwards to detect lines on the ground.

## Operation
- Power on the robot.
- Place it on a surface with a line to follow.
- The robot will use its infrared sensors to detect the line and adjust its movement accordingly.
- The robot will grab the block.
- Refer to the code comments for understanding the logic behind the robot's movements.
- The robot will continue following the line until manually turned off or encountering a specific condition (e.g., all sensors off the line).
- The robot will lave the block.

## Code Explanation
- **`setup()`**: Initializes pins for motor control and sensor reading.
- **`loop()`**: Continuously reads sensor values and adjusts the robot's movement based on the detected line or lack thereof.
- **`getSensor()`**: Reads sensor values and updates the `sensorValues` array.
- **Movement Functions**:
  - `forward()`, `backward()`, `stop()`: Control the robot's movement.
  - `left()`, `right()`: Turn the robot left or right.
  - `adjustLeft()`, `adjustRight()`: Slightly adjust the robot's direction when only one sensor detects the line.
  - `turnAround()`: Perform a 180-degree turn when all sensors are off the line.

## Notes
- Adjust the threshold value in the `getSensor()` function (`sensorState >= 800 ? 1 : 0`) according to your environment and sensor characteristics.
- Ensure proper calibration of the sensors and motors for optimal performance.
- Experiment with different track designs and sensor placements for better line-following capabilities.

## Group Memmbers:
Mahmoud Hamid
Nikita Golovanoov
