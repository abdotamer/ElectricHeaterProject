/*
 * TIMER_Interface.h
 *
 *  Created on: Nov 6, 2021
 *      Author: gerges
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void TIMER0_VidInit(void);
void TIMER0_VidSET_Preload(u8 Copy_u8PreloadValue);
void TIMER0_VidSET_CTCValue(u8 Copy_u8CTCValue);
void TIMER0_OFF();
#endif /* TIMER_INTERFACE_H_ */
