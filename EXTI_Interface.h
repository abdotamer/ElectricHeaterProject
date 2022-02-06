/*
 * EXIT_Interface.h
 *
 *  Created on: Dec 29, 2021
 *      Author: nesre
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define EXTI0  0
#define EXTI1  1
#define EXTI2  2

#define EXTI_RISING_EDGE         0
#define EXTI_FALLING_EDGE        1
#define EXTI_ANY_LOGICAL_CHANGE  2
#define EXTI_LOW_LEVEL           3

void EXTI0_VidInit(void);
void EXTI1_VidInit(void);
void EXTI2_VidInit(void);
void EXTI0_VidDis(void);
void EXTI1_VidDis(void);
void EXTI2_VidDis(void);
void EXTI_VidSet_SenseControl(u8 Copy_u8EXTI_Number,u8 Copy_u8SenseControl);

#endif /* EXTI_INTERFACE_H_ */
