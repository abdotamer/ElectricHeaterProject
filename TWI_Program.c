/*
 * TWI_Program.c
 *
 *  Created on: Nov 27, 2021
 *      Author: gerges
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"TWI_Private.h"
#include"TWI_Interface.h"

void TWI_VidInitMaster(u8 Copy_u8Address)
{
	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,6);
	/*Check if the master node will be addressed*/
	if(Copy_u8Address!=0)
	{
	/*Set the Required address in the 7MSB of TWAR*/
	TWAR=Copy_u8Address<<1;
	}
	else
	{
		/*Do Nothing*/
	}
	/*Set SCL Frequency To 400kHz,with 16MHz system Frequency*/
	/*1- Set TWBR=12*/
	TWBR=12;
	/*Set Precaler bits(TWPS0,TWPS1)*/
	CLR_BIT(TWSR,1);
	CLR_BIT(TWSR,0);
	/*Enable TWI*/
	SET_BIT(TWCR,2);
}
void TWI_VidInitSlave(u8 Copy_u8Address)
{
	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,6);
	/*Set the Required address in the 7MSB of TWAR*/
	TWAR=Copy_u8Address<<1;
	/*Enable TWI*/
	SET_BIT(TWCR,2);
}
TWI_ErrStatus TWI_SendStartCondition(void)
{
	TWI_ErrStatus Local_Error=NoError;
	/*send Start Condition*/
	SET_BIT(TWCR,5);
	/*Clear The Interrupt Flag To start The Previous Operation*/
	SET_BIT(TWCR,7);
	/*Wait Until The operation is finished and the flag is raised */
	while(GET_BIT(TWCR,7)==0);
	/*Check the operation status*/
	if((TWSR&0xF8)!=0X08)
	{
		Local_Error=StartConditionError;
	}
	else
	{
		/*Do nothing*/
	}
	return Local_Error;
}
TWI_ErrStatus TWI_SendRepeatedStartCondition(void)
{
	TWI_ErrStatus Local_Error=NoError;
	/*send Start Condition*/
	SET_BIT(TWCR,5);
	/*Clear The Interrupt Flag To start The Previous Operation*/
	SET_BIT(TWCR,7);
	/*Wait Until The operation is finished and the flag is raised */
	while(GET_BIT(TWCR,7)==0);
	/*Check the operation status*/
	if((TWSR&0xF8)!=0X10)
	{
		Local_Error=RepeatedStartError;
	}
	else
	{
		/*Do nothing*/
	}
	return Local_Error;
}
TWI_ErrStatus TWI_SendSlaveAddress_WithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_Error=NoError;
	/*Send 7bits Slave Address To the Bus*/
	TWDR=Copy_u8SlaveAddress<<1;
	/*Set the Write Request in the LSB bit in the data Register*/
	CLR_BIT(TWDR,0);
	/*Clear The start Condition Bit*/
	CLR_BIT(TWCR,5);
	/*Clear The Interrupt Flag To start The Previous Operation*/
	SET_BIT(TWCR,7);
	/*Wait Until The operation is finished and the flag is raised */
	while(GET_BIT(TWCR,7)==0);
	/*Check the operation status*/
	if((TWSR&0xF8)!=0X18)
	{
		Local_Error=SlaveAddressWithWriteError;
	}
	else
	{
		/*Do nothing*/
	}
	return Local_Error;
}
TWI_ErrStatus TWI_SendSlaveAddress_WithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ErrStatus Local_Error=NoError;
	/*Send 7bits Slave Address To the Bus*/
	TWDR=Copy_u8SlaveAddress<<1;
	/*Set the Read Request in the LSB bit in the data Register*/
	SET_BIT(TWDR,0);
	/*Clear The start Condition Bit*/
	CLR_BIT(TWCR,5);
	/*Clear The Interrupt Flag To start The Previous Operation*/
	SET_BIT(TWCR,7);
	/*Wait Until The operation is finished and the flag is raised */
	while(GET_BIT(TWCR,7)==0);
	/*Check the operation status*/
	if((TWSR&0xF8)!=0X40)
	{
		Local_Error=SlaveAddressWithReadError;
	}
	else
	{
		/*Do nothing*/
	}
	return Local_Error;
}
TWI_ErrStatus TWI_MasterSendData(u8 Copy_u8Data)
{
	TWI_ErrStatus Local_Error=NoError;
	/*Send 8bits Data Byte To the Bus*/
	TWDR=Copy_u8Data;
	/*Clear The Interrupt Flag To start The Previous Operation*/
	SET_BIT(TWCR,7);
	/*Wait Until The operation is finished and the flag is raised */
	while(GET_BIT(TWCR,7)==0);
	/*Check the operation status*/
	if((TWSR&0xF8)!=0X28)
	{
		Local_Error=MasterWriteError;
	}
	else
	{
		/*Do nothing*/
	}
	return Local_Error;
}
TWI_ErrStatus TWI_MasterReadData(u8* Copy_pu8Data)
{
	TWI_ErrStatus Local_Error=NoError;
	/*Clear The Interrupt Flag To start The Previous Operation*/
	SET_BIT(TWCR,7);
	/*Wait Until The operation is finished and the flag is raised */
	while(GET_BIT(TWCR,7)==0);
	/*Check the operation status*/
	if((TWSR&0xF8)!=0X50)
	{
		Local_Error=MasterReadError;
	}
	else
	{
		*Copy_pu8Data=TWDR;
	}
	return Local_Error;
}
TWI_ErrStatus TWI_SendStopCondition(void)
{
	/*Send Stop Condition*/
	SET_BIT(TWCR,4);
	/*Clear The Interrupt Flag To start The Previous Operation*/
	SET_BIT(TWCR,7);
}
