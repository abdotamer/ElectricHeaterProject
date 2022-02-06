/*
 * System_State.c
 *
 *  Created on: Jan 1, 2022
 *      Author: Ahmed Loutfi
 */

#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"DIO_Interface.h"
#include"ADC_Interface.h"
#include"EXTI_Config.h"
#include"EXTI_Interface.h"
#include"GIE_Interface.h"
#include"TIMER_Interface.h"
#include"TWI_Interface.h"
#include"EEPROM_interface.h"
#include"Heater_Config.h"
#include "Heater_Private.h"
#include "System_State_Interface.h"
#include<util/delay.h>

//u16 CurrentState;
u8  datareceive;


void System_Init(void)
{
	GIE_VidDisable();
	ADC_Init();
	Seven_seg_OFF();
	Seven_seg_Init();
	//desired_temp = Init_Desired_Temp;


	//EEPROM_vidsenddatabyte(0,0,desired_temp);

	/*Set EXTI0 pin as an input and active pull up resistor*/
	//DIO_SetPinDirection(DIO_PORTD,PIN2,PIN_INPUT);

	//Initialization for cooler & Heater & LEDS & PushButtons
	DIO_SetPinDirection(COOLER_PORT, COOLER_PIN, PIN_OUTPUT);
	DIO_SetPinDirection(HEATER_PORT,HEATER_PIN,PIN_OUTPUT);

	DIO_SetPinDirection(LED_PORT,LED_PIN,PIN_OUTPUT);
	DIO_SetPinDirection(SYSTEM_LED_PORT,SYSTEM_LED_PIN,PIN_OUTPUT);

	DIO_SetPinDirection(PUSH_BUTTON_SYSTEM_PORT,PUSH_BUTTON_SYSTEM_PIN,PIN_INPUT);
	DIO_SetPinDirection(PUSH_BUTTON_Cooler_PORT,PUSH_BUTTON_Cooler_PIN,PIN_INPUT);
	DIO_SetPinDirection(PUSH_BUTTON_Heater_PORT,PUSH_BUTTON_Heater_PIN,PIN_INPUT);

	/*Set  Timer Preload*/
	//TIMER0_VidSET_Preload(156);

	/*Intialization for EXTI0*/
	EXTI0_VidInit();
	EXTI1_VidInit();
	EXTI2_VidInit();

	/*Timer Initialization*/
	TIMER0_VidSET_CTCValue(78); //0.01 Sec -> 16MHz = 156, 8MHz = 78
	TIMER1_Init();
	TIMER0_VidInit();
	/*Enable to GIE*/
	GIE_VidEnable();

	DIO_SetPinValue(SYSTEM_LED_PORT,SYSTEM_LED_PIN,PIN_HIGH);
	TWI_VidInitMaster(0);
	if(EEPROM_readdatabyte(0,0) != 0xFF)   // check if there are no data in EEPROM (first time to use it)
	{
		desired_temp = EEPROM_readdatabyte(0,0);       // read data from byte number 0 in external EEPROM IC
	}
	else
	{
		desired_temp = Init_Desired_Temp;

	}
	EEPROM_vidsenddatabyte(0,0,desired_temp);
}

void System_Dis(void)
{
	GIE_VidDisable();
	DIO_SetPinValue(SYSTEM_LED_PORT,SYSTEM_LED_PIN,PIN_LOW);
	DIO_SetPinValue(LED_PORT,LED_PIN,PIN_LOW);
	DIO_SetPinValue(HEATER_PORT,HEATER_PIN,PIN_LOW);
	DIO_SetPinValue(COOLER_PORT,COOLER_PIN,PIN_LOW);
	EXTI0_VidDis();
	EXTI1_VidDis();
	TIMER0_OFF();
	TIMER1_OFF();
	Seven_seg_OFF();
	GIE_VidEnable();
}

u16 Current_State(u16 PrevState,u16 CurrentTemp)
{
	//u16 desired;
	//Setting_Mode
	//CLR_BIT(DDRD,2);
	//CLR_BIT(DDRD,6 );
	//DIO_GetPinValue
	u16 NewState = PrevState;
	switch (PrevState) {
		case COOLING:
			if(CurrentTemp < desired_temp - 5)
				NewState = NOTHING;
			break;
		case HEATING:
			if(CurrentTemp > desired_temp + 5)
				NewState = NOTHING;
			break;
		case NOTHING:
			if(CurrentTemp < desired_temp)
				NewState = HEATING;
			else if (CurrentTemp > desired_temp)
				NewState = COOLING;
			break;
		default:
			break;
	}
	return NewState;
}

u16 Current_Temp(void)
{
	f32 Digital_Value;
	ADC_StartConversion(0);
	Digital_Value=ADC_ReadADCValue();

	return Digital_Value*5/1024*150/1.5;
}


u8 Setting_Mode(u8* Flag)
{
	//u16 Current_temp=0;
	//u16 desired_temp;

	//CLR_BIT(DDRD,2);
	//CLR_BIT(DDRD,6);

	//seven_Seg_Display(current_temperature); // Set Temperature From EEPROM
	u8 ChangeStatus = 0;
	if((DIO_GetPinValue(PUSH_BUTTON_Heater_PORT,PUSH_BUTTON_Heater_PIN)==1) && (desired_temp<Max_Temp))
	{
		desired_temp += 5;
		ChangeStatus = 1;
	}
	if ((DIO_GetPinValue(PUSH_BUTTON_Cooler_PORT,PUSH_BUTTON_Cooler_PIN )==1)&& (desired_temp>Min_Temp))
	{
		desired_temp-= 5;
		ChangeStatus = 1;
	}
	if(ChangeStatus)
	{
		EEPROM_vidsenddatabyte(0,0,desired_temp);
	}
	if(*Flag == 1|| ChangeStatus)
	{
		*Flag = 0;
		seven_Seg_Display(desired_temp);
		_delay_ms(180);
		Seven_seg_OFF();
	}
	return ChangeStatus;
}




void SystemFun(u16 Desired_State,u8* Flag)
{
	if(Desired_State == HEATING)
	{
		DIO_SetPinValue(HEATER_PORT,HEATER_PIN ,HEATER_ON);
		DIO_SetPinValue(COOLER_PORT,COOLER_PIN ,Cooler_OFF);
	}
	else if(Desired_State == COOLING)
	{
		DIO_SetPinValue(COOLER_PORT,COOLER_PIN ,Cooler_ON);
		DIO_SetPinValue(HEATER_PORT,HEATER_PIN ,HEATER_OFF);
	}
	else
	{
		DIO_SetPinValue(HEATER_PORT,HEATER_PIN ,HEATER_OFF);
		DIO_SetPinValue(COOLER_PORT,COOLER_PIN ,Cooler_OFF);
	}

	HeaterLamp(Desired_State,Flag);
}

void HeaterLamp(u16 Desired_State,u8* Flag)
{
	if(Desired_State == HEATING)
	{
		DIO_SetPinValue(LED_PORT,LED_PIN ,PIN_HIGH);
	}
	else if(Desired_State == COOLING && *(Flag)== 1)
	{
		DIO_SetPinValue(LED_PORT,LED_PIN ,PIN_HIGH);
		_delay_ms(50);
		DIO_SetPinValue(LED_PORT,LED_PIN ,PIN_LOW);
		*(Flag) = 0;
	}
	else
		DIO_SetPinValue(LED_PORT,LED_PIN ,PIN_LOW);
}
/*
void Heating_Mode(u16 desired_temp)
{


	while(current_temperature<desired_temp)
	{
		//heating on

		DIO_SetPinValue(LED_HEATER_PORT,LED_HEATER_PIN ,LED_HEATER_ON);
		_delay_ms(300);
		DIO_SetPinValue(LED_HEATER_PORT,LED_HEATER_PIN , LED_HEATER_OFF );
		_delay_ms(300);
	}

	//heating off
	DIO_SetPinValue(LED_HEATER_PORT,LED_HEATER_PIN, LED_HEATER_OFF );

}*/
void Seven_seg_Init(void)
{
	DIO_SetPinDirection(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PINA,PIN_OUTPUT);
	DIO_SetPinDirection(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PINB,PIN_OUTPUT);
	DIO_SetPinDirection(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PINC,PIN_OUTPUT);
	DIO_SetPinDirection(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PIND,PIN_OUTPUT);

	DIO_SetPinDirection(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PINA,PIN_OUTPUT);
	DIO_SetPinDirection(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PINB,PIN_OUTPUT);
	DIO_SetPinDirection(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PINC,PIN_OUTPUT);
	DIO_SetPinDirection(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PIND,PIN_OUTPUT);

	DIO_SetPinDirection(SEVEN_SEGMENT_ENABLE_PORT,SEVEN_SEGMENT_ENABLE_PIN,PIN_OUTPUT);
}


void seven_Seg_Display(u16 Temp)
{
	DIO_SetPinValue(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PINA,(Temp/10)>>3&1);
	DIO_SetPinValue(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PINB,(Temp/10)>>2&1);
	DIO_SetPinValue(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PINC,(Temp/10)>>1&1);
	DIO_SetPinValue(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PIND,(Temp/10)&1);

	DIO_SetPinValue(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PINA,(Temp%10)>>3&1);
	DIO_SetPinValue(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PINB,(Temp%10)>>2&1);
	DIO_SetPinValue(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PINC,(Temp%10)>>1&1);
	DIO_SetPinValue(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PIND,(Temp%10)&1);

	DIO_SetPinValue(SEVEN_SEGMENT_ENABLE_PORT,SEVEN_SEGMENT_ENABLE_PIN,PIN_LOW);
}
void Seven_seg_OFF(void)
{
	DIO_SetPinValue(SEVEN_SEGMENT_ENABLE_PORT,SEVEN_SEGMENT_ENABLE_PIN,PIN_HIGH);
	/*DIO_SetPinValue(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PINA,PIN_LOW);
	DIO_SetPinValue(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PINB,PIN_LOW);
	DIO_SetPinValue(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PINC,PIN_LOW);
	DIO_SetPinValue(SEVEN_SEGMENT_LEFT_PORT,SEVEN_SEGMENT_LEFT_PIND,PIN_LOW);

	DIO_SetPinValue(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PINA,PIN_LOW);
	DIO_SetPinValue(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PINB,PIN_LOW);
	DIO_SetPinValue(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PINC,PIN_LOW);
	DIO_SetPinValue(SEVEN_SEGMENT_RIGHT_PORT,SEVEN_SEGMENT_RIGHT_PIND,PIN_LOW);*/
}

void TIMER1_Init(void)
{
	TIMER1_SetCTCValue(31250); // 1 Sec -> 16MHz =62500, 8MHz = 31250

	/*select the Prescaler_256*/
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	SET_BIT(TCCR1B,2);

	/*Select Normal Mode (Overflow)*/
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);

	/*Timer OCA interrupt enable*/
	SET_BIT(TIMSK,4);
	TIMER1_Reset();
}

void TIMER1_Reset(void)
{
	TCNT1 &= 0;
	Timer1Count = 0;
}
void TIMER1_SetCTCValue(u16 Copy_u16CTCValue)
{
	OCR1A=Copy_u16CTCValue;
}
void TIMER1_OFF(void)
{
	CLR_BIT(TIMSK,5);
	CLR_BIT(TIMSK,4);
	CLR_BIT(TIMSK,3);
	CLR_BIT(TIMSK,2);

}
