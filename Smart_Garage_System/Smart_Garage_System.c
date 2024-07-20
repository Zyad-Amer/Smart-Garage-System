/*
 * Smart_Garage_System.c
 *
 *  Created on: Jul 6, 2024
 *      Author: Zyad Montaser
 */

#include "Smart_Garage_System.h"

int main()
{
	uint16 ADC_result=0;

	/* Create configuration structure for ADC driver */
	ADC_ConfigType ADC_Configurations = {AVCC,F_CPU_64};

	SREG |=(1<<7);/*enable I-Bit for external interrupt*/

	/*set the direction of led pin PD0 as output*/
	GPIO_setupPinDirection(PORTD_ID,PIN0_ID,PIN_OUTPUT);

	/*set the direction of the switches pins PD2 & PD3 as input (IR simulators)*/
	GPIO_setupPinDirection(PORTD_ID,PIN2_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTD_ID,PIN3_ID,PIN_INPUT);

	/*Activating the internal pullup for pins PD2 & PD3*/
	GPIO_writePin(PORTD_ID,PIN2_ID,1);
	GPIO_writePin(PORTD_ID,PIN3_ID,1);

	/* initialize the led to be turned off*/
	GPIO_writePin(PORTD_ID,PIN0_ID,LOGIC_LOW);

	/*passing the configuration structure to the function by address*/
	ADC_init(&ADC_Configurations);

	LCD_init();/*initialize the LCD */

	SERVO_MOTOR_vInit(); /*initialize the LCD */

	CreatePassword();

	/*Display number of cars inside the garage on LCD*/
	LCD_clearScreen();
	LCD_displayString("Cars Number =0");

	/*Display the garage state on LCD*/
	LCD_moveCursor(1,0);
	LCD_displayString("State: Available");

	/*INTIALIZING INT0 and INT0*/
	EXTI_vConfig_( INT_0 , INPUT , FALLING_EDGE);
	EXTI_vConfig_(INT_1 , INPUT , FALLING_EDGE);

	while(1)
	{
		ADC_result=ADC_readChannel(ADC_CHANNEL);

		/* at the night*/
		if(ADC_result >= ADC_THRESHOLD)
		{
			GPIO_writePin(PORTD_ID,PIN0_ID,LOGIC_HIGH);/*turn on the led*/
		}

		/* at the Day light*/
		else if(ADC_result < ADC_THRESHOLD)
		{
			GPIO_writePin(PORTD_ID,PIN0_ID,LOGIC_LOW);/*turn off the led*/
		}


		/*check if the IR sensor 1 detect a car(if external interrupt 0 triggered)*/
		if(INT0_IR1_FLAG==triggered)
		{
			if(Cars_Number == Max_CARS_NUMBER)
			{
				changeToBusyOnLCD(); /*change the garage state to busy on lcd*/
			}
			else
			{
				/*open the arm gate then wait the car to pass then close it again*/
				enterTheCar();

				if (Cars_Number == (Max_CARS_NUMBER - 1))
				{
					changeToBusyOnLCD();/*change the garage state to busy on lcd*/
				}

				Cars_Number++; /*add the entered car to the counter*/
				changeCarsNumberOnLCD();/*change the number of cars on the LCD*/
			}
			INT0_IR1_FLAG=0; /*clear the interrupt flag for the next time*/
		}

		//check if the IR sensor 2 detect a car(if external interrupt 1 triggered)/
		if(INT1_IR2_FLAG==triggered)
		{
			if(Cars_Number == Max_CARS_NUMBER)
			{
				//Opening the gate for car to pass and waiting till pass and closing the gate again
				Exit_TheCar();

				//Displaying Available Word on lcd
				changeToAvailableOnLCD();

				//decrement the cars number by one
				Cars_Number-- ;

				changeCarsNumberOnLCD();/*change the number of cars on the LCD*/
			}
			else
			{
				//Opening the gate for car to pass and waiting till pass and closing the gate again
				Exit_TheCar();

				//decrement the cars number by one
				Cars_Number-- ;

				changeCarsNumberOnLCD();/*change the number of cars on the LCD*/
			}
		  	INT1_IR2_FLAG=0; /*clear the interrupt flag for the next time*/
		}
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

ISR(INT0_vect)
{
	INT0_IR1_FLAG=1; /*trigger the int0 flag to indicate that the interrupt ocuur*/
	SET_BIT(GIFR,6); /*clear the interrupt flag for the next time*/
}

ISR(INT1_vect)
{
	INT1_IR2_FLAG=1;/*trigger the int1 flag to indicate that the interrupt ocuur*/
	SET_BIT(GIFR,7); /*clear the interrupt flag for the next time*/
}


void changeToBusyOnLCD(void)
{
	/*change the garage state to busy*/
	LCD_moveCursor(1,7);
	LCD_displayString("Busy     ");/*display 5 spaces to avoid overwrite of "Available"word*/
}

void changeCarsNumberOnLCD(void)
{
	LCD_moveCursor(0,13);
	LCD_intgerToString(Cars_Number); /*change number of cars on LCD*/
	LCD_displayString("  ");
}

void enterTheCar(void)
{
	/*Rotating the servo motor to open the arm gate*/
	SERVO_MOTOR_vRotate_90ClockWise();

	/*wait the car to pass the arm */
	while (!GPIO_readPin(PORTD_ID,PIN2));

	/*Rotating the servo motor to close the arm gate*/
	SERVO_MOTOR_vRotate_90Anti_ClockWise();
}

uint8 compareArrays(uint8 *arr1,uint8 *arr2,uint8 size)
{
	uint8 i;
	for(i=0;i<size;i++)
	{
		if(arr1[i]!=arr2[i])
		{
			return UNMATCHED_PASSWORDS;
		}
	}
	return MATCHED_PASSWORDS;
}

/*function to get the password from the user then store it in an array
 * and display * for each number then go to infinite loop until press = */
void getPassword(uint8 *pass,uint8 size,uint8 firstPlace)
{
	uint8 i,key;
	for(i=0;i<size;i++)
	{
		key=KEYPAD_getPressedKey();
		if(key <10 )/*if the user enters any number from 0 to 9 store it in pass array*/
		{
			pass[i]=key;
			LCD_moveCursor(1,firstPlace+i);
			LCD_displayCharacter('*');
			_delay_ms(190);
		}
		else if(key ==13)/*handling the delete button */
		{
			i--;
			LCD_moveCursor(1,firstPlace+i);
			LCD_displayCharacter(' ');
			i--;
			_delay_ms(190);
		}
		else/*if the user enters any other button do nothing and wait a valid number*/
		{
			while(key >10){key=KEYPAD_getPressedKey();}
		}
	}
	/*wait for pressing =(enter) */
	while(KEYPAD_getPressedKey() !=EQUALBUTTON){}
}

void CreatePassword(void)
{
	uint8 pass1[PASSWORD_SIZE]={0},pass2[PASSWORD_SIZE]={0},CheckPass;

	LCD_clearScreen();
	LCD_displayString("Enter pass ");
	LCD_intgerToString(PASSWORD_SIZE);
	LCD_displayString(" Num");

	/*Get the 1st password from the user then store it in pass1 array
	 * and display '*' for each number entered then wait for pressing =(enter)*/
	getPassword(pass1,PASSWORD_SIZE,0);

	/*clear screen and display the new string*/
	LCD_clearScreen();
	LCD_displayString("plz re-enter the");
	LCD_displayStringRowColumn(1,0,"same pass: ");

	/*Get the 2nd password from the user and store it in pass2 array
	 * and display '*' for each number entered and wait for pressing =(enter)*/
	getPassword(pass2,PASSWORD_SIZE,11);

	CheckPass=compareArrays(pass1,pass2,PASSWORD_SIZE);

	/*if 2 different passwords are entered */
	if(CheckPass== UNMATCHED_PASSWORDS)
	{
		LCD_clearScreen();
		LCD_displayString("Passwords differ");
		LCD_displayStringRowColumn(1,0,"Retry");
		_delay_ms(3000);/*delay for vision*/
		CreatePassword();
	}

	/*if 2 matched passwords are entered*/
	else if(CheckPass==MATCHED_PASSWORDS)
		{
			LCD_clearScreen();
			LCD_displayString("Password created");
			LCD_displayStringRowColumn(1,0,"successfully");
			_delay_ms(1500);/*delay for vision*/
		}
}

void EXTI_vConfig_(uint8 copy_u8Int_No , uint8 copy_u8Dirn_Of_Pin , uint8 copy_u8Sense_Opt)
{
	switch(copy_u8Int_No )
	{
		/*Configuring INT0*/

		case 0 :
			//enabling INT0
			SET_BIT(GICR ,6);
			//configuring dirn
			if(copy_u8Dirn_Of_Pin == INPUT)
				GPIO_setupPinDirection(PORTD_ID,PIN2_ID,PIN_INPUT);
			else
				GPIO_setupPinDirection(PORTD_ID,PIN2_ID,PIN_OUTPUT);
			//configuring sensing options
			switch(copy_u8Sense_Opt)
			{
				case 0 :
					CLEAR_BIT(MCUCR , 0);
					CLEAR_BIT(MCUCR , 1);
				break;
				case 1 :
					CLEAR_BIT(MCUCR , 1);
					SET_BIT(MCUCR , 0);
				break;
				case 2 :
					CLEAR_BIT(MCUCR , 0);
					SET_BIT(MCUCR , 1);
				break;
				case 3 :
					SET_BIT(MCUCR , 0);
					SET_BIT(MCUCR , 1);
				break;
			}
		break;

		/*Configuring INT1*/

		case 1 :
			//enabling INT1

			SET_BIT(GICR ,7);

			//configuring dirn

			if(copy_u8Dirn_Of_Pin == INPUT)
				GPIO_setupPinDirection(PORTD_ID,PIN3_ID,PIN_INPUT);
			else
				GPIO_setupPinDirection(PORTD_ID,PIN3_ID,PIN_OUTPUT);
		//configuring sensing options
			switch(copy_u8Sense_Opt)
			{
				case 0 :
					CLEAR_BIT(MCUCR , 2);
					CLEAR_BIT(MCUCR , 3);
				break;
				case 1 :
					CLEAR_BIT(MCUCR , 3);
					SET_BIT(MCUCR , 2);
				break;
				case 2 :
					CLEAR_BIT(MCUCR , 2);
					SET_BIT(MCUCR , 3);
				break;
				case 3 :
					SET_BIT(MCUCR , 2);
					SET_BIT(MCUCR , 3);
				break;
			}
		break;
	}
}
void changeToAvailableOnLCD(void)
{
	/*change the garage state to Available*/
	LCD_moveCursor(1,7);
	LCD_displayString("Available");
}

void Exit_TheCar(void)
{
	/*Rotating the servo motor to open the arm gate*/
	SERVO_MOTOR_vRotate_90ClockWise();

	/*wait the car to pass the arm */
	while (!GPIO_readPin(PORTD_ID,PIN3_ID));

	/*Rotating the servo motor to close the arm gate*/
	SERVO_MOTOR_vRotate_90Anti_ClockWise();
}
