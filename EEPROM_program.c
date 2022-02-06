/*
 * EEPROM_program.c
 *
 *  Created on: Dec 21, 2021
 *      Author: nesre
 */
#include"STD_TYPES.h"
#include"TWI_Interface.h"
#include"EEPROM_private.h"
#include<util\delay.h>

void EEPROM_vidsenddatabyte(u8 Copy_u8locationaddress,u8 Copy_u8pagenumber,u8 Copy_u8databyte){
	u8 Loc_u8addresspacket;
	Loc_u8addresspacket=EEPROM_Fixed_Address|Copy_u8pagenumber;

	/*1-send start condition*/
	TWI_SendStartCondition();
	/*2-send slave address(page number)+write request*/
	TWI_SendSlaveAddress_WithWrite(Loc_u8addresspacket);
	/*3-send 8 bites location address*/
	TWI_MasterSendData(Copy_u8locationaddress);
	/*4-send data byte to the memory location*/
	TWI_MasterSendData(Copy_u8databyte);
	/*5-SEND STOP Condition*/
	TWI_SendStopCondition();
	/*delay until the write cycle is finished*/
	_delay_ms(10);

}
/*read data byte from EEPROM*/
u8 EEPROM_readdatabyte(u8 Copy_u8locationaddress,u8 Copy_u8pagenumber){
	u8 Loc_u8addresspacket;
	u8  Loc_u8datareceive;
		Loc_u8addresspacket=EEPROM_Fixed_Address|Copy_u8pagenumber;

		/*1-send start condition*/
		TWI_SendStartCondition();
		/*2-send slave address(page number)+write request*/
		TWI_SendSlaveAddress_WithWrite(Loc_u8addresspacket);
		/*3-send 8 bites location address*/
		TWI_MasterSendData(Copy_u8locationaddress);
		/*4-send repeated start */
		TWI_SendRepeatedStartCondition();
		/*5-send slave address(page number)+read request*/
		TWI_SendSlaveAddress_WithRead(Loc_u8addresspacket);
		/*Read data byte from memory location*/
		TWI_MasterReadData(&Loc_u8datareceive);
		/*5-SEND STOP Condition*/
		TWI_SendStopCondition();
		return Loc_u8datareceive;
}
