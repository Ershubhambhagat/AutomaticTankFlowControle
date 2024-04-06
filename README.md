# AutomaticTankFlowControle

# Arduino Uno Automation Project

## Problem Statement
The automation system is designed to address the common issue where individuals either do not want to manually switch the motor on/off or tend to forget to turn off the motor after use. The goal is to create a reliable system that can manage the motor's operation autonomously, ensuring that it turns on when needed and, more importantly, turns off when not in use to prevent wastage of electricity and potential safety hazards.

## Project Overview
This project involves the creation of an automated system using an **Arduino Uno**, an **ultrasonic sensor**, and a **relay** to control a motor. The goal is to design a system that can autonomously start and stop the motor based on certain conditions detected by the ultrasonic sensor.

## Components
- **Arduino Uno**: The central controller for the automation system.
- **Ultrasonic Sensor**: Used to detect the presence or absence of an object or person at a certain distance.
- **Relay Module**: Acts as an electronic switch to control the power to the motor.


## Potential Solutions
- **Check Connections**: Ensure all components are properly connected, and there are no loose connections.
- **Verify Code**: Review the Arduino sketch to make sure the logic for starting and stopping the motor is correct.
- **Sensor Calibration**: Calibrate the ultrasonic sensor to accurately detect the required distances.
- **Test Relay**: Confirm that the relay is functioning correctly and is able to switch the motor on and off.

## Chaser LED Indicator
To enhance the functionality of the automation system, a **chaser LED** is incorporated to indicate the motor's status. When the motor is off, the chaser LED activates, providing a visual cue that the system is in standby mode. This feature not only serves as a reminder that the motor is not currently in use but also adds an aesthetic element to the setup.

### Features
- **Visual Indicator**: The chaser LED lights up in a sequence to clearly show that the motor is off.
- **Energy Efficient**: LEDs consume minimal power, making it an eco-friendly indicator option.
- **Safety Measure**: Acts as a safety feature by visually confirming the motor is not accidentally left running.

By integrating the chaser LED, users can easily ascertain the operational state of the motor at a glance, ensuring better control and safety of the automated system.



## Conclusion
This automation project aims to simplify tasks by using sensor data to control a motor. With proper setup and troubleshooting, the system will be able to operate the motor without manual intervention, providing a seamless automated experience.




Code Discription




## Arduino Code Explanation

This Arduino script is designed to automate a motor using an ultrasonic sensor for water level detection and a relay for motor control. Additionally, a series of LEDs provide a chaser effect when the motor is off.

### Code Components
- **Ultrasonic Sensor**: Utilizes pins 2 (trigger) and 5 (echo) to measure water level.
- **Relay**: Connected to pin 8, controls the motor's power state.
- **LEDs**: Pins 7, 6, 3, 9, and 11 are used for the chaser LEDs, indicating the motor's off state.

### Constants
- `WaitForIncreaseWater`: A delay constant set for 5 minutes (300,000 milliseconds).
- `intervaltoraginal`: A shorter delay for operations, set for 3 seconds (300 milliseconds).
- `DeepSleep`: A long delay for entering a deep sleep mode, set for 50 minutes (3,000,000 milliseconds).
- `OnMotor15` and `OffMotor10`: Water level thresholds for turning the motor on (15 inches) and off (10 inches).
- `SensorNotWorking35`: A threshold to check if the sensor is not working properly (35 inches).

### Setup Function
Initializes the serial communication, sets the relay and LED pins as outputs.

### Loop Function
The main loop starts by triggering the ultrasonic sensor to measure the water level. If the water level is at or below 10 inches, it activates the chaser LEDs in a back-and-forth pattern and turns the relay (and thus the motor) off. If the water level is above 35 inches, it prints a message indicating the sensor is not working.

### Chaser LED Pattern
When the water level is low, the chaser LEDs light up sequentially, creating a visual alert that the motor is off.

.
### Pump On Logic
If the water level is less than or equal to 15 inches, the system starts the motor and activates the chaser LEDs. The system then waits for 5 minutes (as defined by `WaitForIncreaseWater`) before checking the water level again.

If the water level has not increased after 5 minutes, the system turns off the motor and activates the chaser LEDs. If the water level has increased, the system enters a while loop where it continues to check the water level as long as it is greater than or equal to 10 inches (`OffMotor10`). Inside this loop, the chaser LEDs are activated.

This logic ensures that the motor is only running when necessary, i.e., when the water level is below a certain threshold. It also ensures that the motor is turned off when the water level reaches a certain height, preventing overflow.

### While Loop and Final Else Statement
The while loop continues to check the water level as long as it is greater than or equal to 10 inches (`OffMotor10`). Inside this loop, the chaser LEDs are activated and the water level is checked again. If the water level is still greater than or equal to `OffMotor10`, the system stays in the while loop, continuously checking the water level and activating the chaser LEDs.

If the water level drops below `OffMotor10`, the system exits the while loop and checks the final else statement. If the water level is not greater than `OnMotor15` and not less than or equal to `OffMotor10`, the system assumes that the tank is full or the water level has not increased. It then turns off the motor, activates the chaser LEDs, and prints the current water level.

### Function: microsecondsToInches
This function converts the time taken for the ultrasonic wave to travel to the water surface and back into inches. The speed of sound in air is approximately 1125 feet per second, which is equivalent to 74 microseconds per inch. The round trip is divided by 2.

This function is used to convert the duration returned by `pulseIn()` into a distance, allowing the system to measure the water level in inches.

