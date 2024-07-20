# Smart Garage System

## Overview

The Smart Garage System project is designed to manage and secure a garage with various automated features. It includes:

- **Car Count Display**: Shows the number of cars inside the garage and indicates if the garage is "Available" or "Busy".
- **Automated Arm Gate**: Controlled by a servo motor to automatically open and close for car entry and exit.
- **Automatic Lighting**: Turns on the garage lights at night and off during the day.
- **Password Protection**: Requires a password for accessing certain functionalities, allowing users to create and confirm passwords for secure access.

## Features

- **Car Count Display**: Displays the car count and garage state on an LCD.
- **Automated Arm Gate**: Servo motor controlled for automatic gate operation.
- **Automatic Lighting**: Lights controlled based on time of day.
- **Password Protection**: Secure access through password creation and confirmation.

## Setup and Configuration

### Hardware Requirements

- Microcontroller (e.g., AVR)
- LCD display
- Servo motor
- IR sensors
- Keypad
- ADC module
- LEDs and resistors
- Push buttons or switches
- Breadboard and connecting wires

### Software Requirements

- AVR-GCC or equivalent compiler
- AVR programmer

### Pin Configuration

- **LCD**: Connect as per the `lcd.h` library configurations.
- **Servo Motor**: Connect to a suitable PWM pin.
- **IR Sensors**: Connect to PD2 (INT0) and PD3 (INT1).
- **LED**: Connect to PD0.
- **Keypad**: Connect to the microcontroller as per the `keypad.h` library.

## Code Overview

### Functions

- **changeToBusyOnLCD**: Updates the LCD to show "Busy".
- **changeCarsNumberOnLCD**: Updates the car count on the LCD.
- **enterTheCar**: Opens the gate for car entry, waits for the car to pass, then closes the gate.
- **compareArrays**: Compares two arrays to check for matches.
- **getPassword**: Captures a user password.
- **CreatePassword**: Guides users to create and confirm a password.
- **EXTI_vConfig_**: Configures external interrupts.
- **changeToAvailableOnLCD**: Updates the LCD to show "Available".
- **Exit_TheCar**: Opens the gate for car exit, waits for the car to pass, then closes the gate.

### Interrupt Service Routines (ISRs)

- **ISR(INT0_vect)**: Handles interrupt from the first IR sensor.
- **ISR(INT1_vect)**: Handles interrupt from the second IR sensor.

## Usage

1. **Setup Hardware**: Connect all components as per the pin configuration.
2. **Compile and Upload**: Compile the code using AVR-GCC or an equivalent compiler and upload it to the microcontroller.
3. **Run the System**: Power on the system. The LCD will display the number of cars and the garage state. The system will automatically manage the gate and lighting based on car activity and ambient light conditions.
