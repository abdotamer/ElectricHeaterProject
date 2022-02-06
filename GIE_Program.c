/*
 * GIE_Program.c
 *
 *  Created on: Oct 29, 2021
 *      Author: gerges
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"GIE_Private.h"

void GIE_VidEnable(void)
{
	SET_BIT(SREG,7);
}
void GIE_VidDisable(void)
{
	CLR_BIT(SREG,7);
}
