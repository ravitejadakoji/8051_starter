#ifndef DELAY_H
#define	DELAY_H

#include "stdutils.h"

#define C_OneMSDelayCount 112u

#define ENABLE_DELAY_SEC 0

/*****************************
Delay Function Prototypes
****************************/

void delay_us(uint16_t var_Count_us);
void delay_ms(uint16_t var_Count_ms);
void delay_sec(uint16_t var_ount_sec);

#endif	
