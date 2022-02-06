/*
 * ADC_Interface.h
 *
 *  Created on: Oct 30, 2021
 *      Author: gerges
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

void ADC_Init(void);

void ADC_StartConversion(u8 Copy_u8Channel);

u16 ADC_ReadADCValue(void);

u16 ADC_AnalogValue(u16 Copy_DigitalValue);

#endif /* ADC_INTERFACE_H_ */
