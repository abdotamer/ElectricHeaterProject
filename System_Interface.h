/*
 * System_State.h
 *
 *  Created on: Jan 1, 2022
 *      Author: Ahmed Loutfi
 */

#ifndef SYSTEM_INTERFACE_H_
#define SYSTEM_INTERFACE_H_


//Possible States For Heater
#define NOTHING 0
#define HEATING 1
#define COOLING 2

#define SYSTEM_OFF 0
#define SYSTEM_ON  1
#define SYSTEM_SET 2

void System_Init(void);
void System_Dis(void);
u8 Setting_Mode(u8* Flag);
void SystemFun(u16 Desired_State,u8* Flag);
void HeaterLamp(u16 Desired_State,u8* Flag);
void Seven_seg_Init(void);
void Seven_seg_OFF(void);
void seven_Seg_Display(u16 Temp);
u16 Current_Temp(void);
u16 Current_State(u16 PrevState,u16 CurrentTemp);
void TIMER1_Init(void);
void TIMER1_Reset(void);
void TIMER1_OFF(void);
void TIMER1_SetCTCValue(u16 Copy_u16CTCValue);

static u8 Timer1Count=0;
//u8 Flag_1_Sec =0;
//u8 Flag_5_Sec =0;

#endif /* SYSTEM_INTERFACE_H_ */
