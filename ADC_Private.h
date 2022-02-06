/*
 * ADC_Private.h
 *
 *  Created on: Oct 30, 2021
 *      Author: gerges
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADMUX       *((volatile u8*)0x27)
#define ADCSRA      *((volatile u8*)0x26)
#define ADC         *((volatile u16*)0x24)

#define ADCH        *((volatile u8*)0x25)
#define ADCL        *((volatile u8*)0x24)

#define SFIO        *((volatile u8*)0x50)


#define  ADC_INTERNAL_2.56V_REF_VOLT     2560

#define ADC_RIGHT_ADJUST      0
#define ADC_LEFT_ADJUST       1

#define ADC_PRESCALER_2   1
#define ADC_PRESCALER_4   2
#define ADC_PRESCALER_8   3
#define ADC_PRESCALER_16  4
#define ADC_PRESCALER_32  5
#define ADC_PRESCALER_64  6
#define ADC_PRESCALER_128 7




#endif /* ADC_PRIVATE_H_ */
