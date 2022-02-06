/*
 * TIMER_Private.h
 *
 *  Created on: Nov 6, 2021
 *      Author: gerges
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define TCCR0       *((volatile u8*)0x53)
#define TIMSK       *((volatile u8*)0x59)
#define TCNT0       *((volatile u8*)0x52)
#define OCR0        *((volatile u8*)0x5C)

#define TIMER_NO_PRESCALER       1
#define TIMER_8_PRESCALER        2
#define TIMER_64_PRESCALER       3
#define TIMER_256_PRESCALER      4
#define TIMER_1024_PRESCALER     5
#define TIMER_EXTERNAL_CLOCK_FALLING_EDGE    6
#define TIMER_EXTERNAL_CLOCK_RAISING_EDGE    7

#define TIMER_NORMAL_MODE                 1
#define TIMER_CTC_MODE					  2
#define TIMER_PHASE_CORRECT_PWM_MODE      3
#define TIMER_FAST_PWM_MODE               4

#define TIMER0_OC0_DISCONNECTED     0
#define TIMER0_OC0_TOGGLE           1
#define TIMER0_OC0_CLR              2
#define TIMER0_OC0_SET              3

#endif /* TIMER_PRIVATE_H_ */
