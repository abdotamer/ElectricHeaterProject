/*
 * ADC_Program.c
 *
 *  Created on: Oct 30, 2021
 *      Author: gerges
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"ADC_Private.h"
#include"ADC_Config.h"

void ADC_Init(void)
{
	/*1- Select Reference Voltage*/
#if SET_ADC_REF_VOLT==ADC_AVCC_REF_VOLT
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
#elif SET_ADC_REF_VOLT == ADC_INTERNAL_2560mV_REF_VOLT
	SET_BIT(ADMUX,6);
	SET_BIT(ADMUX,7);
#else
#error "Reference Voltage Option is not valid"
#endif
	/*2- Select Right or left Adjsut*/
#if SET_ADC_LEFT_ADJUST==ADC_LEFT_ADJUST
	SET_BIT(ADMUX,5);
#elif SET_ADC_LEFT_ADJUST==ADC_RIGHT_ADJUST
	CLR_BIT(ADMUX,5);
#else
#error "ADC LEFT Adjust option is not valid"
#endif
	/*Select Prescaler */
	ADCSRA&=0xF8;
	ADCSRA|=SET_ADC_PRESCALER;

	/*ADC Enable*/
	SET_BIT(ADCSRA,7);
}

void ADC_StartConversion(u8 Copy_u8Channel)
{
	/*Select the Suitable Channel*/
	ADMUX&=0xE0;
	ADMUX|=Copy_u8Channel;
	/*Start conversion*/
	SET_BIT(ADCSRA,6);
	/*Wait to complete conversion*/
	while(GET_BIT(ADCSRA,4)==0);
}

u16 ADC_ReadADCValue(void)
{
	return ADC;
}

u16 ADC_AnalogValue(u16 Copy_DigitalValue)
{
	u16 Local_u16AnalogValue;
	Local_u16AnalogValue=(Copy_DigitalValue*SET_ADC_REF_VOLT)/1023;
	return Local_u16AnalogValue;
}
