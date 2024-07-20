/*
 * Servo_Motor.c
 *
 * Created: 7/5/2024 5:01:48 PM
 *  Author: Zyad Ayman
 */ 
#include "pwm.h"

void SERVO_MOTOR_vInit()
{
	//Initializing PWM of Timer1
	PWM_vInit_T1_FastMode();
	//Setting ICR1A as a Compare Value for Servo Motor *it is constant for Servo Motor*
	PWM_vSetValue_ICR1_T1_Manual(2499);
	
}
void SERVO_MOTOR_vRotate_90ClockWise()
{
	//setting OCR1A Value to get 5% duty Cycle
	PWM_vSetValue_OCR1A_T1_Manual(187);
	
	
}
void SERVO_MOTOR_vRotate_90Anti_ClockWise()
{
		
	//setting OCR1A Value to get 7.5% duty Cycle
	PWM_vSetValue_OCR1A_T1_Manual(125);
	
	
}
