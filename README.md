Smart Garage System
This Smart Garage System project is designed to manage and secure a garage with various automated features. The system includes a car count display, automated arm gate control, automatic lighting, and password protection. This document provides an overview of the features, setup, and functionality of the Smart Garage System.

Features
Car Count Display:
Displays the number of cars inside the garage on an LCD.
Shows the garage state as "Available" or "Busy" based on the capacity.
Automated Arm Gate:
Controlled by a servo motor.
Opens and closes automatically to allow cars to enter and exit.
Automatic Lighting:
The garage lighting system automatically turns on at night and off during the day.
Password Protection:
Requires a password to access certain functionalities.
Users can create and confirm passwords for secure access.
Setup and Configuration
Hardware Requirements
Microcontroller (e.g., AVR)
LCD display
Servo motor
IR sensors
Keypad
ADC module
LEDs and necessary resistors
Push buttons or switches
Breadboard and connecting wires
Software Requirements
AVR-GCC or equivalent compiler
AVR programmer
Pin Configuration
LCD: Connect as per the lcd.h library configurations.
Servo Motor: Connect to a suitable PWM pin.
IR Sensors: Connected to PD2 (INT0) and PD3 (INT1).
LED: Connected to PD0.
Keypad: Connect to the microcontroller as per the keypad.h library.

Code Overview
Functions
changeToBusyOnLCD: Updates the garage state to "Busy" on the LCD.
changeCarsNumberOnLCD: Updates the car count on the LCD.
enterTheCar: Opens the gate for a car to enter, waits for the car to pass, and then closes the gate.
compareArrays: Compares two arrays to check if they match.
getPassword: Captures a password from the user.
CreatePassword: Guides the user to create and confirm a password.
EXTI_vConfig_: Configures external interrupts.
changeToAvailableOnLCD: Updates the garage state to "Available" on the LCD.
Exit_TheCar: Opens the gate for a car to exit, waits for the car to pass, and then closes the gate.
Interrupt Service Routines (ISRs)
ISR(INT0_vect): Handles the interrupt triggered by the first IR sensor.
ISR(INT1_vect): Handles the interrupt triggered by the second IR sensor.
Usage
Setup Hardware: Connect all components as per the pin configuration.
Compile and Upload: Compile the code using AVR-GCC or equivalent and upload it to the microcontroller.
Run the System: Power on the system. The LCD will display the number of cars and the garage state. The system will automatically control the gate and lighting based on car entry/exit and ambient light conditions.
