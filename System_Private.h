/*
 * Heater_Private.h
 *
 *  Created on: Jan 7, 2022
 *      Author: user
 */

#ifndef SYSTEM_PRIVATE_H_
#define SYSTEM_PRIVATE_H_

#define HEATER_OUT      PIN_OUTPUT
#define HEATER_ON       PIN_HIGH
#define HEATER_OFF      PIN_LOW

#define Cooler_OUT      PIN_OUTPUT
#define Cooler_ON       PIN_HIGH
#define Cooler_OFF      PIN_LOW


//Timer1 Registers
#define TCCR1A    *((volatile u8*)0x4F)
#define TCCR1B    *((volatile u8*)0x4E)
#define ICR1      *((volatile u16*)0x46)
#define OCR1A     *((volatile u16*)0x4A)
#define OCR1B     *((volatile u16*)0x48)
#define TIMSK     *((volatile u8*)0x59)
#define TCNT1     *((volatile u16*)0x4C)

u16 desired_temp;
u16 MaxSensorReading;
#endif /* SYSTEM_PRIVATE_H_ */
