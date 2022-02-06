/*
 * main.c
 *
 *  Created on: Dec 15, 2021
 *      Author: Ahmed Loutfi
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_Interface.h"
#include"EXTI_Config.h"
#include"EXTI_Interface.h"
#include"GIE_Interface.h"
#include"TIMER_Interface.h"
#include<util/delay.h>
#include "System_State_Interface.h"
#include "Heater_Private.h"
#include "Heater_Config.h"
#define High 1
#define Low  0


u16 Temp = 70;
u16 AvrgTemp;
u16 State = NOTHING;
u16 SystemState = SYSTEM_OFF;
u8 Flag_1_Sec =0;
u8 Flag_5_Sec =0;

int main(void)
{
	System_Init();
	Temp = Current_Temp();
	AvrgTemp = Temp;
	while(1)
	{
		switch (SystemState) {
		case SYSTEM_OFF:
			System_Dis();
			break;
		case SYSTEM_ON:
			seven_Seg_Display(Temp);
			State = Current_State(State,AvrgTemp);
			SystemFun(State,&Flag_1_Sec);
			break;
		case SYSTEM_SET:
			EXTI0_VidDis();
			EXTI1_VidDis();
			TIMER1_Reset();
			Flag_5_Sec = 0;
			Flag_1_Sec = 1; //-> for showing
			while(Flag_5_Sec == 0)
			{
				if(Setting_Mode(&Flag_1_Sec)==1)
				{
					Flag_5_Sec = 0;
					TIMER1_Reset();
				}
			}
			SystemState = SYSTEM_ON;
			EXTI0_VidInit();
			EXTI1_VidInit();
			break;
		default:
			break;
		}
		/**/
	}
	return 0;

}



/*Interrupt Service Routine (ISR)*/
//Up Push Button ISR
void __vector_1(void)     __attribute__((signal));
void __vector_1(void)
{
	Seven_seg_OFF();
	SystemState = SYSTEM_SET;
	while(DIO_GetPinValue(PUSH_BUTTON_Heater_PORT,PUSH_BUTTON_Heater_PIN )==1)
	{
		//For preventing any change on the first press
	}
}
//Down Push Button ISR
void __vector_2(void)     __attribute__((signal));
void __vector_2(void)
{
	Seven_seg_OFF();
	SystemState = SYSTEM_SET;
	while(DIO_GetPinValue(PUSH_BUTTON_Cooler_PORT,PUSH_BUTTON_Cooler_PIN )==1)
	{
		//For preventing any change on the first press
	}
}
//ON-OFF Push Button ISR
void __vector_3(void)     __attribute__((signal));
void __vector_3(void)
{
	if(SystemState == SYSTEM_OFF)
	{
		SystemState = SYSTEM_ON;
		System_Init();
	}
	else
	{
		SystemState = SYSTEM_OFF;
		System_Dis();
	}

}

void __vector_10(void)     __attribute__((signal));
void __vector_10(void)
{
	static u8 Timer0Count = 0;
	static u16 Readings = 0;
	static u16 ReadingCont = 0;
	Timer0Count ++;
	if(Timer0Count == 10)
	{
		ReadingCont++;
		Temp = Current_Temp();
		Readings += Temp;
		if(ReadingCont%Num_Of_Temp_Measures == 0)
		{
			AvrgTemp=Readings/Num_Of_Temp_Measures;
			Readings = 0;
			ReadingCont = 0;
		}
	}
/**/
}

void __vector_7(void)     __attribute__((signal));
void __vector_7(void)
{
	Flag_1_Sec = 1;
	Timer1Count++;
	if(Timer1Count==5)
	{
		Flag_5_Sec = 1;
		Timer1Count=0;
	}
}

/**/
