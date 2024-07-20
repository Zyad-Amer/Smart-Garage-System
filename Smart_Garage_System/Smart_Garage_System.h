/*
 * Smart_Garage_System.h
 *
 *  Created on: Jul 6, 2024
 *      Author: Zyad Montaser
 */

#ifndef SMART_GARAGE_SYSTEM_H_
#define SMART_GARAGE_SYSTEM_H_

#include "lcd.h"
#include "keypad.h"
#include "gpio.h"
#include "adc.h"
#include "Servo_Motor.h"
#include <avr/io.h> /*for SREG register*/
#include <avr/interrupt.h> /* for external interrupt*/
#include <util/delay.h> /*for delay function*/
#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Max_CARS_NUMBER 3
#define ADC_THRESHOLD 511 /* 1023/2=511 */
#define ADC_CHANNEL 0

#define EQUALBUTTON '='

#define PASSWORD_SIZE 5
#define UNMATCHED_PASSWORDS    10 /*any random number */
#define MATCHED_PASSWORDS      20/*any random number */

#define INPUT 0
#define INT_0 0
#define INT_1 1
#define FALLING_EDGE 2
/*******************************************************************************
 *                         Types Declarations                                   *
 *******************************************************************************/
typedef enum
{
	/*Enumeration to define the garage states*/
	Busy,Available
}Garage_State;

typedef enum
{
	/*Enumeration to define the garage state*/
	Untriggered,triggered
}Flag_State;

/*******************************************************************************
 *                      Global Variables                                   *
 *******************************************************************************/
uint8 Cars_Number=0;
uint8 INT0_IR1_FLAG=Untriggered;
uint8 INT1_IR2_FLAG=Untriggered;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*function to change the state of the garage on LCD from available to busy*/
void changeToBusyOnLCD (void);

/*function to change the number of cars on the LCD*/
void changeCarsNumberOnLCD(void);

/*function to open the arm gate then wait the car to pass then close it again*/
void enterTheCar(void);

uint8 compareArrays(uint8 *arr1,uint8 *arr2,uint8 size);
void getPassword(uint8 *pass,uint8 size,uint8 firstPlace);
void CreatePassword(void);

void EXTI_vConfig_(uint8 copy_u8Int_No , uint8 copy_u8Dirn_Of_Pin , uint8 copy_u8Sense_Opt);

void changeToAvailableOnLCD(void);

void Exit_TheCar(void);

#endif /* SMART_GARAGE_SYSTEM_H_ */
