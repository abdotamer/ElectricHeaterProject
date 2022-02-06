/*
 * TWI_Interface.h
 *
 *  Created on: Nov 27, 2021
 *      Author: gerges
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_
typedef enum
{
	NoError,
	StartConditionError,
	RepeatedStartError,
	SlaveAddressWithWriteError,
	SlaveAddressWithReadError,
	MasterWriteError,
	MasterReadError
}TWI_ErrStatus;

void TWI_VidInitMaster(u8 Copy_u8Address);
void TWI_VidInitSlave(u8 Copy_u8Address);
TWI_ErrStatus TWI_SendStartCondition(void);
TWI_ErrStatus TWI_SendRepeatedStartCondition(void);
TWI_ErrStatus TWI_SendSlaveAddress_WithWrite(u8 Copy_u8SlaveAddress);
TWI_ErrStatus TWI_SendSlaveAddress_WithRead(u8 Copy_u8SlaveAddress);
TWI_ErrStatus TWI_MasterSendData(u8 Copy_u8Data);
TWI_ErrStatus TWI_MasterReadData(u8* Copy_pu8Data);
TWI_ErrStatus TWI_SendStopCondition(void);

#endif /* TWI_INTERFACE_H_ */
