/*
 * Heater_Config.h
 *
 *  Created on: Jan 7, 2022
 *      Author: user
 */

#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

/*
 * Defining System PINS and PORTS
 */

#define PUSH_BUTTON_SYSTEM_PORT	DIO_PORTB
#define PUSH_BUTTON_SYSTEM_PIN	PIN2

#define SYSTEM_LED_PORT		DIO_PORTB
#define SYSTEM_LED_PIN			PIN3

#define SEVEN_SEGMENT_ENABLE_PORT	DIO_PORTA
#define SEVEN_SEGMENT_ENABLE_PIN	PIN2

#define SEVEN_SEGMENT_LEFT_PORT  DIO_PORTB
#define SEVEN_SEGMENT_LEFT_1MB   PIN4
#define SEVEN_SEGMENT_LEFT_2MB   PIN5
#define SEVEN_SEGMENT_LEFT_3MB   PIN6
#define SEVEN_SEGMENT_LEFT_4MB   PIN7

#define SEVEN_SEGMENT_RIGHT_PORT  DIO_PORTC
#define SEVEN_SEGMENT_RIGHT_1MB   PIN4
#define SEVEN_SEGMENT_RIGHT_2MB   PIN5
#define SEVEN_SEGMENT_RIGHT_3MB   PIN6
#define SEVEN_SEGMENT_RIGHT_4MB   PIN7

#define PUSH_BUTTON_Heater_PORT   DIO_PORTD
#define PUSH_BUTTON_Heater_PIN    PIN2

#define PUSH_BUTTON_Cooler_PORT   DIO_PORTD
#define PUSH_BUTTON_Cooler_PIN    PIN3

#define HEATER_PORT     DIO_PORTD
#define HEATER_PIN      PIN4

#define COOLER_PORT     DIO_PORTD
#define COOLER_PIN      PIN5

#define LED_PORT		DIO_PORTD
#define LED_PIN			PIN7

/*Initial State options:
 * 1- SYSTEM_ON
 * 2- SYSTEM_OFF
 * 3- SYSTEM_SET
 */
#define InitialState SYSTEM_OFF

#define Init_Desired_Temp 60
#define Num_Of_Temp_Measures 10
#define Min_Temp 35
#define Max_Temp 75

#endif /* SYSTEM_CONFIG_H_ */
