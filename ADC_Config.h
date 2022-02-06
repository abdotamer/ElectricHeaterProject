/*
 * ADC_Config.h
 *
 *  Created on: Oct 30, 2021
 *      Author: gerges
 */

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#define  ADC_AVCC_REF_VOLT               5000UL
#define  ADC_INTERNAL_2560mV_REF_VOLT	 2.56
/*Reference Voltage Options:
 * 1- ADC_AVCC_REF_VOLT
 * 2- ADC_INTERNAL_2560mV_REF_VOLT
 */

#define SET_ADC_REF_VOLT ADC_AVCC_REF_VOLT

/*ADC LEFT Adjsut Options:
 * 1- ADC_LEFT_ADJUST
 * 2- ADC_RIGHT_ADJUST
 */

#define SET_ADC_LEFT_ADJUST ADC_RIGHT_ADJUST

/*ADC PRESCALER Options:
 * 1- ADC_PRESCALER_2
 * 2- ADC_PRESCALER_4
 * 3- ADC_PRESCALER_8
 * 4- ADC_PRESCALER_16
 * 5- ADC_PRESCALER_32
 * 6- ADC_PRESCALER_64
 * 7- ADC_PRESCALER_128
 */
/*in single ended channel -->ADC Channel start from zero to 7 */
#define SET_ADC_PRESCALER   ADC_PRESCALER_128



#endif /* ADC_CONFIG_H_ */
