/*
 * EXTI_program.c
 *
 *  Created on: Dec 29, 2021
 *      Author: nesre
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"EXTI_Private.h"
#include"EXTI_Interface.h"
void EXTI0_VidInit(void)
{
	/*set sense control*/
#if SET_SENSE_CONTROL==EXTI_RISING_EDGE
	SET_BIT(MCUCR,1);
	SET_BIT(MCUCR,0);

#elif SET_SENSE_CONTROL==EXTI_FALLING_EDGE
	SET_BIT(MCUCR,1);
	CLR_BIT(MCUCR,0);

#elif SET_SENSE_CONTROL==EXTI_ANY_LOGICAL_CHANGE
	CLR_BIT(MCUCR,1);
	SET_BIT(MCUCR,0);

#elif SET_SENSE_CONTROL==EXTI_LOW_LEVEL
	CLR_BIT(MCUCR,1);
	CLR_BIT(MCUCR,0);
#else
#error"Sense Control Options is not Valid......"
#endif
	/*Enable To EXTI0*/
	SET_BIT(GICR,6);
}
void EXTI1_VidInit(void)
{
	/*set sense control*/
#if SET_SENSE_CONTROL==EXTI_RISING_EDGE
	SET_BIT(MCUCR,3);
	SET_BIT(MCUCR,2);

#elif SET_SENSE_CONTROL==EXTI_FALLING_EDGE
	SET_BIT(MCUCR,3);
	CLR_BIT(MCUCR,2);

#elif SET_SENSE_CONTROL==EXTI_ANY_LOGICAL_CHANGE
	CLR_BIT(MCUCR,3);
	SET_BIT(MCUCR,2);

#elif SET_SENSE_CONTROL==EXTI_LOW_LEVEL
	CLR_BIT(MCUCR,3);
	CLR_BIT(MCUCR,2);
#else
#error"Sense Control Options is not Valid......"
#endif
	/*Enable To EXTI1*/
	SET_BIT(GICR,7);
}
void EXTI2_VidInit(void)
{
	/*set sense control*/
#if SET_SENSE_CONTROL==EXTI_RISING_EDGE
	SET_BIT(MCUCSR,6);

#elif SET_SENSE_CONTROL==EXTI_FALLING_EDGE
	CLR_BIT(MCUCSR,6);
#else
#error"Sense Control Options is not Valid......"
#endif
	/*Enable To EXTI2*/
	SET_BIT(GICR,5);
}

void EXTI_VidSet_SenseControl(u8 Copy_u8EXTI_Number,u8 Copy_u8SenseControl)
{
	switch(Copy_u8EXTI_Number)
	{
	case EXTI0:
		if(Copy_u8SenseControl==EXTI_RISING_EDGE)
		{
			SET_BIT(MCUCR,1);
			SET_BIT(MCUCR,0);
		}
		else if(Copy_u8SenseControl==EXTI_FALLING_EDGE)
		{
			SET_BIT(MCUCR,1);
			CLR_BIT(MCUCR,0);
		}
		else if(Copy_u8SenseControl==EXTI_ANY_LOGICAL_CHANGE)
		{
			CLR_BIT(MCUCR,1);
			SET_BIT(MCUCR,0);
		}
		else if(Copy_u8SenseControl==EXTI_LOW_LEVEL)
		{
			CLR_BIT(MCUCR,1);
			CLR_BIT(MCUCR,0);
		}
		break;
	case EXTI1:
		if(Copy_u8SenseControl==EXTI_RISING_EDGE)
		{
			SET_BIT(MCUCR,3);
			SET_BIT(MCUCR,2);
		}
		else if(Copy_u8SenseControl==EXTI_FALLING_EDGE)
		{
			SET_BIT(MCUCR,3);
			CLR_BIT(MCUCR,2);
		}
		else if(Copy_u8SenseControl==EXTI_ANY_LOGICAL_CHANGE)
		{
			CLR_BIT(MCUCR,3);
			SET_BIT(MCUCR,2);
		}
		else if(Copy_u8SenseControl==EXTI_LOW_LEVEL)
		{
			CLR_BIT(MCUCR,3);
			CLR_BIT(MCUCR,2);
		}
		break;
		break;
	case EXTI2:
		if(Copy_u8SenseControl==EXTI_RISING_EDGE)
		{
			SET_BIT(MCUCSR,6);
		}
		else if(Copy_u8SenseControl==EXTI_FALLING_EDGE)
		{
			CLR_BIT(MCUCSR,6);
		}
		break;
	}
}

void EXTI0_VidDis(void)
{
	CLR_BIT(GICR,6);
}
void EXTI1_VidDis(void)
{
	CLR_BIT(GICR,7);
}
void EXTI2_VidDis(void)
{
	CLR_BIT(GICR,5);
}
