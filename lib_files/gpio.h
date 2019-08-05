#ifndef _GPIO_H
#define _GPIO_H

#include "stdutils.h"

typedef enum
{
	P0_0,P0_1,P0_2,P0_3,P0_4,P0_5,P0_6,P0_7,
	P1_0,P1_1,P1_2,P1_3,P1_4,P1_5,P1_6,P1_7,
	P2_0,P2_1,P2_2,P2_3,P2_4,P2_5,P2_6,P2_7,
	P3_0,P3_1,P3_2,P3_3,P3_4,P3_5,P3_6,P3_7,
	P_NC = 0xFF
}gpioPins_et;

/**********************************
GPIO Function Prototypes
**********************************/

#define GPIO_PinDir GPIO_PinWrite
void GPIO_PinWrite(gpioPins_et enm_pinNum, uint8_t var_pinVal);
uint8_t GPIO_PinRead (gpioPins_et enm_pinNum);


#endif
