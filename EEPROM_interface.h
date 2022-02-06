/*
 * EEPROM_interface.h
 *
 *  Created on: Dec 21, 2021
 *      Author: nesre
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_
/*send data byte to EEPROM*/
void EEPROM_vidsenddatabyte(u8 Copy_u8locationaddress,u8 Copy_u8pagenumber,u8 Copy_u8databyte);
/*read data byte from EEPROM*/
u8 EEPROM_readdatabyte(u8 Copy_u8locationaddress,u8 Copy_u8pagenumber);
#endif /* EEPROM_INTERFACE_H_ */
